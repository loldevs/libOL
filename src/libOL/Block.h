// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Block__
#define __libol__Block__

#include <cstdint>
#include <cassert>
#include <iostream>
#include <vector>
#include <cstring>

namespace libol {
    class Block {
    public:
        size_t offset;

        struct BlockHeader {
            uint8_t marker;

            bool timeIsAbs;
            float timeAbs;
            uint8_t timeDiff;

            bool sizeIs32;
            uint8_t size8;
            uint32_t size32;

            bool hasExplicitType;
            uint8_t type;

            bool paramIs32;
            uint8_t param8;
            uint32_t param32;
        };

        BlockHeader header;

        float time;
        uint8_t type;
        uint32_t entityId; // (?)
        uint32_t size;

        std::vector<uint8_t> content;

        template<class T>
        void read(T* dest, size_t offset) {
            assert(offset + sizeof(T) <= this->size);
            memcpy(dest, this->content.data() + offset, sizeof(T));
        }
        template<class T>
        void read(T* dest, size_t offset, size_t count) {
            size_t length = count * sizeof(T);
            assert(offset + length <= this->size);
            memcpy(dest, this->content.data() + offset, length);
        }

        class Stream {
            Block& block;
            size_t pos;
        public:
            Stream(Block& block, size_t pos = 0) :
                block(block),
                pos(pos)
            {} 

            size_t tellg() { return pos; }
            void seekg(size_t offset) { pos = offset; }
            void ignore(size_t bytes) { pos += bytes; }
            uint8_t get() { uint8_t data; read(&data); return data; }

            template<class T>
            void read(T* dest) {
                this->block.read(dest, pos);
                pos += sizeof(T);
            }
            template<class T>
            void read(T* dest, size_t count){
                this->block.read(dest, pos, count);
                pos += sizeof(T) * count;
            }
        };

        Stream createStream(size_t offset = 0);

        static Block decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__Block__) */
