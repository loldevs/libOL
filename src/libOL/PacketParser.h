// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketParser__
#define __libol__PacketParser__

#include "Block.h"
#include "Packet.h"
#include "PacketDecoders.h"

#include <map>
#include <fstream>

namespace libol {
    class PacketParser {
        friend struct Packet;

        struct PacketDecoder {
            std::function< std::string () > getName;
            std::function< Value (Block&) > decode;
        };

        std::map<PacketType::Id, PacketDecoder > decoders;

        template<class PACKET>
        void registerPacket() {
            PacketType::Id type = PACKET::type;
            decoders[type] = PacketDecoder({PACKET::name, PACKET::decode});
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
            registerPacket<SetTeamPkt>();
            registerPacket<SetItemStacksPkt>();
            registerPacket<SummonerDisconnectPkt>();
        }

        Packet decode(Block& block) {
            Packet packet;

            packet.timestamp = block.time;
            if(block.type == PacketType::ExtendedType) {
                uint16_t realType;
                block.read(&realType, 0);
                packet.type = realType;
            } else
                packet.type = block.type;
            packet.entityId = block.entityId;

            packet.isDecoded = false;
            if(decoders.count(packet.type)) {
                auto& decoder = decoders[packet.type];
                try {
                    packet.data = decoder.decode(block);
                    packet.typeName = decoder.getName();
                    packet.isDecoded = true;
                } catch(ParseException& ex) {
                    packet.isDecoded = false;
                    throw;
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
