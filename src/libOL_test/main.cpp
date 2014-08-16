// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include <iostream>
#include <fstream>

#include <libOL/Chunks.h>
#include <libOL/Rofl.h>
#include <libOL/Keyframe.h>

void test_keyframe()
{

    std::ifstream ifs("../../lol-spec/analysis/keyframes/EUW1.1623958895.3.keyframe", std::ios::binary);

    libol::Keyframe frame = libol::Keyframe::decode(ifs);

    std::cout << "Time: " << frame.header.timestamp << "s" << std::endl;

    for(auto& player : frame.players) {
        std::cout << player.summonerName << " as " << player.championName << std::endl;

        std::cout << "Runes: ";
        for(auto& rune : player.runes) {
            std::cout << rune << " ";
        }
        std::cout << std::endl;

        int count = 0;
        for(auto& mastery : player.masteries) {
            count += mastery.pointsSpent;
        }
        std::cout << count << " mastery points spent" << std::endl;

        std::cout << "Items: " << std::endl;
        for(auto& item : player.items) {
            std::cout << (unsigned) item.quantity << " * " << item.itemId << " with "
                << (unsigned) item.charges << " charges and " << item.cooldown << " cooldown" << std::endl;
        }
    }
}


void test_rofl() {
    std::ifstream ifs("/Users/toulouse/code/lol/lmao/rofl/22923174.rofl", std::ios::binary);

    libol::Rofl rofl = libol::Rofl::decode(ifs);

    auto header0 = rofl.chunkHeaders[0];
    auto chunk = rofl.getDecryptedChunk(ifs, header0);
}

int main(int argc, const char * argv[])
{
    test_keyframe();
    return 0;
}


