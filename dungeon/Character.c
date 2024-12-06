#include <stdio.h>
#include <string.h>
#include "character.h"

// 캐릭터 데이터 정의
Character player = {"Crowler", 100, 5, 5, 5, 5, 5, 0,0};

// Getter 함수
Character* getPlayer() {
    return &player;
}

// Setter 함수
void setPlayer(Character newPlayer) {
    player = newPlayer;
}
// 골드 획득
void addGold(Character* player, int amount) {
    if (amount < 0) {
        printf("골드 획득량은 음수가 될 수 없습니다.\n");
        return;
    }
    player->gold += amount;
    printf("골드를 %d 획득했습니다! 현재 골드: %d\n", amount, player->gold);
}

// 골드 소모
int spendGold(Character* player, int amount) {
    if (amount > player->gold) {
        printf("골드가 부족합니다! 현재 골드: %d\n", player->gold);
        return 0; // 실패
    }
    player->gold -= amount;
    printf("골드를 %d 소모했습니다! 남은 골드: %d\n", amount, player->gold);
    return 1; // 성공
}

// 특정 속성 업데이트 함수
void updatePlayerStat(const char* stat, int value) {
    if (strcmp(stat, "health") == 0) {
        player.health = value;
    } else if (strcmp(stat, "strength") == 0) {
        player.strength = value;
    } else if (strcmp(stat, "agility") == 0) {
        player.agility = value;
    } else if (strcmp(stat, "intelligence") == 0) {
        player.intelligence = value;
    } else if (strcmp(stat, "sensory") == 0) {
        player.sensory = value;
    } else if (strcmp(stat, "luck") == 0) {
        player.luck = value;
    } else {
        printf("Error: Unknown stat '%s'.\n", stat);
    }
}
