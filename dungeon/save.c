#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"

// 던전과 스테이터스를 저장하는 함수
void saveDungeonAndStats(const char *filename, int health, int strength, int agility, int intelligence, int sensory, int luck, char dungeon[DUNGEON_SIZE][DUNGEON_SIZE]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return;
    }

        // 던전 정보 저장
    fprintf(file, "\nDungeon:\n");
    for (int i = 0; i < DUNGEON_SIZE; i++) {
        for (int j = 0; j < DUNGEON_SIZE; j++) {
            fprintf(file, "%c ", dungeon[i][j]);
        }
        fprintf(file, "\n");
    }

    // 스테이터스 저장
    fprintf(file, "Health: %d\n", health);
    fprintf(file, "Strength: %d\n", strength);
    fprintf(file, "Agility: %d\n", agility);
    fprintf(file, "Intelligence: %d\n", intelligence);
    fprintf(file, "Sensory: %d\n", sensory);
    fprintf(file, "Luck: %d\n", luck);

    fclose(file);
    printf("저장 완료: %s\n", filename);
}
