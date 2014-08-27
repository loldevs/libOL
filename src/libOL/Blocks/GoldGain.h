// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__GoldGain__
#define __libol__GoldGain__

#include "Block.h"

#include <cstdint>

namespace libol {
    class GoldGain {
    public:
        uint32_t entityId;
        float amount;

        static bool test(Block& block);
        static GoldGain decode(Block& block);
    };
}

#endif /* defined(__libol__GoldGain__) */
