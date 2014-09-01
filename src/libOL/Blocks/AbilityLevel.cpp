// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "AbilityLevel.h"

#include <iostream>
#include <cassert>

namespace libol {
    AbilityLevel AbilityLevel::decode(Block& block) {
        assert(block.type == 0x15);
        assert(block.size == 0x3);

        AbilityLevel entry;

        entry.abilityId = block.content[0];
        entry.level = block.content[1];
        assert(block.content[3] == 0x00);

        return entry;
    }
}
