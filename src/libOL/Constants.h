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
            SetHealth = 0xAE,
            GoldGain = 0xE4
        };
    };

    struct SummonerSpell {
        enum Id : uint32_t {
            Revive = 0x05C8B3A5,
            Smite = 0x065E8695,
            Exhaust = 0x08A8BAE4,
            Barrier = 0x0CCFB982,
            Teleport = 0x004F1364,
            Ghost = 0x064ACC95,
            Heal = 0x0364AF1C,
            Cleanse = 0x064D2094,
            Clarity = 0x03657421,
            Ignite = 0x06364F24,
            Promote = 0x0410FF72,
            Clair = 0x09896765,
            Flash = 0x06496EA8,
            Test = 0x0103D94C,
        };

        static std::string getName(uint32_t id) {
            switch(id) {
                case Revive: return "Revive";
                case Smite: return "Smite";
                case Exhaust: return "Exhaust";
                case Barrier: return "Barrier";
                case Teleport: return "Teleport";
                case Ghost: return "Ghost";
                case Heal: return "Heal";
                case Cleanse: return "Cleanse";
                case Clarity: return "Clarity";
                case Ignite: return "Ignite";
                case Promote: return "Promote";
                case Clair: return "Clair";
                case Flash: return "Flash";
                case Test: return "Test";
                default: return "UnknownSpell";
            }
        }
    };

    struct AttentionPingType {
        enum Id : uint8_t {
            Default = 0xb0,
            Danger = 0xb2,
            EnemyMissing,
            OnMyWay,
            Retreat,
            AssistanceNeeded
        };

        static std::string getName(uint8_t id) {
            switch(id) {
                case Default: return "Default";
                case Danger: return "Danger";
                case EnemyMissing: return "EnemyMissing";
                case OnMyWay: return "OnMyWay";
                case Retreat: return "Retreat";
                case AssistanceNeeded: return "AssistanceNeeded";
                default: return "UnknownPingType";
            }
        }
    };
}

#endif /* defined(__libol__PacketTypes__) */
