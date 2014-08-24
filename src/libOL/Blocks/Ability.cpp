// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Ability.h"

#include <iostream>
#include <cassert>

namespace libol {
    Ability Ability::decode(Block& block) {
        assert(block.type == 0x15);
        assert(block.size == 0x3);

        Ability entry;

        entry.abilityId = block.content[0];
        entry.level = block.content[1];
        assert(block.content[3] == 0x00);

        return entry;
    }
}
