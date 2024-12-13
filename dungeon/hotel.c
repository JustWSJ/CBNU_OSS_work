#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hotel.h"

// 세이브 데이터 저장 함수
void saveProgress(const char* dungeonName, int clearedFloor) {
    FILE *file = fopen("save_data.txt", "w");
    if (file == NULL) {
        printf("세이브 파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "%s\n%d\n", dungeonName, clearedFloor);
    fclose(file);
    printf("진행 상황이 저장되었습니다! (%s 던전, %d층 클리어)\n", dungeonName, clearedFloor);
}
// 세이브 데이터 로드 함수
Character loadProgress(void) {
    Character player = {"Crowler", 100, 100, 5, 5, 5, 5, -1};
    FILE *file = fopen("save_data.txt", "r");

    if (file != NULL) {
        char dungeonName[50];
        int clearedFloor;
        fscanf(file, "%49s %d", dungeonName, &clearedFloor);
        player.Maxfloor = clearedFloor;
        fclose(file);
        printf("저장된 진행 상황: %s 던전, %d층 클리어\n", dungeonName, clearedFloor);
    } else {
        printf("저장된 데이터가 없습니다. 새로운 게임을 시작합니다.\n");
    }

    return player;
}

// 휴식 기능: 체력을 최대 체력으로 회복
void restAtHotel(Character* player) {
    player->health = player->maxHealth;  // 체력을 최대 체력으로 회복
    printf("\n[호텔에서 휴식 중...]\n");
    printf("체력이 완전히 회복되었습니다! (현재 체력: %d/%d)\n", player->health, player->maxHealth);
}