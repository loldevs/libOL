// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PayloadHeader__
#define __libol__PayloadHeader__

#include <cstdint>
#include <iostream>
#include <vector>

namespace libol {
    class PayloadHeader {
    public:
        uint64_t gameId;
        uint32_t gameLength;
        uint32_t keyframeCount;
        uint32_t chunkCount;
        uint32_t endStartupChunkId;
        uint32_t startGameChunkId;
        uint32_t keyframeInterval;
        uint16_t encryptionKeyLength;
        std::string encryptionKey;

        std::vector<uint8_t> getDecodedEncryptionKey();

        static PayloadHeader decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__PayloadHeader__) */
