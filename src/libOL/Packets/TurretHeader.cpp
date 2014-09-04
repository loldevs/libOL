// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "TurretHeader.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool TurretHeader::test(Block& block) {
        return (
            block.type == 0x9D
            && block.size == 0x4A
        );
    }

    TurretHeader::TurretHeader(Block& block) {
        auto stream = block.createStream();

        stream.read(&entityId);

        uint8_t byte;
        stream.read(&byte);
        assert(byte == 0x40);

        // Turret name
        char nameChars[0x41];
        stream.read(nameChars, 0x40);
        nameChars[0x40] = 0x00;
        name = nameChars;

        uint32_t type;
        stream.read(&type);
        if(type == 0x2) {
            isFountainLaser = false;
        } else {
            assert(type == 0x80000000);
            isFountainLaser = true;
        }

        uint8_t attackable;
        stream.read(&attackable);
        if(attackable == 0x1) {
            isAttackable = false;
        } else {
            assert(attackable == 0x2);
            isAttackable = true;
        }
    }
}
