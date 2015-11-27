#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <mist/stream.h>
#include <mist/flv_tag.h>
#include <mist/defines.h>
#include <mist/ts_packet.h>
#include <mist/mp4_generic.h>
#include "input_ts.h"

/// \todo Implement this trigger equivalent...
/*
if(Triggers::shouldTrigger("STREAM_PUSH", smp)){
  std::string payload = streamName+"\n" + myConn.getHost() +"\n"+capa["name"].asStringRef()+"\n"+reqUrl;
  if (!Triggers::doTrigger("STREAM_PUSH", payload, smp)){
    DEBUG_MSG(DLVL_FAIL, "Push from %s to %s rejected - STREAM_PUSH trigger denied the push", myConn.getHost().c_str(), streamName.c_str());
    myConn.close();
    configLock.post();
    configLock.close();
    return;
  }
}
*/


namespace Mist {
  
  
  /// Constructor of TS Input
  /// \arg cfg Util::Config that contains all current configurations.
  inputTS::inputTS(Util::Config * cfg) : Input(cfg) {
    capa["name"] = "TS";
    capa["decs"] = "Enables TS Input";
    capa["source_match"] = "/*.ts";
    capa["priority"] = 9ll;
    capa["codecs"][0u][0u].append("H264");
    capa["codecs"][0u][0u].append("HEVC");
    capa["codecs"][0u][1u].append("AAC");
    capa["codecs"][0u][1u].append("AC3");

    capa["optional"]["port"]["name"] = "UDP Port";
    capa["optional"]["port"]["help"] = "The udp port on which to listen for incoming UDP Packets";
    capa["optional"]["port"]["type"] = "uint";
    capa["optional"]["port"]["default"] = 9876;
    capa["optional"]["port"]["option"] = "--port";
    cfg->addOption("port",
                   JSON::fromString("{\"arg\":\"integer\",\"value\":9876,\"short\":\"p\",\"long\":\"port\",\"help\":\"The udp port on which to listen for incoming UDP Packets.\"}"));

    pushing = false;
    inFile = NULL;
  }

  inputTS::~inputTS() {
    if (inFile){
      fclose(inFile);
    }
  }
  
  ///Setup of TS Input
  bool inputTS::setup() {
#ifdef INPUT_LIVE
    if (config->getString("input") == "-") {
      inFile = stdin;
    }else{
      pushing = true;
      udpCon.setBlocking(false);
      udpCon.bind(config->getInteger("port"));
    }
#else
    if (config->getString("input") != "-"){
      inFile = fopen(config->getString("input").c_str(), "r");
    }
    if (!inFile) {
      return false;
    }
#endif
    return true;
  }
  
  ///Track selector of TS Input
  ///\arg trackSpec specifies which tracks  are to be selected
  ///\todo test whether selecting a subset of tracks work
  void inputTS::trackSelect(std::string trackSpec) {
    selectedTracks.clear();
    long long int index;
    while (trackSpec != "") {
      index = trackSpec.find(' ');
      selectedTracks.insert(atoi(trackSpec.substr(0, index).c_str()));
      if (index != std::string::npos) {
        trackSpec.erase(0, index + 1);
      } else {
        trackSpec = "";
      }
    }
  }

  
  ///Reads headers from a TS stream, and saves them into metadata
  ///It works by going through the entire TS stream, and every time
  ///It encounters a new PES start, it writes the currently found PES data
  ///for a specific track to metadata. After the entire stream has been read, 
  ///it writes the remaining metadata.
  ///\todo Find errors, perhaps parts can be made more modular
  bool inputTS::readHeader(){
    if (!inFile) {
      return false;
    }
    DTSC::File tmp(config->getString("input") + ".dtsh");
    if (tmp){
      myMeta = tmp.getMeta();
      return true;
    } 
    
    TS::Packet packet;//to analyse and extract data
    fseek(inFile, 0, SEEK_SET);//seek to beginning
    
    bool first = true;
    long long int lastBpos = 0;
    while (packet.FromFile(inFile) && !feof(inFile)){
      tsStream.parse(packet, lastBpos);
      lastBpos = ftell(inFile);
      while(tsStream.hasPacketOnEachTrack()){
        if (first){
          tsStream.initializeMetadata(myMeta);
          first = false;
        }
        DTSC::Packet headerPack;
        tsStream.getEarliestPacket(headerPack);
        myMeta.update(headerPack);
      }

    }

    fseek(inFile, 0, SEEK_SET);
    std::ofstream oFile(std::string(config->getString("input") + ".dtsh").c_str());
    oFile << myMeta.toJSON().toNetPacked();
    oFile.close();
    return true;
  }
  

