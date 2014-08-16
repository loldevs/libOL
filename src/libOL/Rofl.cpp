// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Rofl.h"

#include <fstream>
#include <glog/logging.h>

#include "Chunks.h"

namespace libol {
    Rofl Rofl::decode(std::ifstream& ifs) {
        Rofl file;

        // Header
	DLOG(INFO) << "Decoding ROFL header";
        file.header = Header::decode(ifs);

        // Metadata
	DLOG(INFO) << "Reading metadata @ " << file.header.metadataOffset << " len " << file.header.metadataLength;
        ifs.seekg(file.header.metadataOffset);
        file.metadata.resize(file.header.metadataLength);
        ifs.read(reinterpret_cast<char *>(&file.metadata[0]), file.header.metadataLength);

        // Payload Header
	DLOG(INFO) << "Reading payload header @ " << file.header.payloadHeaderOffset; 
        ifs.seekg(file.header.payloadHeaderOffset);
        file.payloadHeader = PayloadHeader::decode(ifs);

        // Chunk and Keyframe headers
	DLOG(INFO) << "Reading chunk/keyframe headers @ " << (file.header.payloadHeaderOffset + file.header.payloadHeaderLength);
        ifs.seekg(file.header.payloadHeaderOffset + file.header.payloadHeaderLength);
	DLOG(INFO) << "Reading " << file.payloadHeader.chunkCount << " chunk headers";
        file.chunkHeaders = ChunkHeader::decodeMultiple(ifs, file.payloadHeader.chunkCount);
	DLOG(INFO) << "Reading " << file.payloadHeader.keyframeCount << " keyframe headers";
        file.keyframeHeaders = ChunkHeader::decodeMultiple(ifs, file.payloadHeader.keyframeCount);

	DLOG(INFO) << "Done decoding ROFL";

        return file;
    }

    void Rofl::seekToChunk(std::ifstream& ifs, ChunkHeader chunkHeader) {
        ifs.seekg(header.payloadOffset +
                  payloadHeader.chunkCount * ROFL_CHUNK_HEADER_LENGTH +
                  payloadHeader.keyframeCount  * ROFL_KEYFRAME_HEADER_LENGTH +
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
