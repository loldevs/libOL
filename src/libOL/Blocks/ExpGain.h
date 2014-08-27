// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__ExpGain__
#define __libol__ExpGain__

#include "Block.h"

#include <cstdint>

namespace libol {
    class ExpGain {
    public:
        uint32_t entityId;
        uint32_t victim;
        float amount;

        static bool test(Block& block);
        static ExpGain decode(Block& block);
    };
}

#endif /* defined(__libol__ExpGain__) */
