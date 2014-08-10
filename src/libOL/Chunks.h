// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Chunks__
#define __libol__Chunks__

#include <vector>
#include <cstdint>

namespace libol {
    namespace Chunks {
        std::vector<uint8_t> decryptAndDecompress(std::vector<uint8_t> bytes, std::vector<uint8_t> key);
    }
}

#endif /* defined(__libol__Chunks__) */
