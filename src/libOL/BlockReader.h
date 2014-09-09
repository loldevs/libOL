// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__BlockReader__
#define __libol__BlockReader__

#include "Block.h"

#include <vector>
#include <ifstream>

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
                lastEntID = block.header.param32;
            } else {
                lastEntID += block.header.param8;
            }
            block.entityId = lastEntID;
        }
    public:
        std::vector<Block> readBlocksFromStream(std::ifstream& ifs) {
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
