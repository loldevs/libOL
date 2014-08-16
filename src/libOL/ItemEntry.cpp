// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "ItemEntry.h"

#include <fstream>
#include <cassert>
#include <cstring>

namespace libol {
    ItemEntry ItemEntry::decode(std::ifstream& ifs) {
        ItemEntry entry;

        ifs.read(reinterpret_cast<char *>(&entry.itemId), sizeof(entry.itemId));
        assert(ifs.get() == 0x00);
        assert(ifs.get() == 0x00);
        entry.slotId = ifs.get();
        entry.quantity = ifs.get();
        entry.charges = ifs.get();

        return entry;
    }

    void ItemEntry::decodeCooldown(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char *>(&this->cooldown), sizeof(this->cooldown));
    }
}
