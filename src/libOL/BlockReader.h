// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__BlockReader__
#define __libol__BlockReader__

#include "Block.h"

#include <vector>
#include <fstream>

namespace libol {
    class BlockReader {
        float lastTime;
        uint8_t lastType;
        uint32_t lastEntId;
        
        void processBlock(Block& block) {
            if (block.header.timeIsAbs) {
                lastTime = block.header.timeAbs;
            } else {
                lastTime += block.header.timeDiff / 1000.0;
            }
            block.time = lastTime;

            if (block.header.hasExplicitType) {
                lastType = block.header.type;
            }
            block.type = lastType;

            if (block.header.paramIs32) {
                lastEntId = block.header.param32;
            } else {
                lastEntId += block.header.param8;
            }
            block.entityId = lastEntId;
        }
    public:
        std::vector<Block> readBlocksFromStream(std::ifstream& ifs) {
            std::vector<Block> result;

             while (true) {
                Block block = Block::decode(ifs);
                ifs.peek(); // provoke eof
                if (!ifs.eof()) {
                    processBlock(block);
                    result.push_back(block);
                } else
                    break;
            }

            return result;
        }

    };
}

#endif /* defined(__libol__BlockReader__) */
