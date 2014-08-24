// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__SummonerData__
#define __libol__SummonerData__

#include "Block.h"

#include <cstdint>
#include <array>

namespace libol {
    class MasteryEntry {
    public:
        uint8_t id;
        uint8_t tree;
        /* 03 00 */
        uint8_t pointsSpent;
        
        static bool probe(Block::Stream& ifs);
        static MasteryEntry decode(Block::Stream& ifs);
    };
    
    class SummonerData {
    public:
        std::array<uint32_t, 30> runes;
        std::array<uint32_t, 2> spells;
        std::vector<MasteryEntry> masteries;
        uint8_t level;
        
        static SummonerData decode(Block& block);
    };
}

#endif /* defined(__libol__SummonerData__) */
