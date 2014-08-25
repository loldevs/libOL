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

    Block::Stream Block::createStream(size_t offset) {
        Stream stream(*this, offset);
        return stream;
    }

    Block Block::decode(std::ifstream& ifs, Block* previous) {
        Block block;

        uint8_t marker = ifs.get();

        // Bit 1: Time format
        block.time.isAbsolute = !get_bit(marker, 0);
        if(block.time.isAbsolute) {
            ifs.read(reinterpret_cast<char*>(&block.time.absolute), sizeof(block.time.absolute));
        } else {
            block.time.diff = ifs.get();
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
            if(previous != nullptr) {
                block.type = previous->type;
            } else {
                std::cout << "typeless block as first block" << std::endl;
                exit(1);
            }
        }

        // Bit 3: Blockdata size
        block.param.is32 = !get_bit(marker, 2);
        if(block.param.is32) {
            ifs.read(reinterpret_cast<char*>(&block.param.value32), sizeof(block.param.value32));
        } else {
            block.param.value8 = ifs.get();
        }

        // Read content
        block.content.resize(block.size);
        ifs.read(reinterpret_cast<char*>(block.content.data()), block.size);

        return block;
    }
}
