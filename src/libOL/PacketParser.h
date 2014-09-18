// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketParser__
#define __libol__PacketParser__

#include "Block.h"
#include "Packet.h"
#include "PacketDecoders.h"

#include <vector>
#include <fstream>

namespace libol {
    class PacketParser {
        friend struct Packet;

        struct PacketDecoder {
            std::function< std::string () > getName;
            std::function< bool (Block&) > test;
            std::function< Value (Block&) > decode;
        };
        std::vector< PacketDecoder > decoders;

        template<class PACKET>
        void registerPacket() {
            decoders.push_back(PacketDecoder({PACKET::name, PACKET::test, PACKET::decode}));
        };

        PacketParser() {
            registerPacket<SetAbilityLevelPkt>();
            registerPacket<ExpGainPkt>();
            registerPacket<GoldGainPkt>();
            registerPacket<SetInventoryPkt>();
            registerPacket<ItemPurchasePkt>();
            registerPacket<HeroSpawnPkt>();
            registerPacket<SummonerDataPkt>();
            registerPacket<PlayerStatsPkt>();
            registerPacket<MovementGroupPkt>();
            registerPacket<SetOwnershipPkt>();
            registerPacket<AttentionPingPkt>();
            registerPacket<PlayEmotePkt>();
            registerPacket<DamageDonePkt>();
            registerPacket<SetDeathTimerPkt>();
            registerPacket<SetHealthPkt>();
            registerPacket<AttributeGroupPkt>();
        }

        Packet decode(Block& block) {
            Packet packet;

            packet.timestamp = block.time;
            packet.type = block.type;
            packet.entityId = block.entityId;

            packet.isDecoded = false;
            for(auto& decoder : decoders) {
                if(decoder.test(block)) {
                    packet.isDecoded = true;
                    packet.typeName = decoder.getName();
                    packet.data = decoder.decode(block);
                    break;
                }
            }

            return packet;
        }

        static PacketParser& getInstance() {
            static PacketParser instance;
            return instance;
        }
    };
}

#endif /* defined(__libol__PacketParser__) */
