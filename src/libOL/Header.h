// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Header__
#define __libol__Header__

#include <array>
#include <cstdint>
#include <iostream>

namespace libol {
    class Header {
    public:
        std::array<uint8_t, 6> magic;
        std::array<uint8_t, 256> signature;
        uint16_t headerlength;
        uint32_t fileLength;
        uint32_t metadataOffset;
        uint32_t metadataLength;
        uint32_t payloadHeaderOffset;
        uint32_t payloadHeaderLength;
        uint32_t payloadOffset;

        static Header decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__Header__) */
