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

    auto decryptionKey = file.payloadHeader.getDecodedEncryptionKey();

    auto header0 = file.chunkHeaders[0];
    std::vector<uint8_t> chunk0;
    chunk0.resize(header0.chunkLength);

    ifs.seekg(file.header.payloadOffset +
              file.payloadHeader.chunkCount * 17 +
              file.payloadHeader.keyframeCount  * 17 +
              header0.offset);
    ifs.read(reinterpret_cast<char *>(&chunk0[0]), header0.chunkLength);

    auto chunk0decrypted = libol::Chunks::decryptAndDecompress(chunk0, decryptionKey);
    std::cout << "foo" << std::endl;
    return 0;
}


