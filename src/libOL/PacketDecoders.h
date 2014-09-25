// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketDecoders__
#define __libol__PacketDecoders__

#include "Value.h"
#include "Block.h"
#include "Constants.h"
#include "EntityAttribute.h"
#include "ParseException.h"

#include <cstdint>
#include <cmath>
#include <array>

namespace libol {
    class SetAbilityLevelPkt {
    public:
        static const PacketType::Id type = PacketType::SetAbilityLevel;
        static std::string name() { return "SetAbilityLevel"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x3);

            Object data = Object();

            data.setv("abilityId", block.content[0]);
            data.setv("level", block.content[1]);

            //assert(block.content[2] == 0x00);

            return Value::create(data);
        }
    };

    class GoldRewardPkt {
    public:
        static const PacketType::Id type = PacketType::GoldReward;
        static std::string name() { return "GoldReward"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0xc);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("receiverEntId", stream.read<uint32_t>());
            data.setv("killedEntId", stream.read<uint32_t>());
            data.setv("amount", stream.read<float>());

            return Value::create(data);
        }
    };

    class GoldGainPkt {
    public:
        static const PacketType::Id type = PacketType::GoldGain;
        static std::string name() { return "GoldGain"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x8);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("receiverEntId", stream.read<uint32_t>());
            data.setv("amount", stream.read<float>());

            return Value::create(data);
        }
    };

    class SetInventoryPkt {
    public:
        static const PacketType::Id type = PacketType::SetInventory;
        static std::string name() { return "SetInventory"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x98);

            Object data = Object();
            std::array<Object, 10> items;

            auto stream = block.createStream(0x2);

            for(size_t i = 0; i < items.size(); i++) {
                items[i].setv("itemId", stream.read<uint32_t>());
                items[i].setv("slotId", stream.get());
                items[i].setv("stacks", stream.get());
                items[i].setv("charges", stream.get());
            }

            for(size_t i = 0; i < items.size(); i++) {
                items[i].setv("cooldown", stream.read<float>());
            }

            for(size_t i = 0; i < items.size(); i++) {
                items[i].setv("baseCooldown", stream.read<float>());
            }

            Array itemsArr = Array();
            for(auto& item : items)
                itemsArr.pushv(item);
            data.setv("items", itemsArr);

            return Value::create(data);
        }
    };

    class ItemPurchasePkt {
    public:
        static const PacketType::Id type = PacketType::ItemPurchase;
        static std::string name() { return "ItemPurchase"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x8);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("itemId", stream.read<uint32_t>());
            data.setv("slot", stream.get());
            data.setv("stacks", stream.read<uint16_t>());

            //assert(block.content[0x7] == 0x40);

            return Value::create(data);
        }
    };

    class ChampionSpawnPkt {
    public:
        static const PacketType::Id type = PacketType::ChampionSpawn;
        static std::string name() { return "ChampionSpawn"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0xC3);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("entityId", stream.read<uint32_t>());
            data.setv("clientId", stream.read<uint32_t>());

            stream.ignore(0xA); // unknown

            // Summoner name
            char summonerChars[0x81];
            stream.read(summonerChars, 0x80);
            summonerChars[0x80] = 0x00;
            data.setv("summonerName", std::string(summonerChars));

            // Champion name
            char championChars[0x11];
            stream.read(championChars, 0x10);
            championChars[0x10] = 0x00;
            data.setv("championName", std::string(championChars));

            stream.ignore(0x21); // unknown

            return Value::create(data);
        }
    };

    class SummonerDataPkt {
    public:
        static const PacketType::Id type = PacketType::SummonerData;
        static std::string name() { return "SummonerData"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x212);

            Object data = Object();

            auto stream = block.createStream();

            Array runes = Array();
            for(size_t i = 0; i < 30; i++) {
                runes.pushv(stream.read<uint32_t>());
            }
            data.setv("runes", runes);

            uint32_t spell1Id = stream.read<uint32_t>();
            uint32_t spell2Id = stream.read<uint32_t>();
            data.setv("spell1", spell1Id);
            data.setv("spell1Name", SummonerSpell::getName(spell1Id));
            data.setv("spell2", spell2Id);
            data.setv("spell2Name", SummonerSpell::getName(spell2Id));

            Array masteries = Array();
            size_t masteryCount = 0;
            while(masteryCount++ < 79) {
                auto pos = stream.tellg();
                stream.ignore(2);
                uint8_t test = stream.get();
                stream.seekg(pos);
                if(test != 0x03) break;

                Object entry = Object();
                uint8_t id = stream.get();
                entry.setv("id", id);
                uint8_t tree = stream.get();
                entry.setv("tree", tree);
                entry.setv("talentId", 4100 + (tree - 0x74) * 0x64 + ((id >> 4) - 0x03) * 0x0A + (id & 0x0F));
                EXPECT(stream.get() == 0x03);
                EXPECT(stream.get() == 0x00);
                entry.setv("pointsSpent", stream.get());
                masteries.pushv(entry);
            }
            data.setv("masteries", masteries);

            data.setv("level", block.content[0x210]);

            return Value::create(data);
        }
    };

    class PlayerStatsPkt {
    public:
        static const PacketType::Id type = PacketType::PlayerStats;
        static std::string name() { return "PlayerStats"; }

        static Value decode(Block& block) {
            bool hasJungleStats;
            switch(block.size) {
                case 0x128:
                    hasJungleStats = false;
                    break;
                case 0x130:
                    hasJungleStats = true;
                    break;
                default:
                    throw ParseException("PlayerStats: unknown size " + std::to_string(block.size));
            }

            Object data = Object();

            auto stream = block.createStream(0x4);

            data.setv("assists", stream.read<uint32_t>());
            stream.ignore(0x4);
            data.setv("kills", stream.read<uint32_t>());
            stream.ignore(0x4);
            data.setv("doubleKills", stream.read<uint32_t>());
            stream.ignore(3 * 0x4);
            data.setv("unrealKills", stream.read<uint32_t>());
            data.setv("goldEarned", stream.read<float>());
            data.setv("goldSpent", stream.read<float>());
            stream.ignore(10 * 0x4);
            data.setv("currentKillingSpree", stream.read<uint32_t>());
            data.setv("largestCriticalStrike", stream.read<float>());
            data.setv("largestKillingSpree", stream.read<uint32_t>());
            data.setv("largestMultiKill", stream.read<uint32_t>());
            stream.ignore(0x4);
            data.setv("longestTimeSpentLiving", stream.read<float>());
            data.setv("magicDamageDealt", stream.read<float>());
            data.setv("magicDamageDealtToChampions", stream.read<float>());
            data.setv("magicDamageTaken", stream.read<float>());
            data.setv("minionsKilled", stream.read<uint32_t>());
            stream.ignore(0x2); // Padding
            data.setv("neutralMinionsKilled", stream.read<uint32_t>());
            if(hasJungleStats) {
                data.setv("neutralMinionsKilledInEnemyJungle", stream.read<uint32_t>());
                data.setv("neutralMinionsKilledInTeamJungle", stream.read<uint32_t>());
            }
            stream.ignore(0x4);
            data.setv("deaths", stream.read<uint32_t>());
            data.setv("pentaKills", stream.read<uint32_t>());
            data.setv("physicalDamageDealt", stream.read<float>());
            data.setv("physicalDamageDealtToChampions", stream.read<float>());
            data.setv("physicalDamageTaken", stream.read<float>());
            stream.ignore(0x4);
            data.setv("quadraKills", stream.read<uint32_t>());
            stream.ignore(9 * 0x4);
            data.setv("teamId", stream.read<uint32_t>());
            stream.ignore(4 * 0x4);
            data.setv("totalDamageDealt", stream.read<float>());
            data.setv("totalDamageDealtToChamptions", stream.read<float>());
            data.setv("totalDamageTaken", stream.read<float>());
            data.setv("totalHeal", stream.read<uint32_t>());
            data.setv("totalTimeCrowdControlDealt", stream.read<float>());
            data.setv("totalTimeSpentDead", stream.read<float>());
            data.setv("totalUnitsHealed", stream.read<uint32_t>());
            data.setv("tripleKills", stream.read<uint32_t>());
            data.setv("trueDamageDealt", stream.read<float>());
            data.setv("trueDamageDealtToChamptions", stream.read<float>());
            data.setv("trueDamageTaken", stream.read<float>());
            data.setv("towerKills", stream.read<uint32_t>());
            data.setv("inhibitorKills", stream.read<uint32_t>());
            stream.ignore(0x4);
            data.setv("wardsKilled", stream.read<uint32_t>());
            data.setv("wardsPlaced", stream.read<uint32_t>());
            stream.ignore(2 * 0x4);
            stream.ignore(0x2); // Padding

            return Value::create(data);
        }
    };

    class MovementGroupPkt {
    public:
        static const PacketType::Id type = PacketType::MovementGroup;
        static std::string name() { return "MovementGroup"; }

        static Value decode(Block& block) {
            Object data = Object();

            auto stream = block.createStream();

            data.setv("timestamp", stream.read<uint32_t>()); // in ms from start
            uint16_t numUpdates = stream.read<uint16_t>();

            Array updates = Array();
            while(numUpdates--) {
                Object update = Object();

                uint8_t numCoords = stream.get(); // includes the 2 start coords
                update.setv("entityId", stream.read<uint32_t>());

                if(numCoords % 2) {
                    stream.ignore(1);
                    numCoords--;
                }

                std::vector<uint8_t> bitmask; // defines if a coord is relative for non-start coords
                if(numCoords > 2) {
                    size_t bmSize = std::floor((numCoords - 3) / 8.f) + 1;
                    for (size_t i = 0; i < bmSize; i++)
                        bitmask.push_back(stream.get());
                }

                int16_t startX = stream.read<int16_t>();
                int16_t startY = stream.read<int16_t>();
                Object start = Object();
                start.setv("x", startX);
                start.setv("y", startY);
                update.setv("position", start);

                Array waypoints = Array();
                for(size_t i = 0; i < (size_t)(numCoords - 2); i++) {
                    Object point = Object();

                    if(bitmask[floor(i  / 8.f)] & (1 << i % 8))
                        point.setv("x", startX + stream.read<int8_t>());
                    else
                        point.setv("x", stream.read<int16_t>());

                    i++;
                    if(bitmask[floor(i / 8.f)] & (1 << i % 8))
                        point.setv("y", startY + stream.read<int8_t>());
                    else
                        point.setv("y", stream.read<int16_t>());

                    waypoints.pushv(point);
                }
                update.setv("waypoints", waypoints);

                updates.pushv(update);
            }
            data.setv("updates", updates);

            return Value::create(data);
        }
    };

    class SetOwnershipPkt {
    public:
        static const PacketType::Id type = PacketType::SetOwnership;
        static std::string name() { return "SetOwnership"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x4);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("ownerEntId", stream.read<uint32_t>());

            return Value::create(data);
        }
    };

    class AttentionPingPkt {
    public:
        static const PacketType::Id type = PacketType::AttentionPing;
        static std::string name() { return "AttentionPing"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x11);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("x", stream.read<float>());
            data.setv("y", stream.read<float>());
            data.setv("targetEntId", stream.read<uint32_t>());
            data.setv("playerEntId", stream.read<uint32_t>());

            uint8_t type = stream.read<uint8_t>();
            data.setv("type", type);
            data.setv("typeName", AttentionPingType::getName(type));

            return Value::create(data);
        }
    };

    class PlayEmotePkt {
    public:
        static const PacketType::Id type = PacketType::PlayEmote;
        static std::string name() { return "PlayEmote"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x1);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("type", stream.read<uint8_t>()); // TODO: find out enum

            return Value::create(data);
        }
    };

    class DamageDonePkt {
    public:
        static const PacketType::Id type = PacketType::DamageDone;
        static std::string name() { return "DamageDone"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0xd);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("type", stream.read<uint8_t>()); // TODO: find out enum
            data.setv("receiverEntId", stream.read<uint32_t>());
            data.setv("sourceEntId", stream.read<uint32_t>());
            data.setv("amount", stream.read<float>());

            return Value::create(data);
        }
    };

    class SetDeathTimerPkt {
    public:
        static const PacketType::Id type = PacketType::SetDeathTimer;
        static std::string name() { return "SetDeathTimer"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x12);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("killerEntId", stream.read<uint32_t>());
            stream.ignore(8);
            data.setv("timer", stream.read<float>());
            stream.ignore(2);

            return Value::create(data);
        }
    };

    class SetHealthPkt {
    public:
        static const PacketType::Id type = PacketType::SetHealth;
        static std::string name() { return "SetHealth"; }

        static Value decode(Block& block) {
            if(block.size == 0x2) { // TODO: understand this
                throw ParseException("SetHealth: size is only 2 bytes");
            }

            REQUIRE(block.size == 0xa);

            Object data = Object();

            auto stream = block.createStream();

            stream.ignore(2);
            data.setv("maxHealth", stream.read<float>());
            data.setv("currentHealth", stream.read<float>());

            return Value::create(data);
        }
    };

    class AttributeGroupPkt {
    public:
        static const PacketType::Id type = PacketType::AttributeGroup;
        static std::string name() { return "AttributeGroup"; }

        static Value decode(Block& block) {
            Object data = Object();

            auto stream = block.createStream();

            data.setv("timestamp", stream.read<uint32_t>()); // in ms from start
            uint8_t numUpdates = stream.read<uint8_t>();

            Array updates = Array();
            while(numUpdates--) {
                Object update = Object();

                uint8_t groupMask = stream.get(); // defines which groups of attributes will follow
                update.setv("entityId", stream.read<uint32_t>());

                Object attr = Object();
                for(uint8_t groupBit = 0; groupBit < 8; groupBit++) {
                    if(!(groupMask & (1 << groupBit))) continue;

                    uint32_t attrMask = stream.read<uint32_t>(); // defines which attributes from this group will follow

                    uint8_t groupSize = stream.get();
                    size_t groupStart = stream.tellg();

                    for(uint8_t attrBit = 0; attrBit < 32; attrBit++) {
                        if(!(attrMask & (1 << attrBit))) continue;

                        if(!EntityAttribute::read(&attr, stream, groupBit, attrBit)) {
                            stream.seekg(groupStart + groupSize);
                            break;
                        }
                    }
                    if(stream.tellg() != groupStart + groupSize) // TODO: investigate
                        stream.seekg(groupStart + groupSize);
                }
                update.setv("attributes", attr);

                updates.pushv(update);
            }
            data.setv("updates", updates);

            return Value::create(data);
        }
    };

    class SetTeamPkt {
    public:
        static const PacketType::Id type = PacketType::SetTeam;
        static std::string name() { return "SetTeam"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x1);

            Object data = Object();

            auto stream = block.createStream();

            uint8_t teamId = stream.get();
            data.setv("team", teamId);
            data.setv("teamName", Team::getName(teamId));

            return Value::create(data);
        }
    };

    class SetItemStacksPkt {
    public:
        static const PacketType::Id type = PacketType::SetItemStacks;
        static std::string name() { return "SetItemStacks"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x3);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("slotId", stream.get());
            data.setv("stacks", stream.read<uint16_t>());

            return Value::create(data);
        }
    };

    class SummonerDisconnectPkt {
    public:
        static const PacketType::Id type = PacketType::SummonerDisconnect;
        static std::string name() { return "SummonerDisconnect"; }

        static Value decode(Block& block) {
            REQUIRE(block.size == 0x5);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("entityId", stream.read<uint32_t>());
            stream.ignore(1); // unknown

            return Value::create(data);
        }
    };

    class SetLevelPkt {
    public:
        static const PacketType::Id type = PacketType::SetLevel;
        static std::string name() { return "SetLevel"; }

        static Value decode(Block &block) {
            REQUIRE(block.size == 0x2);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("level", stream.read<uint8_t>());
            data.setv("skillPoints", stream.read<uint8_t>());

            return Value::create(data);
        }
    };

    class ChampionRespawnPkt {
    public:
        static const PacketType::Id type = PacketType::ChampionRespawn;
        static std::string name() { return "ChampionRespawn"; }

        static Value decode(Block &block) {
            REQUIRE(block.size == 0xc);

            Object data = Object();

            auto stream = block.createStream();

            data.setv("x", stream.read<float>());
            data.setv("y", stream.read<float>());
            data.setv("mana", stream.read<float>());

            return Value::create(data);
        }
    };
}

#endif /* defined(__libol__PacketDecoders__) */
