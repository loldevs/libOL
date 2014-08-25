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
#include <libOL/Keyframe.h>

#define MAX_ARGUMENT_LENGTH 600

int test_keyframe(std::vector<std::string> arguments)
{
    assert(arguments.size() == 1);

    std::ifstream ifs(arguments.at(0), std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open " << arguments.at(0) << ": " << strerror(errno) << std::endl;
        return 2;
    }

    std::vector<libol::Block> blocks;
    libol::Block prev;
    bool first = true;
    while(true) {
        libol::Block block = libol::Block::decode(ifs, first ? nullptr : &prev);
        first = false;
        prev = block;
        ifs.peek(); // provoke eof
        if(!ifs.eof())
            blocks.push_back(block);
        else
            break;
    }

    auto frame = libol::Keyframe::decode(blocks);

    std::cout << "Time: " << frame.header.timestamp << "s" << std::endl;

    for(auto& player : frame.players) {
        std::cout << player.summoner.name << "[" << (unsigned) player.summoner.level << "] as " << player.champion << std::endl;
        std::cout << player.stats.kills << "/" << player.stats.deaths << "/" << player.stats.assists << std::endl;

        std::cout << "Runes: ";
        for(auto& rune : player.summoner.runes) {
            std::cout << rune << " ";
        }
        std::cout << std::endl;

        int count = 0;
        for(auto& mastery : player.summoner.masteries) {
            count += mastery.pointsSpent;
        }
        std::cout << count << " mastery points spent" << std::endl;

        std::cout << "Items: " << std::endl;
        for(auto& item : player.items) {
            std::cout << (unsigned) item.quantity << " * " << item.itemId << " with "
                << (unsigned) item.charges << " charges and cooldown of " << item.cooldown << "/" << item.baseCooldown << std::endl;
        }

        std::cout << "Abilities: " << std::endl;
        for(auto& ability : player.abilities) {
            std::cout << (unsigned) ability.abilityId << ": Level " << (unsigned) ability.level << std::endl;
        }
    }

    for(auto& turret : frame.turrets) {
        std::cout << "Turret: " << turret.name << std::endl;
        std::cout << "IsFountainLaser: " << turret.isFountainLaser << std::endl;
        std::cout << "IsAttackable: " << turret.isAttackable << std::endl;
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
    std::cerr << prog_name << " [rofl|keyframe] <rofl/keyframe file>" << std::endl;
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
    } else if (command == "keyframe") {
        return test_keyframe(arguments);
    }

    return usage(executable_name);
}


