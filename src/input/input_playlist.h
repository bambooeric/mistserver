#include "input.h"
#include <mist/dtsc.h>
#include <deque>

namespace Mist {
  class inputPlaylist : public Input {
    public:
      inputPlaylist(Util::Config * cfg);
      bool needsLock(){return false;}
    protected:
      bool checkArguments();
      bool readHeader() { return true; }
      virtual void parseStreamHeader() {myMeta.tracks[1].codec = "PLACEHOLDER";}
      std::string streamMainLoop();
      virtual bool needHeader(){return false;}
    private:
      void reloadPlaylist();
      std::deque<std::string> playlist;
      std::deque<uint16_t> playlist_startTime;
      std::string currentSource;
      size_t playlistIndex;
      size_t minIndex, maxIndex;
      bool seenValidEntry;
      uint32_t wallTime;
      uint32_t reloadOn;
  };
}

typedef Mist::inputPlaylist mistIn;

