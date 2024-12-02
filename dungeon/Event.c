#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "monster.h"
#include "battle.h"


/*  Event name
D = entrance dungeon
B = battle
S(칸 탐색 후 전투)?
K = boss battle
F(랜덤 이벤트)
I(지정 이벤트)
*/

const char *Event_name[6] = {'D', 'B', 'S', 'K', 'F', 'I'};

//  F random event

//  I designated event







void callEvent(char flag){
    if(flag == Event_name[0]){
        //  function enter dungeon
    } else if(flag == Event_name[1]){
        //  function battle
        srand(time(NULL));
        battle(getPlayer(), getMonster(rand()%5));
    } else if(flag == Event_name[2]) {
        //  function search
    } else if(flag == Event_name[3]) {
        //  function boss battle
    } else if(flag == Event_name[4]) {
        //  function rand event
    } else if(flag == Event_name[5]) {
        //  function event
    }
}