//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#ifndef __lllib__File__
#define __lllib__File__

#include <iostream>
#include <vector>

#include "ChunkHeader.h"
#include "Header.h"
#include "PayloadHeader.h"

namespace lllib {
    class File {
    private:
        std::ifstream& _ifs;
    public:
        Header header;
        std::string metadata;
        PayloadHeader payloadHeader;
        std::vector<ChunkHeader> chunkHeaders;
        std::vector<ChunkHeader> payloadHeaders;

        File(std::ifstream&);
    };
}

#endif /* defined(__lllib__File__) */
