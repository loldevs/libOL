// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Keyframe.h"
#include "Blocks/PlayerHeader.h"
#include "Blocks/SummonerData.h"
#include "Blocks/Inventory.h"
#include "Blocks/PlayerStats.h"
#include "Blocks/Ability.h"
#include "Blocks/TurretHeader.h"

#include <iostream>

namespace libol {
    Keyframe Keyframe::decode(std::vector<Block>& blocks) {
        Keyframe frame;

        frame.header = KeyframeHeader::decode(blocks[0]);

        for(size_t i = 1; i < blocks.size(); i++) {
            if(PlayerHeader::test(blocks[i])) {
                Player player;

                auto header = PlayerHeader::decode(blocks[i++]);
                player.playerId = header.playerNumber;
                player.entityId = header.entityId;
                player.champion = header.championName;
                player.summoner.name = header.summonerName;
                
                auto data = SummonerData::decode(blocks[i++]);
                player.summoner.level = data.level;
                player.summoner.runes = data.runes;
                player.summoner.masteries = data.masteries;

                player.items = Inventory::decode(blocks[i++]).items;

                while(!PlayerStats::test(blocks[i])) { // Jump over itemreplacement or similar blocks
                    i++;
                    assert(i <= blocks.size());
                }
                player.stats = PlayerStats::decode(blocks[i++]).stats;

                player.abilities.push_back(Ability::decode(blocks[i++]));
                player.abilities.push_back(Ability::decode(blocks[i++]));
                player.abilities.push_back(Ability::decode(blocks[i++]));
                player.abilities.push_back(Ability::decode(blocks[i]));

                frame.players.push_back(player);
            }

            if(TurretHeader::test(blocks[i])) {
                Turret turret;

                auto header = TurretHeader::decode(blocks[i++]);
                turret.entityId = header.entityId;
                turret.name = header.name;
                turret.isFountainLaser = header.isFountainLaser;
                turret.isAttackable = header.isAttackable;

                turret.items = Inventory::decode(blocks[i]).items;

                frame.turrets.push_back(turret);
            }
        }

        return frame;
    }
}
