#include <stdio.h>
#include <string.h>
#include "character.h"

// 캐릭터 데이터 정의
Character player = {"Crowler", 5, 5, 5, 5, 5, 5, 100, -1};

// Getter 함수
Character* getPlayer() {
    return &player;
}

// Setter 함수
void setPlayer(Character newPlayer) {
    player = newPlayer;
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
