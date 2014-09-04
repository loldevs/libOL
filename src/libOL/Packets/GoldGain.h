// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__GoldGain__
#define __libol__GoldGain__

#include "Packet.h"

#include <cstdint>

namespace libol {
    class GoldGain : public Packet {
    public:
        uint32_t entityId;
        float amount;

        GoldGain(Block& block);
        static bool test(Block& block);
    };
}

#endif /* defined(__libol__GoldGain__) */
