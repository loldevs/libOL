// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "KeyframeHeader.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool KeyframeHeader::test(Block& block) {
        return (
            (block.type == 0x61 || block.type == 0x62)
            && block.entityId == 0
            && block.size == 2
            && block.content[0] == 0x00
        );
    }

    KeyframeHeader::KeyframeHeader(Block& block) {
        test(block);
    }
}
