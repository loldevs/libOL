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
    public:
        Header header;
        std::string metadata;
        PayloadHeader payloadHeader;
        std::vector<ChunkHeader> chunkHeaders;
        std::vector<ChunkHeader> keyframeHeaders;

        static File decode(std::ifstream& ifs);
    };
}

#endif /* defined(__lllib__File__) */
