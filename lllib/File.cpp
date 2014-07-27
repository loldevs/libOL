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

        return file;
    }
}