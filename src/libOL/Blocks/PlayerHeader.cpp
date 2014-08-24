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

    PlayerHeader PlayerHeader::decode(Block& block) {
        assert(test(block));

        PlayerHeader player;

        auto stream = block.createStream();

        stream.read(&player.entityId);
        stream.read(&player.playerNumber);

        stream.read(player.unk0.data(), player.unk0.size());

        // Summoner name
        char summonerChars[0x81];
        stream.read(summonerChars, 0x80);
        summonerChars[0x80] = 0x00;
        player.summonerName = summonerChars;

        // Champion name
        char championChars[0x11];
        stream.read(championChars, 0x10);
        championChars[0x10] = 0x00;
        player.championName = championChars;

        stream.read(player.unk1.data(), player.unk1.size());

        return player;
    }
}
