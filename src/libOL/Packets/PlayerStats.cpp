// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "PlayerStats.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool PlayerStats::test(Block& block) {
        return (
            block.type == 0x46
            && (block.size == 0x128 || block.size == 0x120)
            && (block.content[0] == 0x28 || block.content[0] == 0x20)
            && block.content[1] == 0x01
            && block.content[2] == 0x00
            && block.content[3] == 0x00
        );
    }

    PlayerStats::PlayerStats(Block& block) {
        if(block.size == 0x128) // TODO: read no jungle maps
            block.read(&stats, 0x4);
    }
}
