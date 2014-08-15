// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PlayerSegment__
#define __libol__PlayerSegment__

#include <cstdint>
#include <iostream>
#include <array>

namespace libol {
    class PlayerSegment {
    public:
        std::array<uint8_t, 0x17> header;
        std::string summonerName;
        std::string championName;
        std::array<uint8_t, 0x2C> unk0;
        std::array<uint32_t, 30> runes;
        std::array<uint8_t, 0x194> masteries;
        std::array<uint8_t, 0x09> itemsHeader;
        std::array<uint8_t, 9/* items (10 in wiki) */ * (0x07 + 0x04)> items;
        /* playerData header */
        std::array<uint8_t, 0x130> playerData;
        /* abilities */
        /* unknown string data */
        /* unknown data */
        std::array<uint8_t, 0x09> footer;

        static bool probe(std::ifstream& ifs);
        static PlayerSegment decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__PlayerSegment__) */
