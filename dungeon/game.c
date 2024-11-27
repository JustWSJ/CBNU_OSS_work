#include <stdio.h>
#include "game.h"
#include "dungeon.h"
#include "save.h"

void loadExistingGame() {
    Dungeon dungeon;
    loadGame("savegame.dat", &dungeon); // 저장된 게임 불러오기
    printDungeon(&dungeon);
}
