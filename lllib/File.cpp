//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include "File.h"

#include <fstream>

namespace lllib {
    File File::decode(std::ifstream& ifs) {
        File file;

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
}