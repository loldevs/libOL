// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Keyframe__
#define __libol__Keyframe__

#include "Blocks/Block.h"
#include "Blocks/KeyframeHeader.h"
#include "Player.h"
#include "Turret.h"

#include <cstdint>
#include <vector>

namespace libol {
    class Keyframe {
    public:
        KeyframeHeader header;
        std::vector<Player> players;
        std::vector<Turret> turrets;

        static Keyframe decode(std::vector<Block>& blocks);
    };
}

#endif /* defined(__libol__Keyframe__) */
