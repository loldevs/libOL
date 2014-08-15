// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "KeyframeHeader.h"

#include <fstream>
#include <assert.h>
#include <cstring>

namespace libol {
    KeyframeHeader KeyframeHeader::decode(std::ifstream& ifs) {
        KeyframeHeader header;
        ifs.read(reinterpret_cast<char *>(&header.start), sizeof(header.start));
        assert(header.start == 0x03);
        ifs.read(reinterpret_cast<char *>(&header.timestamp), sizeof(header.timestamp));
        ifs.read(reinterpret_cast<char *>(header.unk0.data()), header.unk0.size());
        std::array<uint8_t, 11> unk0_ref {{
            0x02, 0x00, 0x00,
            0x00, 0x62 /* 0x61 in wiki */, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00
        }};
        assert(!memcmp((void*) header.unk0.data(), (void*) unk0_ref.data(), sizeof(unk0_ref)));
        return header;
    }
}
