// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "GoldGain.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool GoldGain::test(Block& block) {
        return (
            block.type == 0xE4
            && block.size == 0x8
        );
    }

    GoldGain GoldGain::decode(Block& block) {
        assert(test(block));

        GoldGain msg;

        auto stream = block.createStream();

        stream.read(&msg.entityId);
        stream.read(&msg.amount);

        return msg;
    }
}
