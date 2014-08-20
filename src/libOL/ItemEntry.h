// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__ItemEntry__
#define __libol__ItemEntry__

#include <cstdint>
#include <iostream>

namespace libol {
    class ItemEntry {
    public:
        uint16_t itemId;
        /* 00 00 */
        uint8_t slotId;
        uint8_t quantity;
        uint8_t charges;

        static ItemEntry decode(std::ifstream& ifs);

        float cooldown;
        void decodeCooldown(std::ifstream& ifs);

        float baseCooldown;
        void decodeBaseCooldown(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__ItemEntry__) */
