//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#ifndef __lllib__PayloadHeader__
#define __lllib__PayloadHeader__

#include <cstdint>
#include <vector>

namespace lllib {
    class PayloadHeader {
    public:
        int64_t gameId;
        int32_t gameLength;
        int32_t keyframeCount;
        int32_t chunkCount;
        int32_t endStartupChunkId;
        int32_t startGameChunkId;
        int32_t keyframeInterval;
        int16_t encryptionKeyLength;
        std::vector<uint8_t> encryptionKey;
    };
}

#endif /* defined(__lllib__PayloadHeader__) */
