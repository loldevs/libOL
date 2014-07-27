//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#ifndef __lllib__PayloadHeader__
#define __lllib__PayloadHeader__

#include <cstdint>
#include <vector>

namespace lllib {
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
        std::vector<uint8_t> encryptionKey;

        static PayloadHeader decode(std::ifstream& ifs);
    };
}

#endif /* defined(__lllib__PayloadHeader__) */
