// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__KeyframeHeader__
#define __libol__KeyframeHeader__

#include "Block.h"

#include <cstdint>
#include <array>

namespace libol {
    class KeyframeHeader {
    public:
    	float timestamp;

        static KeyframeHeader decode(Block& block);
    };
}

#endif /* defined(__libol__KeyframeHeader__) */
