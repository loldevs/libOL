// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "ItemPurchase.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool ItemPurchase::test(Block& block) {
        return (
            block.type == 0x6F
            && block.size == 0x8
        );
    }

    ItemPurchase ItemPurchase::decode(Block& block) {
        assert(test(block));

        ItemPurchase entry;
        entry.entityId = block.entityId;

        auto stream = block.createStream();

        stream.read(&entry.itemId);
        stream.read(&entry.slotId);
        stream.read(&entry.quantity);

        assert(block.content[0x7] == 0x40);

        return entry;
    }
}
