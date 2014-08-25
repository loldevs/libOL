// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "KeyframeHeader.h"

#include <iostream>
#include <cassert>

namespace libol {
    KeyframeHeader KeyframeHeader::decode(Block& block) {
        KeyframeHeader header;
        assert(block.type == 0x61 || block.type == 0x62);
        assert(block.time.isAbsolute);
        header.timestamp = block.time.absolute;
        assert(block.param.is32);
        assert(block.param.value32 == 0);
        assert(block.size == 2);
        assert(block.content[0] == 0x00);
        //assert(block.content[1] == 0x00); // 0x01 in custom game
        return header;
    }
}
