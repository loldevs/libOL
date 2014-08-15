// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__KeyframeHeader__
#define __libol__KeyframeHeader__

#include <cstdint>
#include <iostream>
#include <array>

namespace libol {
    class KeyframeHeader {
    public:
        uint8_t start; /* 03 */
        float timestamp; // In seconds
        std::array<uint8_t, 11> unk0;
        
        static KeyframeHeader decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__KeyframeHeader__) */
