// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__MasteryEntry__
#define __libol__MasteryEntry__

#include <cstdint>
#include <iostream>

namespace libol {
    class MasteryEntry {
    public:
        uint8_t id;
        uint8_t tree;
        /* 03 00 */
        uint8_t pointsSpent;
        
        static bool probe(std::ifstream& ifs);
        static MasteryEntry decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__MasteryEntry__) */
