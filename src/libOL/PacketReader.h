// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PacketReader__
#define __libol__PacketReader__

#include "Block.h"
#include "Packets/Packet.h"
#include "Packets/KeyframeHeader.h"
#include "Packets/PlayerHeader.h"
#include "Packets/SummonerData.h"
#include "Packets/Inventory.h"
#include "Packets/PlayerStats.h"
#include "Packets/AbilityLevel.h"
#include "Packets/TurretHeader.h"
#include "Packets/ItemPurchase.h"
#include "Packets/GoldGain.h"
#include "Packets/ExpGain.h"

#include <functional>
#include <vector>

namespace libol {
    class PacketReader {
        std::vector< std::function< void (Block&) > > handlers;
        std::vector< std::function< void (Packet*) > > packetHandlers;

        void callPacketHandlers(Packet* packet) {
            for(auto handler : packetHandlers) {
                handler(packet);
            }
        }
    public:
        void read(Block& block) {
            for(auto handler : handlers) {
                handler(block);
            }
        }

        void read(std::vector<Block>& blocks) {
            for(auto& block : blocks) read(block);
        }

        template<class PACKET>
        void on(std::function<void (PACKET&)> cb) {
            handlers.push_back([this, cb] (Block& block) {
                if(PACKET::test(block)) {
                    PACKET packet(block);
                    packet.timestamp = block.time;
                    callPacketHandlers(&packet);
                    cb(packet);
                }
            });
        }

        void onPacket(std::function<void (Packet*)> cb) {
            packetHandlers.push_back(cb);
        }
    };
}

#endif /* defined(__libol__PacketReader__) */
