// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Inventory__
#define __libol__Inventory__

#include "Block.h"

#include <cstdint>
#include <array>

namespace libol {
    class Inventory {
    public:
        struct Item {
            uint32_t itemId;
            uint8_t slotId;
            uint8_t quantity;
            uint8_t charges;
            float cooldown;
            float baseCooldown;
        };

        std::array<Item, 10> items;

        static Inventory decode(Block& ifs);
    };
}

#endif /* defined(__libol__Inventory__) */
