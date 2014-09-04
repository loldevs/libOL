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

    ExpGain::ExpGain(Block& block) {
        auto stream = block.createStream();

        stream.read(&entityId);
        stream.read(&victim);
        stream.read(&amount);
    }
}
