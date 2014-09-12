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

    Value AbilityLevel::decode(Block& block) {
        Object data = Object();

        data.setv("abilityId", block.content[0]);
        data.setv("level", block.content[1]);

        assert(block.content[2] == 0x00);

        return Value::create(data);
    }
}
