// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "TowerHeader.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool TowerHeader::test(Block& block) {
        return (
            block.type == 0x9D
            && block.size == 0x4A
        );
    }

    TowerHeader TowerHeader::decode(Block& block) {
        assert(test(block));

        TowerHeader tower;

        auto stream = block.createStream();

        stream.read(&tower.entityId);

        uint8_t byte;
        stream.read(&byte);
        assert(byte == 0x40);

        // Tower name
        char nameChars[0x41];
        stream.read(nameChars, 0x40);
        nameChars[0x40] = 0x00;
        tower.name = nameChars;

        uint32_t type;
        stream.read(&type);
        if(type == 0x2) {
            tower.isFountainLaser = false;
        } else {
            assert(type == 0x80000000);
            tower.isFountainLaser = true;
        }

        uint8_t attackable;
        stream.read(&attackable);
        if(attackable == 0x1) {
            tower.isAttackable = false;
        } else {
            assert(attackable == 0x2);
            tower.isAttackable = true;
        }

        return tower;
    }
}
