// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Block.h"

#include <fstream>
#include <cassert>
#include <cstring>

namespace libol {
    bool get_bit(uint8_t byte, int n) {
        return (byte >> (7 - n)) & 1;
    }

    Block Block::decode(std::ifstream& ifs, Block* previous) {
        Block block;

        block.headBlock = previous; // TODO: seek explicitly typed block

        uint8_t marker = ifs.get();

        if(
            get_bit(marker, 4)
            || get_bit(marker, 5)
            || !get_bit(marker, 6)
            || !get_bit(marker, 7)
        ) std::cout << "unexpected marker bit" << std::endl;

        // Bit 1: Time format
        block.time.isAbsolute = get_bit(marker, 0);
        if(block.time.isAbsolute) {
            block.time.diff = ifs.get();
        } else {
            ifs.read(reinterpret_cast<char*>(&block.time.absolute), sizeof(block.time.absolute));
        }

        // Bit 4: Size size
        if(get_bit(marker, 3)) {
            block.size = (unsigned) ifs.get();
        } else {
            ifs.read(reinterpret_cast<char*>(&block.size), sizeof(block.size));
        }

        // Bit 2: Has type
        block.hasExplicitType = !get_bit(marker, 1);
        if(block.hasExplicitType) {
            block.type = ifs.get();
        } else {
            if(block.headBlock != nullptr) {
                block.type = block.headBlock.type;
            } else {
                std::cout << "no headBlock on typeless block" << std::endl;
                exit(1);
            }
        }

        // Bit 3: Blockdata size
        block.data.is32 = !get_bit(marker, 2);
        if(block.data.is32) {
            ifs.read(reinterpret_cast<char*>(&block.data.value32), sizeof(block.data.value32));
        } else {
            block.data.value8 = ifs.get();
        }

        // Read content
        block.content.resize(block.size);
        ifs.read(reinterpret_cast<char*>(block.content.data()), block.size);

        return block;
    }
}
