// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Keyframe__
#define __libol__Keyframe__

#include <cstdint>
#include <iostream>
#include <vector>

#include <libOL/KeyframeHeader.h>
#include <libOL/PlayerSegment.h>

namespace libol {
    class Keyframe {
    public:
        KeyframeHeader header;
        std::vector<PlayerSegment> players;
        /* Turret segments */
        /* unknown data */

        static Keyframe decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__Keyframe__) */
