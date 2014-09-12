// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__AbilityLevel__
#define __libol__AbilityLevel__

#include "../Value.h"
#include "../Block.h"

#include <cstdint>

namespace libol {
    class AbilityLevel {
    public:
        uint32_t entityId;
        uint8_t abilityId;
        uint8_t level;

        static Value decode(Block& block);
        static bool test(Block& block);
    };
}

#endif /* defined(__libol__AbilityLevel__) */
