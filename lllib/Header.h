//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#ifndef __lllib__Header__
#define __lllib__Header__

#include <array>
#include <cstdint>
#include <iostream>

namespace lllib {
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

#endif /* defined(__lllib__Header__) */
