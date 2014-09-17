// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Packet.h"
#include "PacketParser.h"


namespace libol {
    Packet Packet::decode(Block& block) {
        return PacketParser::getInstance().decode(block);
    }
}
