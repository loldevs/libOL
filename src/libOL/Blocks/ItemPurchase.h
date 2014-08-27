// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__ItemPurchase__
#define __libol__ItemPurchase__

#include "Block.h"

#include <cstdint>

namespace libol {
    class ItemPurchase {
    public:
        uint32_t entityId;
        uint32_t itemId;
        uint8_t slotId;
        uint16_t quantity;
        /* 40 */

        static bool test(Block& block);
        static ItemPurchase decode(Block& block);
    };
}

#endif /* defined(__libol__ItemPurchase__) */
