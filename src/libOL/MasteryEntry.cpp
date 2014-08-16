// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "MasteryEntry.h"

#include <fstream>
#include <cassert>
#include <cstring>

namespace libol {
    bool MasteryEntry::probe(std::ifstream& ifs) {
        auto pos = ifs.tellg();
        ifs.ignore(2);
        uint8_t test = ifs.get();
        ifs.seekg(pos);

        return test == 0x03;
    }

    MasteryEntry MasteryEntry::decode(std::ifstream& ifs) {
        MasteryEntry entry;

        entry.id = ifs.get();
        entry.tree = ifs.get();
        uint8_t byte = ifs.get();
        assert(byte == 0x03);
        byte = ifs.get();
        assert(byte == 0x00);
        ifs.read(reinterpret_cast<char *>(&entry.pointsSpent), sizeof(entry.pointsSpent));

        return entry;
    }
}