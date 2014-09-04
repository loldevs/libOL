// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "AbilityLevel.h"

#include <cassert>

namespace libol {
    bool AbilityLevel::test(Block& block) {
        return (
            block.type == 0x15
            && block.size == 0x3
        );
    }

    AbilityLevel::AbilityLevel(Block& block) {
        entityId = block.entityId;
        abilityId = block.content[0];
        level = block.content[1];
        assert(block.content[3] == 0x00);
    }
}
