// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketTypes__
#define __libol__PacketTypes__

#include <cstdint>

namespace libol {
    struct PacketType {
        enum : uint8_t {
            EndSpawn = 0x11,
            SetAbilityLevel = 0x15,
            ExpGain = 0x22,
            SummonerData = 0x2A,
            PlayerStats = 0x46,
            HeroSpawn = 0x4C,
            StartSpawn = 0x62,
            ItemPurchase = 0x6F,
            TurretSpawn = 0x9D,
            GoldGain = 0xE4
        };
    };
}

#endif /* defined(__libol__PacketTypes__) */