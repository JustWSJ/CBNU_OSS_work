#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_DUNGEON_SIZE 5  // 시작 던전 크기 5x5
#define DUNGEON_SIZE_INCREASE_STEP 5  // 던전 크기 증가 값
#define MAX_DUNGEON_SIZE 100  // 최대 던전 크기
#define LEVEL_INCREASE_STEP 5  // 던전 크기 증가 주기 (5계층마다)

void generateDungeon(char dungeon[][MAX_DUNGEON_SIZE], int dungeonSize) {
    for (int i = 0; i < dungeonSize; i++) {
        for (int j = 0; j < dungeonSize; j++) {
            // 랜덤으로 벽('#') 또는 길('.')을 생성
            dungeon[i][j] = (rand() % 2) == 0 ? '#' : '.';
        }
    }

    // 던전 시작점과 끝점을 설정
    dungeon[0][0] = 'S';  // S: 시작점
    dungeon[dungeonSize - 1][dungeonSize - 1] = 'E';  // E: 종료점
}

int isSpecialLevel(int level) {
    // 0, 10, 20, ..., 100 계층에서는 미로를 생성하지 않음
    return (level % 10 == 0);
}

void generateDungeonForLevel(int level, char dungeon[][MAX_DUNGEON_SIZE]) {
    // 0, 10, 20, ..., 100 계층에서는 미로를 생성하지 않음
    if (isSpecialLevel(level)) {
        return;
    }

    // 던전 크기 계산
    int dungeonSize = INITIAL_DUNGEON_SIZE + (level / LEVEL_INCREASE_STEP) * DUNGEON_SIZE_INCREASE_STEP;

    // 던전 크기가 최대 크기인 100을 넘지 않도록 제한
    if (dungeonSize > MAX_DUNGEON_SIZE) dungeonSize = MAX_DUNGEON_SIZE;

    // 던전 생성
    generateDungeon(dungeon, dungeonSize);
}
