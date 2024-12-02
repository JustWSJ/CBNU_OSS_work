#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "monster.h"
#include "battle.h"


//  이벤트 이름
/*
B(강제 전투)
S(칸 탐색 후 전투)
K(보스)
F(랜덤 이벤트)
I(지정 이벤트)
*/

const char *Event_name[5] = {"B", "S", "K", "F", "I"};

void callEvent(char flag){
    if(flag == Event_name[0]){
        srand(time(NULL));
        battle(getPlayer(), getMonster(rand()%5));
    } else if(flag == Event_name[1]) {

    } else if(flag == Event_name[2]) {

    } else if(flag == Event_name[3]) {

    }
}