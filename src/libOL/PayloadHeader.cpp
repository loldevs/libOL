// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "PayloadHeader.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Blowfish/Blowfish.h"

static inline std::vector<uint8_t> b64Decode(std::string const& input) {
    if (input.length() == 0) {
        return std::vector<uint8_t>();
    }
    assert(input.length() % 4 == 0);

    size_t padding = 0;
    if (input[input.size() - 1] == '=') {
        padding++;
    }
    if (input[input.size() - 1] == '=') {
        padding++;
    }

    std::vector<uint8_t> result;
    result.reserve(3 * (input.length() / 4) - padding);

    int decodedBytes = 0;
    uint32_t bytes = 0;
    for (auto cursor = input.begin(); cursor < input.end(); cursor++) {
        char character = *cursor;
        if (character >= 'A' && character <= 'Z') {
            bytes |= character - 'A';
        } else if (character >= 'a' && character <= 'z') {
            bytes |= character - 'a' + 26;
        } else if (character >= '0' && character <= '9') {
            bytes |= character - '0' + 52;
        } else if (character == '+') {
            bytes |= 62;
        } else if (character == '/') {
            bytes |= 63;
        } else if (character == '=') {
            auto fromEnd = input.end() - cursor;
            if (fromEnd == 1) {
                result.push_back((bytes >> 16) & 0xff);
                result.push_back((bytes >> 8) & 0xff);
                return result;
            } else if (fromEnd == 2) {
                result.push_back((bytes >> 10) & 0xff);
                return result;
            }
        }

        if (decodedBytes == 3) {
            result.push_back((bytes >> 16) & 0xff);
            result.push_back((bytes >> 8) & 0xff);
            result.push_back((bytes) & 0xff);
            bytes = 0;
        }

        decodedBytes = (decodedBytes + 1) % 4;
        bytes <<= 6;
    }

    return result;
}

namespace libol {
    std::vector<uint8_t> PayloadHeader::getDecodedEncryptionKey() {
        auto encryptedKeyBytes = b64Decode(this->encryptionKey);

        auto gameIdStr = std::to_string(gameId);
        auto gameIdVec = std::vector<uint8_t>{gameIdStr.begin(), gameIdStr.end()};

        std::vector<uint8_t> out = Blowfish::decrypt(encryptedKeyBytes, gameIdVec);

        return out;
    }

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
