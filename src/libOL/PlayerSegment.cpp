// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "PlayerSegment.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace libol {
    bool PlayerSegment::probe(std::ifstream& ifs) {
        auto pos = ifs.tellg();
        ifs.ignore(2);
        uint8_t test = ifs.get();
        ifs.seekg(pos);

        return test == 0xC3;
    }

    PlayerSegment PlayerSegment::decode(std::ifstream& ifs) {
        PlayerSegment player;

        // Header
        ifs.read(reinterpret_cast<char *>(player.header.data()), player.header.size());

        // Summoner name
        char summonerChars[0x81];
        ifs.read(summonerChars, 0x80);
        summonerChars[0x80] = 0x00;
        player.summonerName = summonerChars;

        // Champion name
        char championChars[0x11];
        ifs.read(championChars, 0x10);
        summonerChars[0x10] = 0x00;
        player.championName = championChars;

        // Unknown 0
        ifs.read(reinterpret_cast<char *>(player.unk0.data()), player.unk0.size());

        // Runes
        ifs.read(reinterpret_cast<char *>(player.runes.data()), player.runes.size() * 4);

        // Masteries
        ifs.read(reinterpret_cast<char *>(player.masteriesHeader.data()), player.masteriesHeader.size());
        auto pos = ifs.tellg();
        int masteryCount = 0;
        while(MasteryEntry::probe(ifs) && masteryCount < 79) {
            player.masteries.push_back(MasteryEntry::decode(ifs));
            masteryCount++;
        }
        ifs.seekg(pos);
        ifs.ignore(0x18C);
        ifs.ignore(4); // Padding

        // Items
        ifs.read(reinterpret_cast<char *>(player.itemsHeader.data()), player.itemsHeader.size());
        for(uint8_t i = 0; i < player.items.size(); i++) {
            player.items[i] = ItemEntry::decode(ifs);
        }

        for(uint8_t i = 0; i < player.items.size(); i++) {
            player.items[i].decodeCooldown(ifs);
        }

        // Playerdata
        ifs.ignore(0x0C /* or 0x0F ? */); // Ignore playerData header
        ifs.read(reinterpret_cast<char *>(player.playerData.data()), player.playerData.size());

        while(ifs.peek() == 0x00 || ifs.peek() == 0x01) ifs.ignore(1); // Jump over some nulls (not in wiki)

        // Abilities
        ifs.ignore(0x04); // Ignore abilities header
        int abilities = 3;
        while(--abilities) {
            ifs.ignore(0x04);
            uint8_t first = ifs.peek();
            if(first == 0xF3)
                ifs.ignore(3);
            else if(first == 0x73)
                ifs.ignore(6);
            else if(first == 0x33)
                ifs.ignore(6);
            else {
                std::cout << "unkown ability format @ " << std::hex << ifs.tellg() << std::endl;
                exit(1);
            }
        }
        ifs.ignore(3); // Ignore last ability

        // Footer
        uint8_t marker[] = {0x00, 0x00, 0x15, 0x01}; // Search for this
        char buf[sizeof(marker)];
        while(true) {
            auto pos = ifs.tellg();
            ifs.read(buf, sizeof(marker));
            if(ifs.eof()) {
                std::cout << "footer not found" << std::endl;
                exit(1);
            }
            ifs.seekg(pos);
            if(!memcmp((void*) marker, (void*) buf, sizeof(marker)))
                break;
            ifs.ignore(1);
        }
        ifs.read(reinterpret_cast<char *>(player.footer.data()), player.footer.size());

        return player;
    }
}
