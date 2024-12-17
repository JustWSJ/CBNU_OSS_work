#include <stdio.h>
#include "character.h"
#include "console_util.h"
#include "key_input.h"

// 캐릭터 스탯 이름
const char *stat_name[6] = {"Health", "Strength", "Agility", "Intelligence", "Sensory", "Luck"};

// 스탯 ID에 따라 값을 업데이트
void updateStat(Character *player, int statID, int delta) {
    switch (statID) {
        case 0: player->health += delta; break;
        case 1: player->strength += delta; break;
        case 2: player->agility += delta; break;
        case 3: player->intelligence += delta; break;
        case 4: player->sensory += delta; break;
        case 5: player->luck += delta; break;
        case 6: player->max_health = player->health * 20; break;
    }
}

// 현재 스탯 값을 가져오기
int getStatValue(Character *player, int statID) {
    switch (statID) {
        case 0: return player->health;
        case 1: return player->strength;
        case 2: return player->agility;
        case 3: return player->intelligence;
        case 4: return player->sensory;
        case 5: return player->luck;
        case 6: return player->max_health;
        default: return 0;
    }
}