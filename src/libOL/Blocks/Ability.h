// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Ability__
#define __libol__Ability__

#include "Block.h"

#include <cstdint>

namespace libol {
    class Ability {
    public:
        uint8_t abilityId;
        uint8_t level;
        /* 00 */

        static Ability decode(Block& block);
    };
}

#endif /* defined(__libol__Ability__) */
