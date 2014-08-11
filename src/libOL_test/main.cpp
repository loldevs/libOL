// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include <iostream>
#include <fstream>

#include <libOL/File.h>
#include <libOL/Chunks.h>

int main(int argc, const char * argv[])
{

    std::ifstream ifs("/Users/toulouse/code/lol/lmao/rofl/22923174.rofl", std::ios::binary);

    libol::File file = libol::File::decode(ifs);

    auto header0 = file.chunkHeaders[0];
    auto chunk = file.getDecryptedChunk(ifs, header0);
    return 0;
}


