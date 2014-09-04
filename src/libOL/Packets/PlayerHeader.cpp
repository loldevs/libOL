// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "PlayerHeader.h"

#include <iostream>
#include <cassert>

namespace libol {
    bool PlayerHeader::test(Block& block) {
        return (
            block.type == 0x4C
            && block.size == 0xC3
        );
    }

    PlayerHeader::PlayerHeader(Block& block) {
        auto stream = block.createStream();

        stream.read(&entityId);
        stream.read(&playerNumber);

        stream.read(unk0.data(), unk0.size());

        // Summoner name
        char summonerChars[0x81];
        stream.read(summonerChars, 0x80);
        summonerChars[0x80] = 0x00;
        summonerName = summonerChars;

        // Champion name
        char championChars[0x11];
        stream.read(championChars, 0x10);
        championChars[0x10] = 0x00;
        championName = championChars;

        stream.read(unk1.data(), unk1.size());
    }
}
