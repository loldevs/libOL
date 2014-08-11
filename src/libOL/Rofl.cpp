// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Rofl.h"

#include <fstream>

#include "Chunks.h"

namespace libol {
    Rofl Rofl::decode(std::ifstream& ifs) {
        Rofl file;

        // Header
        file.header = Header::decode(ifs);

        // Metadata
        ifs.seekg(file.header.metadataOffset);
        file.metadata.resize(file.header.metadataLength);
        ifs.read(reinterpret_cast<char *>(&file.metadata[0]), file.header.metadataLength);

        // Payload Header
        ifs.seekg(file.header.payloadHeaderOffset);
        file.payloadHeader = PayloadHeader::decode(ifs);

        // Chunk and Keyframe headers
        ifs.seekg(file.header.payloadHeaderOffset + file.header.payloadHeaderLength);
        file.chunkHeaders = ChunkHeader::decodeMultiple(ifs, file.payloadHeader.chunkCount);
        file.keyframeHeaders = ChunkHeader::decodeMultiple(ifs, file.payloadHeader.keyframeCount);

        return file;
    }

    void Rofl::seekToChunk(std::ifstream& ifs, ChunkHeader chunkHeader) {
        ifs.seekg(header.payloadOffset +
                  payloadHeader.chunkCount * 17 +
                  payloadHeader.keyframeCount  * 17 +
                  chunkHeader.offset);
    }

    std::vector<uint8_t> Rofl::getDecryptedChunk(std::ifstream& ifs, ChunkHeader chunkHeader) {
        std::vector<uint8_t> chunk;
        chunk.resize(chunkHeader.chunkLength);

        seekToChunk(ifs, chunkHeader);
        ifs.read(reinterpret_cast<char *>(&chunk[0]), chunkHeader.chunkLength);

        auto decryptionKey = payloadHeader.getDecodedEncryptionKey();
        auto decrypted = libol::Chunks::decryptAndDecompress(chunk, decryptionKey);
        return decrypted;
    }

}