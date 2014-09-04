// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__TurretHeader__
#define __libol__TurretHeader__

#include "Packet.h"

#include <cstdint>
#include <array>
#include <vector>
#include <string>

namespace libol {
    class TurretHeader : public Packet {
    public:
        uint32_t entityId;
        std::string name;
        bool isFountainLaser;
        bool isAttackable;

        TurretHeader(Block& block);
        static bool test(Block& block);
    };
}

#endif /* defined(__libol__TurretHeader__) */
