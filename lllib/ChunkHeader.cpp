//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include "ChunkHeader.h"

#include <fstream>

namespace lllib {

    inline void decodeInPlace(std::ifstream& ifs, ChunkHeader& header) {
        ifs.read(reinterpret_cast<char *>(&header.chunkId), sizeof(header.chunkId));
        ifs.read(reinterpret_cast<char *>(&header.chunkType), sizeof(header.chunkType));
        ifs.read(reinterpret_cast<char *>(&header.chunkLength), sizeof(header.chunkLength));
        ifs.read(reinterpret_cast<char *>(&header.nextChunkId), sizeof(header.nextChunkId));
        ifs.read(reinterpret_cast<char *>(&header.offset), sizeof(header.offset));
    }

    std::vector<ChunkHeader> ChunkHeader::decodeMultiple(std::ifstream& ifs, int count) {
        auto headers = std::vector<ChunkHeader>(count);
        for (int i = 0; i < count; i++) {
            lllib::decodeInPlace(ifs, headers[i]);
        }
        return headers;
    }

    ChunkHeader ChunkHeader::decode(std::ifstream& ifs) {
        ChunkHeader chunkHeader;
        lllib::decodeInPlace(ifs, chunkHeader);
        return chunkHeader;
    }
}