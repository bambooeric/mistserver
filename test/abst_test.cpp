/// \file abst_test.cpp
/// Tests the bootstrap generation functions by comparing to a known good bootstrap.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mist/mp4.h>
#include <string.h>
#include <string>

/// This is a known good bootstrap retrieved from a wowza demo server.
unsigned char __data[] ={
    0x00, 0x00, 0x0c, 0xce, 0x61, 0x62, 0x73, 0x74, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x03, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x19, 0xea, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x1a, 0x61, 0x73, 0x72, 0x74, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xc7, 0x01, 0x00, 0x00, 0x0c, 0x86, 0x61, 0x66, 0x72, 0x74,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe8, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5d, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaf, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbb, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xea, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0d, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x19, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x24, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x30, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3c, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x48, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x5f, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6b, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x77, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x82, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8e, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9a, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xa5, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb1, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xbd, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc9, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xd4, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xec, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0f, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x1b, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x26, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x32, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3e, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x49, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x55, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x61, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x6d, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x78, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x84, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x90, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x9b, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xa7, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xb3, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xbf, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xca, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xd6, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xe2, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xee, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf9, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x28, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x34, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x40, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x4b, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x57, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x63, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x6e, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x7a, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x86, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x92, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x9d, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xa9, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xb5, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xcc, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xd8, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe4, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xef, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfb, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x12, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x1e, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2a, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x36, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x41, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x4d, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x59, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x65, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x70, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x7c, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x88, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x93, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x9f, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xab, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xb7, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xc2, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xce, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xda, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xe5, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xf1, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xfd, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x09, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x14, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x20, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x2c, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x37, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x43, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x4f, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x5b, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x66, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x72, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x7e, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x89, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x95, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xa1, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xad, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xb8, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xc4, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xd0, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xdc, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xe7, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf3, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0a, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x16, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x22, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x2e, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x39, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x45, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x51, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x5c, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x68, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x74, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x80, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8b, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x97, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xa3, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xae, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xba, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc6, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xd2, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xdd, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xe9, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xf5, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0c, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x24, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x2f, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3b, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x47, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x53, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x5e, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x6a, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x76, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8d, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x99, 0x50, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xa5, 0x08, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xa9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xb0, 0xc0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbc, 0x78, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xab, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc8, 0x30, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xac, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xd3, 0xe8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xdf, 0xa0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xeb, 0x58, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf7, 0x10, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x02, 0xc8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0e, 0x80, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1a, 0x38, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x25, 0xf0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x31, 0xa8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x3d, 0x60, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 0x18, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x54, 0xd0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0x88, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x6c, 0x40, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xba, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x77, 0xf8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x83, 0xb0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8f, 0x68, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x9b, 0x20, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xa6, 0xd8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xb2, 0x90, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xbe, 0x48, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xca, 0x00, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xd5, 0xb8, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xe1, 0x70, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xed, 0x28, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xf8, 0xe0, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x04, 0x98, 0x00, 0x00, 0x0b, 0xb8, 0x00, 0x00,
    0x00, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x10, 0x50, 0x00, 0x00, 0x09, 0x9a};
unsigned int __data_len = 3278;

/// Generates a bootstrap equal to the above file, then compares.
/// \returns Zero if they are equal (test success), other values otherwise.
int main(int argc, char **argv){
  std::string temp;

  MP4::ASRT asrt;
  asrt.setVersion(1);
  asrt.setQualityEntry(temp, 0);
  asrt.setSegmentRun(1, 199, 0);

  MP4::AFRT afrt;
  afrt.setVersion(1);
  afrt.setTimeScale(1000);
  afrt.setQualityEntry(temp, 0);
  MP4::afrt_runtable afrtrun;
  for (int i = 0; i < 198; i++){
    afrtrun.firstFragment = i + 1;
    afrtrun.firstTimestamp = 3000 * i;
    afrtrun.duration = 3000;
    afrt.setFragmentRun(afrtrun, i);
  }
  afrtrun.firstFragment = 199;
  afrtrun.firstTimestamp = 594000;
  afrtrun.duration = 2458;
  afrt.setFragmentRun(afrtrun, 198);

  MP4::ABST abst;
  abst.setVersion(1);
  abst.setBootstrapinfoVersion(1);
  abst.setProfile(0);
  abst.setLive(false);
  abst.setUpdate(false);
  abst.setTimeScale(1000);
  abst.setCurrentMediaTime(596458);
  abst.setSmpteTimeCodeOffset(0);
  abst.setMovieIdentifier(temp);
  abst.setServerEntry(temp, 0);
  abst.setQualityEntry(temp, 0);
  abst.setDrmData(temp);
  abst.setMetaData(temp);
  abst.setSegmentRunTable(asrt, 0);
  abst.setFragmentRunTable(afrt, 0);

  if (abst.boxedSize() != __data_len){return 42;}
  return memcmp(abst.asBox(), __data, __data_len);
}