  ///Gets the next packet that is to be sent 
  ///At the moment, the logic of sending the last packet that was finished has been implemented, 
  ///but the seeking and finding data is not yet ready.
  ///\todo Finish the implementation
  void inputTS::getNext(bool smart){
    thisPacket.null();
    bool hasPacket = (selectedTracks.size() == 1 ? tsStream.hasPacket(*selectedTracks.begin()) : tsStream.hasPacketOnEachTrack());
    while (!hasPacket && (pushing || !feof(inFile)) && config->is_active){
      if (!pushing) {
        unsigned int bPos = ftell(inFile);
        tsBuf.FromFile(inFile);
        if (selectedTracks.count(tsBuf.getPID())){
          tsStream.parse(tsBuf, bPos);
        }
      }else{
        while (udpCon.Receive()){
          udpDataBuffer.append(udpCon.data, udpCon.data_len);
          while (udpDataBuffer.size() > 188 && (udpDataBuffer[0] != 0x47 || udpDataBuffer[188] != 0x47)){
            size_t syncPos = udpDataBuffer.find("\107", 1);
            udpDataBuffer.erase(0, syncPos);
          }
          while (udpDataBuffer.size() >= 188){
            tsBuf.FromPointer(udpDataBuffer.data());
            tsStream.parse(tsBuf, 0);
            udpDataBuffer.erase(0,188);
          }
        }
        if (userClient.getData()){
          userClient.keepAlive();
        }
        Util::sleep(500);
      }
      if (userClient.getData()){
        userClient.keepAlive();
      }
      hasPacket = (selectedTracks.size() == 1 ? tsStream.hasPacket(*selectedTracks.begin()) : tsStream.hasPacketOnEachTrack());
    }
    if (!hasPacket){
      if(inFile && !feof(inFile)){
        getNext();
      }
      if (pushing){
        sleep(500);
      }
      return;
    }
    if (selectedTracks.size() == 1){
      tsStream.getPacket(*selectedTracks.begin(), thisPacket);
    }else{
      tsStream.getEarliestPacket(thisPacket);
    }
    tsStream.initializeMetadata(myMeta);
    if (!myMeta.tracks.count(thisPacket.getTrackId())){
      getNext();
    }
  }

  void inputTS::readPMT(){
    //save current file position
    int bpos = ftell(inFile);
    if (fseek(inFile, 0, SEEK_SET)){
      FAIL_MSG("Seek to 0 failed");
      return;
    }

    TS::Packet tsBuffer;
    while (!tsStream.hasPacketOnEachTrack() && tsBuffer.FromFile(inFile)){
      tsStream.parse(tsBuffer, 0);
    }
    
    //Clear leaves the PMT in place
    tsStream.clear();


    //Restore original file position
    if (fseek(inFile, bpos, SEEK_SET)){
      return;
    }

  }
  
  ///Seeks to a specific time
  void inputTS::seek(int seekTime){
    tsStream.clear();
    readPMT();
    unsigned long seekPos = 0xFFFFFFFFull;
    for (std::set<unsigned long>::iterator it = selectedTracks.begin(); it != selectedTracks.end(); it++){
      unsigned long thisBPos = 0;
      for (std::deque<DTSC::Key>::iterator keyIt = myMeta.tracks[*it].keys.begin(); keyIt != myMeta.tracks[*it].keys.end(); keyIt++){
        if (keyIt->getTime() > seekTime){
          break;
        }
        thisBPos = keyIt->getBpos();
      }
      if (thisBPos < seekPos){
        seekPos = thisBPos;
      }
    }
    fseek(inFile, seekPos, SEEK_SET);//seek to the correct position
  }
}