// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketParser__
#define __libol__PacketParser__

#include "Block.h"
#include "Packet.h"
/*#include "Packets/KeyframeHeader.h"
#include "Packets/PlayerHeader.h"
#include "Packets/SummonerData.h"
#include "Packets/Inventory.h"
#include "Packets/PlayerStats.h"*/
#include "Packets/AbilityLevel.h"
/*#include "Packets/TurretHeader.h"
#include "Packets/ItemPurchase.h"
#include "Packets/GoldGain.h"
#include "Packets/ExpGain.h"*/

#include <vector>
#include <fstream>

namespace libol {
    typedef std::pair< std::function< bool (Block&) >, std::function< Value (Block&) > > PacketDecoder;
    class PacketParser {
        std::vector< PacketDecoder > decoders;

    public:
        PacketParser() {
            registerPacket<AbilityLevel>();
        }

        template<class PACKET>
        void registerPacket() {
            decoders.push_back(PacketDecoder(PACKET::test, PACKET::decode));
        }

        Packet decode(Block& block) {
            Packet packet;

            packet.timestamp = block.time;
            packet.type = block.type;
            packet.entityId = block.entityId;

            for(auto& decoder : decoders) {
                if(decoder.first(block)) {
                    packet.data = decoder.second(block);
                    break;
                }
            }
            // TODO: do something if no decoder found

            return packet;
        }

    };
}

#endif /* defined(__libol__PacketParser__) */
