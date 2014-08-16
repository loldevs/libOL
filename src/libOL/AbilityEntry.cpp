// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "AbilityEntry.h"

#include <fstream>
#include <cassert>
#include <cstring>

namespace libol {
    AbilityEntry AbilityEntry::decode(std::ifstream& ifs) {
        AbilityEntry entry;

        uint8_t byte = ifs.get();
        assert(byte == 0x00);
        entry.abilityId = ifs.get();
        entry.level = ifs.get();
        byte = ifs.get();
        //assert(byte == 0x00);
        
        byte = ifs.peek();
        switch(byte) {
            case 0xF3:
            case 0xB3:
                ifs.ignore(3);
                break;
            case 0x73:
            case 0x33:
                ifs.ignore(6);
                break;
            default:
                std::cout << "unkown ability format @ " << std::hex << ifs.tellg() << std::endl;
                exit(1);
        }

        return entry;
    }
}
