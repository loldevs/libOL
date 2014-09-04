// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Player__
#define __libol__Player__

#include "PacketReader.h"

#include <cstdint>
#include <vector>


namespace libol {
    class Player {
    public:
        struct Summoner {
            std::string name;
            uint8_t level;
            std::array<uint32_t, 30> runes;
            std::array<uint32_t, 2> spells;
            std::vector<MasteryEntry> masteries;
        };

        uint32_t playerId;
        uint32_t entityId;
        std::string champion;

        Summoner summoner;
        std::array<Inventory::Item, 10> items;
        PlayerStats::Stats stats;
        std::vector<AbilityLevel> abilities;
    };
}

#endif /* defined(__libol__Player__) */
