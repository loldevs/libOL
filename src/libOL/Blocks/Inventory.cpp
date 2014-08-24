// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Inventory.h"

#include <iostream>
#include <cassert>

namespace libol {
    Inventory Inventory::decode(Block& block) {
        assert(block.type == 0xFE);
        assert(block.size == 0x98);
        assert(block.content[0] == 0x0C);
        assert(block.content[1] == 0x01);

        Inventory items;

        auto stream = block.createStream(0x2);

        for(size_t i = 0; i < items.items.size(); i++) {
            stream.read(&items.items[i].itemId);
            stream.read(&items.items[i].slotId);
            stream.read(&items.items[i].quantity);
            stream.read(&items.items[i].charges);
        }

        for(size_t i = 0; i < items.items.size(); i++) {
            stream.read(&items.items[i].cooldown);
        }

        for(size_t i = 0; i < items.items.size(); i++) {
            stream.read(&items.items[i].baseCooldown);
        }

        return items;
    }
}
