#include <stdio.h>
#include <string.h>
#include "character.h"

// 캐릭터 데이터 정의
Character player = {"Crowler", 5, 5, 5, 5, 5, 5, 100, 0};

// Getter 함수
Character* getPlayer() {
    return &player;
}

// Setter 함수
void setPlayer(Character newPlayer) {
    player = newPlayer;
}

// 특정 속성 업데이트 함수
void updatePlayerStat(const int stat, int value) {
    if (stat == 0) {
        player.health = value;
    } else if (stat == 1) {
        player.strength = value;
    } else if (stat == 2) {
        player.agility = value;
    } else if (stat == 3) {
        player.intelligence = value;
    } else if (stat == 4) {
        player.sensory = value;
    } else if (stat == 5) {
        player.luck = value;
    } else {
        printf("Error: Unknown stat.\n");
    }
}
