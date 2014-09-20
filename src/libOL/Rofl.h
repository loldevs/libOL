// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Rofl__
#define __libol__Rofl__

#include <cstdint>
#include <iostream>
#include <vector>

#include <libOL/ChunkHeader.h>
#include <libOL/Header.h>
#include <libOL/PayloadHeader.h>

#define ROFL_CHUNK_HEADER_LENGTH 17
#define ROFL_KEYFRAME_HEADER_LENGTH 17

namespace libol {
    class Rofl {
    public:
        Header header;
        std::string metadata;
        PayloadHeader payloadHeader;
        std::vector<ChunkHeader> chunkHeaders;
        std::vector<ChunkHeader> keyframeHeaders;

        void seekToChunk(std::ifstream& ifs, ChunkHeader chunkHeader);
        std::vector<uint8_t> getDecryptedChunk(std::ifstream& ifs, ChunkHeader chunkHeader);

        static Rofl decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__Rofl__) */
