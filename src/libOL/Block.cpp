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

    Block Block::decode(std::ifstream& ifs) {
        Block block;

        block.offset = ifs.tellg();

        block.header.marker = ifs.get();

        // Bit 1: Time format
        block.header.timeIsAbs = !get_bit(block.header.marker, 0);
        if(block.header.timeIsAbs) {
            ifs.read(reinterpret_cast<char*>(&block.header.timeAbs), sizeof(block.header.timeAbs));
        } else {
            block.header.timeDiff = ifs.get();
        }

        // Bit 4: Size size
        block.header.sizeIs32 = !get_bit(block.header.marker, 3);
        if(block.header.sizeIs32) {
            ifs.read(reinterpret_cast<char*>(&block.header.size32), sizeof(block.header.size32));
            block.size = block.header.size32;
        } else {
            block.header.size8 = ifs.get();
            block.size = (unsigned) block.header.size8;
        }

        // Bit 2: Has type
        block.header.hasExplicitType = !get_bit(block.header.marker, 1);
        if(block.header.hasExplicitType) {
            block.header.type = ifs.get();
        }

        // Bit 3: Blockdata size
        block.header.paramIs32 = !get_bit(block.header.marker, 2);
        if(block.header.paramIs32) {
            ifs.read(reinterpret_cast<char*>(&block.header.param32), sizeof(block.header.param32));
        } else {
            block.header.param8 = ifs.get();
        }

        // Read content
        block.content.resize(block.size);
        ifs.read(reinterpret_cast<char*>(block.content.data()), block.size);

        return block;
    }

    std::vector<Block> Block::readBlocksFromStream(std::ifstream& ifs) {
        std::vector<Block> result;

        while(true) {
            Block block = Block::decode(ifs);
            ifs.peek(); // provoke eof
            if(!ifs.eof())
                result.push_back(block);
            else
                break;
        }

        float gametime = 0;
        uint8_t currType;
        uint32_t currEntityId;

        for(auto& block : result) {
            if(block.header.timeIsAbs) {
                gametime = block.header.timeAbs;
            } else {
                gametime += block.header.timeDiff / 1000.0;
            }
            block.time = gametime;

            if(block.header.hasExplicitType) {
                currType = block.header.type;
            }
            block.type = currType;

            if(block.header.paramIs32) {
                currEntityId = block.header.param32;
            } else {
                currEntityId += block.header.param8;
            }
            block.entityId = currEntityId;
        }

        return result;
    }
}
