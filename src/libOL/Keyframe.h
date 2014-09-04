// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Keyframe__
#define __libol__Keyframe__

#include "Block.h"
#include "PacketReader.h"
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

        Keyframe(std::vector<Block>& blocks);
    };
}

#endif /* defined(__libol__Keyframe__) */
