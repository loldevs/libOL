// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__ChunkHeader__
#define __libol__ChunkHeader__

#include <cstdint>
#include <iostream>
#include <vector>

namespace libol {
    class ChunkHeader {
    public:
        int32_t chunkId;
        uint8_t chunkType;
        int32_t chunkLength;
        int32_t nextChunkId;
        int32_t offset;

        static std::vector<ChunkHeader> decodeMultiple(std::ifstream& ifs, int count);
        static ChunkHeader decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__ChunkHeader__) */
