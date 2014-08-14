// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include <iostream>
#include <fstream>

#include <libOL/Chunks.h>
#include <libOL/Rofl.h>
#include <libOL/Keyframe.h>

void test_keyframe()
{

    std::ifstream ifs("../../lol-spec/analysis2/keyframes/EUW1.1617523548.1.keyframe", std::ios::binary);

    libol::Keyframe frame = libol::Keyframe::decode(ifs);

    for(auto& player : frame.players) {
    	std::cout << player.summonerName << " as " << player.championName << std::endl;
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


