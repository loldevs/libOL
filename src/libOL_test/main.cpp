// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include <iostream>
#include <fstream>

#include <libOL/Chunks.h>
#include <libOL/Rofl.h>

int main(int argc, const char * argv[])
{

    std::ifstream ifs("/Users/toulouse/code/lol/lmao/rofl/22923174.rofl", std::ios::binary);

    libol::Rofl rofl = libol::Rofl::decode(ifs);

    auto header0 = rofl.chunkHeaders[0];
    auto chunk = rofl.getDecryptedChunk(ifs, header0);
    return 0;
}


