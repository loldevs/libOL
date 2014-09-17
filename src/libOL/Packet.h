// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Packet__
#define __libol__Packet__

#include "Value.h"
#include "Block.h"
#include <string>

namespace libol {
    struct Packet {
        ~Packet() {
            data.destroy();
        };

        float timestamp;
        uint8_t type;
        uint32_t entityId;

        bool isDecoded;
        std::string typeName;
        Value data;

        static Packet decode(Block& block);
    };
}

#endif /* defined(__libol__Packet__) */
