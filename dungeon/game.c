#include <stdio.h>
#include "game.h"
#include "dungeon.h"
#include "save.h"

void startNewGame() {
    Dungeon dungeon;
    generateDungeon(&dungeon, 1); // 첫 번째 레벨 던전 생성
    printDungeon(&dungeon);

    saveGame("savegame.dat", &dungeon);  // 게임 저장
}

void loadExistingGame() {
    Dungeon dungeon;
    loadGame("savegame.dat", &dungeon); // 저장된 게임 불러오기
    printDungeon(&dungeon);
}
