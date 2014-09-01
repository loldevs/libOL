// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__AbilityLevel__
#define __libol__AbilityLevel__

#include "Block.h"

#include <cstdint>

namespace libol {
    class AbilityLevel {
    public:
        uint8_t abilityId;
        uint8_t level;
        /* 00 */

        static AbilityLevel decode(Block& block);
    };
}

#endif /* defined(__libol__AbilityLevel__) */
