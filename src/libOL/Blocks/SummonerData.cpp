// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "SummonerData.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool MasteryEntry::probe(Block::Stream& ifs) {
        auto pos = ifs.tellg();
        ifs.ignore(2);
        uint8_t test = ifs.get();
        ifs.seekg(pos);

        return test == 0x03;
    }

    MasteryEntry MasteryEntry::decode(Block::Stream& ifs) {
        MasteryEntry entry;

        entry.id = ifs.get();
        entry.tree = ifs.get();
        uint8_t byte = ifs.get();
        assert(byte == 0x03);
        byte = ifs.get();
        assert(byte == 0x00);
        ifs.read(&entry.pointsSpent);

        return entry;
    }

    SummonerData SummonerData::decode(Block& block) {
        assert(block.type == 0x2A);
        assert(block.size == 0x212);

        SummonerData data;

        auto stream = block.createStream();

        stream.read(data.runes.data(), data.runes.size());
        stream.read(data.spells.data(), data.spells.size());

        int masteryCount = 0;
        while(MasteryEntry::probe(stream) && masteryCount < 79) {
            data.masteries.push_back(MasteryEntry::decode(stream));
            masteryCount++;
        }

        data.level = block.content[0x210];

        return data;
    }
}
