// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Block.h"
#include "ParseException.h"

#include <fstream>
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

        block.channel = block.header.marker & 0xf;

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

    Block Block::decode(uint8_t* buf, size_t& pos, size_t len) {
        Block block;

        block.offset = pos;

        REQUIRE(pos + 1 <= len);
        block.header.marker = buf[pos++];

        block.channel = block.header.marker & 0xf;

        // Bit 1: Time format
        block.header.timeIsAbs = !get_bit(block.header.marker, 0);
        if(block.header.timeIsAbs) {
            REQUIRE(pos + 4 <= len);
            memcpy(&block.header.timeAbs, buf + pos, sizeof(block.header.timeAbs));
            pos += 4;
        } else {
            REQUIRE(pos + 1 <= len);
            block.header.timeDiff = buf[pos++];
        }

        // Bit 4: Size size
        block.header.sizeIs32 = !get_bit(block.header.marker, 3);
        if(block.header.sizeIs32) {
            REQUIRE(pos + 4 <= len);
            memcpy(&block.header.size32, buf + pos, sizeof(block.header.size32));
            pos += 4;
            block.size = block.header.size32;
        } else {
            REQUIRE(pos + 1 <= len);
            block.header.size8 = buf[pos++];
            block.size = (unsigned) block.header.size8;
        }

        // Bit 2: Has type
        block.header.hasExplicitType = !get_bit(block.header.marker, 1);
        if(block.header.hasExplicitType) {
            REQUIRE(pos + 1 < len);
            block.header.type = buf[pos++];
        }

        // Bit 3: Blockdata size
        block.header.paramIs32 = !get_bit(block.header.marker, 2);
        if(block.header.paramIs32) {
            REQUIRE(pos + 4 <= len);
            memcpy(&block.header.param32, buf + pos, sizeof(block.header.param32));
            pos += 4;
        } else {
            REQUIRE(pos + 1 <= len);
            block.header.param8 = buf[pos++];
        }

        // Read content
        block.content.resize(block.size);
        REQUIRE(pos + block.size <= len);
        memcpy(block.content.data(), buf + pos, block.size);
        pos += block.size;

        return block;
    }
}
