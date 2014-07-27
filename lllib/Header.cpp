//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include "Header.h"

#include <fstream>

namespace lllib {
    Header Header::decode(std::ifstream& ifs) {
        Header header;
        ifs.read(reinterpret_cast<char *>(header.magic.data()), header.magic.size());
        ifs.read(reinterpret_cast<char *>(header.signature.data()), header.signature.size());
        ifs.read(reinterpret_cast<char *>(&header.headerlength), sizeof(header.headerlength));
        ifs.read(reinterpret_cast<char *>(&header.fileLength), sizeof(header.fileLength));
        ifs.read(reinterpret_cast<char *>(&header.metadataOffset), sizeof(header.metadataOffset));
        ifs.read(reinterpret_cast<char *>(&header.metadataLength), sizeof(header.metadataLength));
        ifs.read(reinterpret_cast<char *>(&header.payloadHeaderOffset), sizeof(header.payloadHeaderOffset));
        ifs.read(reinterpret_cast<char *>(&header.payloadHeaderLength), sizeof(header.payloadHeaderLength));
        ifs.read(reinterpret_cast<char *>(&header.payloadOffset), sizeof(header.payloadOffset));
        return header;
    }
}