// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__TowerHeader__
#define __libol__TowerHeader__

#include "Block.h"

#include <cstdint>
#include <array>
#include <vector>
#include <string>

namespace libol {
    class TowerHeader {
    public:
        uint32_t entityId;
        std::string name;
        bool isFountainLaser;
        bool isAttackable;

        static bool test(Block& block);
        static TowerHeader decode(Block& block);
    };
}

#endif /* defined(__libol__TowerHeader__) */
