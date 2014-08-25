// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Turret__
#define __libol__Turret__

#include "Blocks/TurretHeader.h"
#include "Blocks/Inventory.h"

#include <cstdint>
#include <vector>


namespace libol {
    class Turret {
    public:
        uint32_t entityId;
        std::string name;
        bool isFountainLaser;
        bool isAttackable;
        std::array<Inventory::Item, 10> items;
    };
}

#endif /* defined(__libol__Turret__) */
