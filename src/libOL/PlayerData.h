// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__PlayerData__
#define __libol__PlayerData__

#include <cstdint>
#include <iostream>

namespace libol {
    struct PlayerData {
        uint32_t kills;
        uint32_t unk0;
        uint32_t assists;
        uint32_t unk1;
        uint32_t doubleKills;
        uint32_t unk2;
        uint32_t unk3;
        uint32_t unk4;
        uint32_t unrealKills;
        float totalGoldEarned;
        float totalGoldSpent;
        uint32_t unk5;
        uint32_t unk6;
        uint32_t unk7;
        uint32_t unk8;
        uint32_t unk9;
        uint32_t unk10;
        uint32_t unk11;
        uint32_t unk12;
        uint32_t unk13;
        uint32_t unk14;
        uint32_t currentKillingSpree;
        float largestCriticalStrike;
        uint32_t largestKillingSpree;
        uint32_t largestMultiKill;
        uint32_t unk15;
        float longestTimeSpentLiving;
        float totalMagicDamageDealt;
        float magicDamageDealtToChampions;
        float magicalDamageTaken;
        uint32_t totalMinionsKilled;
        uint16_t padding0;
        uint32_t totalNeutralMinionsKilled;
        uint32_t neutralMinionsKilledInEnemyJungle;
        uint32_t neutralMinionsKilledInTeamJungle;
        uint32_t deaths;
        uint32_t pentaKills;
        float totalPhysicalDamageDealt;
        float physicalDamageDealtToChampions;
        float physicalDamageTaken;
        uint32_t unk16;
        uint32_t quadraKills;
        uint32_t unk17;
        uint32_t unk18;
        uint32_t unk19;
        uint32_t unk20;
        uint32_t unk21;
        uint32_t unk22;
        uint32_t unk23;
        uint32_t unk24;
        uint32_t unk25;
        uint32_t teamId;
        float unk26;
        float totalDamageDealt;
        float totalDamageDealtToChamptions;
        float totalDamageTaken;
        uint32_t totalHeal;
        float totalTimeCCDealt;
        float totalTimeSpentDead;
        uint32_t totalUnitsHealed;
        uint32_t tripleKills;
        float totalTrueDamageDealt;
        float trueDamageDealtToChamptions;
        float trueDamageTaken;
        uint32_t turretsDestroyed;
        uint32_t inhibitorsDestroyed;
        uint32_t unk27;
        uint32_t wardsDestroyed;
        uint32_t wardsPlaced;
        uint32_t unk28;
        uint32_t unk29;
        uint16_t padding1;
    };
}

#endif /* defined(__libol__PlayerData__) */
