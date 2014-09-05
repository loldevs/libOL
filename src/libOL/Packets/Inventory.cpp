// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Inventory.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool Inventory(Block& block) {
        return (
            block.type == 0xFE
            && block.size == 0x98
            && block.content[0] == 0x0C
            && block.content[1] == 0x01
        );
    }

    Inventory::Inventory(Block& block) {
        entityId = block.entityId;
        
        auto stream = block.createStream(0x2);

        for(size_t i = 0; i < items.size(); i++) {
            stream.read(&items[i].itemId);
            stream.read(&items[i].slotId);
            stream.read(&items[i].quantity);
            stream.read(&items[i].charges);
        }

        for(size_t i = 0; i < items.size(); i++) {
            stream.read(&items[i].cooldown);
        }

        for(size_t i = 0; i < items.size(); i++) {
            stream.read(&items[i].baseCooldown);
        }
    }
}
