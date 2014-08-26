// Copyright (c) 2014 Luke Granger-Brown.
// Distributed under the MIT License.

#ifndef __libol__Blowfish__
#define __libol__Blowfish__

#include <vector>
#include <cstdint>

namespace libol {
    namespace Blowfish {
        std::vector<uint8_t> decrypt(std::vector<uint8_t> bytes, std::vector<uint8_t> key);
        std::vector<uint8_t> encrypt(std::vector<uint8_t> bytes, std::vector<uint8_t> key);
    }
}

#endif /* defined(__libol__Blowfish__) */
