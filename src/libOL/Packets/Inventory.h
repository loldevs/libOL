// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Inventory__
#define __libol__Inventory__

#include "Packet.h"

#include <cstdint>
#include <array>

namespace libol {
    class Inventory : public Packet {
    public:
        struct Item {
            uint32_t itemId;
            uint8_t slotId;
            uint8_t quantity;
            uint8_t charges;
            float cooldown;
            float baseCooldown;
        };

        uint32_t entityId;
        std::array<Item, 10> items;

        Inventory(Block& ifs);
        static bool test(Block& ifs);
    };
}

#endif /* defined(__libol__Inventory__) */
