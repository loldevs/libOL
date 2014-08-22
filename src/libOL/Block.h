// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Block__
#define __libol__Block__

#include <cstdint>
#include <iostream>
#include <vector>

namespace libol {
    class Block {
    public:
        struct BlockTime {
            bool isAbsolute;
            float absolute;
            uint8_t diff;
        };

        struct BlockData { /* Maybe name this BlockParam */
            bool is32;
            uint8_t value8;
            uint32_t value32;
        };

        Block* headBlock;

        BlockTime time;
        uint32_t size;
        bool hasExplicitType;
        uint8_t type;
        BlockData data;

        std::vector<uint8_t> content;

        static Block decode(std::ifstream& ifs, Block* previous);
    };
}

#endif /* defined(__libol__Block__) */
