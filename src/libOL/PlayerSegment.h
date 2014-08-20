// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PlayerSegment__
#define __libol__PlayerSegment__

#include <cstdint>
#include <iostream>
#include <array>
#include <vector>

#include <libOL/MasteryEntry.h>
#include <libOL/ItemEntry.h>
#include <libOL/AbilityEntry.h>

namespace libol {
    class PlayerSegment {
    public:
        std::array<uint8_t, 0x17> header;
        std::string summonerName;
        std::string championName;
        std::array<uint8_t, 0x2C> unk0;
        std::array<uint32_t, 30> runes;
        std::array<uint8_t, 0x08> masteriesHeader;
        std::vector<MasteryEntry> masteries; 
        std::array<uint8_t, 0x09> itemsHeader;
        std::array<ItemEntry, 10> items;
        /* playerData header */
        std::array<uint8_t, 0x130 - 0xC> playerData;
        /* abilities header */
        std::array<AbilityEntry, 4> abilities;
        /* unknown string data */
        /* unknown data */
        std::array<uint8_t, 0x09> footer;

        static bool probe(std::ifstream& ifs);
        static PlayerSegment decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__PlayerSegment__) */
