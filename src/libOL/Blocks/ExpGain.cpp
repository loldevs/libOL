// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "ExpGain.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool ExpGain::test(Block& block) {
        return (
            block.type == 0x22
            && block.size == 0xc
        );
    }

    ExpGain ExpGain::decode(Block& block) {
        assert(test(block));

        ExpGain msg;

        auto stream = block.createStream();

        stream.read(&msg.entityId);
        stream.read(&msg.victim);
        stream.read(&msg.amount);

        return msg;
    }
}
