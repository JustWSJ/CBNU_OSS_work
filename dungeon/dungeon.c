#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console_util.h"
#include "key_input.h"

#define DUNGEON_SIZE_INCREASE_STEP 5  // 던전 크기 증가 값
#define LEVEL_INCREASE_STEP 5  // 던전 크기 증가 주기 (5계층마다)

int SelectFloor(){
    int choice = 0;

    clearScreen();
    printf(" Select Floor\n");
    printf(" > 0\n");
    printf(" > 10\n");
    printf(" > 20\n");
    printf(" > 30\n");
    printf(" > 40\n");
    printf(" > 50\n");
    printf(" > 60\n");
    printf(" > 70\n");
    printf(" > 80\n");
    printf(" > 90\n");
    //while choice
    choice = 0;
    while (1) {
        if(isKeyPressed(KEY_ENTER)){
            Sleep(150);
            break;
        }
    }
    return choice;
}

void DungeonEntrance(int Floor){
    clearScreen();
    printf(" 던전 %d층\n", Floor);
    printf("> %d층으로 가기\n", Floor + 1);
    printf(" 마을로 돌아가기\n");
    //while choice
    
}
