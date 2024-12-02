#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "monster.h"
#include "battle.h"


//  이벤트 이름
/*
R = road
W = Wall
B = battle
K = boss battle
*/
const char *Event_name[4] = {"R", "W", "B", "K"};

void callEvent(char flag){
    if(flag == Event_name[0]){

    } else if(flag == Event_name[1]) {

    } else if(flag == Event_name[2]) {
        srand(time(NULL));
        battle(getPlayer(), getMonster(rand()%5));
    } else if(flag == Event_name[3]) {

    }
}