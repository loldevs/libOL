// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>

#include <libOL/Chunks.h>
#include <libOL/Rofl.h>
#include <libOL/BlockReader.h>
#include <libOL/Packet.h>

#define MAX_ARGUMENT_LENGTH 600

int test_blocks(std::vector<std::string> arguments)
{
    assert(arguments.size() == 1);

    std::ifstream ifs(arguments.at(0), std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open " << arguments.at(0) << ": " << strerror(errno) << std::endl;
        return 2;
    }

    libol::BlockReader reader;
    auto blocks = reader.readBlocksFromStream(ifs);

    for(auto& block : blocks) {
        std::cout << std::hex << "[0x" << block.offset << "]\t";
        std::cout << std::dec << "time: " << block.time << "s\t";
        std::cout << std::hex << "type: 0x" << (unsigned) block.type << "\t";
        std::cout << "param: 0x" << block.entityId << "\t";
        std::cout << "size: 0x" << block.size << std::endl;
    }

    return 0;
}

int test_packets(std::vector<std::string> arguments)
{
    assert(arguments.size() == 1);

    std::ifstream ifs(arguments.at(0), std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open " << arguments.at(0) << ": " << strerror(errno) << std::endl;
        return 2;
    }

    libol::BlockReader reader;
    auto blocks = reader.readBlocksFromStream(ifs);

    for(auto block : blocks) {
        libol::Packet pkt = libol::Packet::decode(block);
        if(pkt.isDecoded) {
            std::cout << pkt.typeName << ": " << pkt.data.toString() << std::endl;
        }
    }

    return 0;
}


int test_rofl(std::vector<std::string> arguments)
{
    assert(arguments.size() == 1);

    std::ifstream ifs(arguments.at(0), std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open " << arguments.at(0) << ": " << strerror(errno) << std::endl;
        return 2;
    }

    libol::Rofl rofl = libol::Rofl::decode(ifs);

    auto header0 = rofl.chunkHeaders[0];
    auto chunk = rofl.getDecryptedChunk(ifs, header0);

    return 0;
}

int usage(std::string prog_name) {
    std::cerr << prog_name << " [rofl|blocks|packets] <rofl/blocks/packets file>" << std::endl;
    return 1;
}

int main(int argc, const char * argv[])
{
    std::string executable_name = std::string(argv[0], 0, MAX_ARGUMENT_LENGTH);
    if (argc < 3) {
        return usage(executable_name);
    }

    // build argument vector
    std::vector<std::string> arguments;
    for (int i = 1; i < argc; ++i) {
        arguments.push_back(std::string(argv[i], 0, MAX_ARGUMENT_LENGTH));
    }

    std::string command = arguments.at(0);
    arguments.erase(arguments.begin());

    if (command == "rofl") {
        return test_rofl(arguments);
    } else if (command == "blocks") {
        return test_blocks(arguments);
    } else if (command == "packets") {
        return test_packets(arguments);
    }

    return usage(executable_name);
}


