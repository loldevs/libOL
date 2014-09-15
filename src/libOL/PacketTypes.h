// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketTypes__
#define __libol__PacketTypes__

#include <cstdint>

namespace libol {
    struct PacketType {
        enum : uint8_t {
            SetOwnership = 0x07,
            EndSpawn = 0x11,
            SetAbilityLevel = 0x15,
            ExpGain = 0x22,
            SummonerData = 0x2A,
            AttentionPing = 0x40,
            PlayEmote = 0x42,
            PlayerStats = 0x46,
            HeroSpawn = 0x4C,
            SetDeathTimer = 0x5E,
            MovementGroup = 0x61,
            StartSpawn,
            DamageDone = 0x65,
            ItemPurchase = 0x6F,
            TurretSpawn = 0x9D,
            GoldGain = 0xE4
        };
    };
}

#endif /* defined(__libol__PacketTypes__) */
