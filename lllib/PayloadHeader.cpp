//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include "PayloadHeader.h"

#include <fstream>

namespace lllib {
    PayloadHeader PayloadHeader::decode(std::ifstream& ifs) {
        PayloadHeader payloadHeader;
        ifs.read(reinterpret_cast<char *>(&payloadHeader.gameId), sizeof(payloadHeader.gameId));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.gameLength), sizeof(payloadHeader.gameLength));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.keyframeCount), sizeof(payloadHeader.keyframeCount));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.chunkCount), sizeof(payloadHeader.chunkCount));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.endStartupChunkId), sizeof(payloadHeader.endStartupChunkId));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.startGameChunkId), sizeof(payloadHeader.startGameChunkId));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.keyframeInterval), sizeof(payloadHeader.keyframeInterval));
        ifs.read(reinterpret_cast<char *>(&payloadHeader.encryptionKeyLength), sizeof(payloadHeader.encryptionKeyLength));

        payloadHeader.encryptionKey.resize(payloadHeader.encryptionKeyLength);
        ifs.read(reinterpret_cast<char *>(&payloadHeader.encryptionKey[0]), payloadHeader.encryptionKeyLength);
        return payloadHeader;
    }
}