// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__KeyframeHeader__
#define __libol__KeyframeHeader__

#include "Packet.h"

#include <cstdint>
#include <array>

namespace libol {
    class KeyframeHeader : public Packet {
    public:
        KeyframeHeader(Block& block);
        static bool test(Block& block);
    };
}

#endif /* defined(__libol__KeyframeHeader__) */
