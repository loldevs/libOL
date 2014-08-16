// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__AbilityEntry__
#define __libol__AbilityEntry__

#include <cstdint>
#include <iostream>

namespace libol {
    class AbilityEntry {
    public:
        /* 00 */
        uint8_t abilityId;
        uint8_t level;
        /* 00 */

        /* unknown data of different size */

        static AbilityEntry decode(std::ifstream& ifs);
    };
}

#endif /* defined(__libol__AbilityEntry__) */
