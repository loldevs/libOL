//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#ifndef __lllib__Header__
#define __lllib__Header__

#include <cstdint>
#include <array>

namespace lllib {
    class Header {
    public:
        std::array<uint8_t, 6> magic;
        std::array<uint8_t, 256> signature;
        int16_t headerlength;
        int32_t fileLength;
        int32_t metadataOffset;
        int32_t metadataLength;
        int32_t payloadHeaderOffset;
        int32_t payloadHeaderLength;
        int32_t payloadOffset;
    };
}

#endif /* defined(__lllib__Header__) */
