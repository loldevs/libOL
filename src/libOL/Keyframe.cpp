// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Keyframe.h"
#include "PacketReader.h"

#include <iostream>

namespace libol {
    Keyframe::Keyframe(std::vector<Block>& blocks) :
        header(blocks[0])
    {

        for(size_t i = 1; i < blocks.size(); i++) {
            if(PlayerHeader::test(blocks[i])) {
                Player player;

                PlayerHeader header(blocks[i++]);
                player.playerId = header.playerNumber;
                player.entityId = header.entityId;
                player.champion = header.championName;
                player.summoner.name = header.summonerName;
                
                SummonerData data(blocks[i++]);
                player.summoner.level = data.level;
                player.summoner.runes = data.runes;
                player.summoner.masteries = data.masteries;

                player.items = Inventory(blocks[i++]).items;

                while(!PlayerStats::test(blocks[i])) { // Jump over itemreplacement or similar blocks
                    i++;
                    assert(i <= blocks.size());
                }
                player.stats = PlayerStats(blocks[i++]).stats;

                player.abilities.push_back(AbilityLevel(blocks[i++]));
                player.abilities.push_back(AbilityLevel(blocks[i++]));
                player.abilities.push_back(AbilityLevel(blocks[i++]));
                player.abilities.push_back(AbilityLevel(blocks[i]));

                players.push_back(player);
            }

            if(TurretHeader::test(blocks[i])) {
                Turret turret;

                TurretHeader header(blocks[i++]);
                turret.entityId = header.entityId;
                turret.name = header.name;
                turret.isFountainLaser = header.isFountainLaser;
                turret.isAttackable = header.isAttackable;

                turret.items = Inventory(blocks[i]).items;

                turrets.push_back(turret);
            }
        }
    }
}
