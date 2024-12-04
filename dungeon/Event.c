#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "monster.h"
#include "battle.h"
#include "shop.h"


/*  Event name
D = entrance dungeon
M = shop
B = battle
S(칸 탐색 후 전투)?
K = boss battle
F = random event
I = designated event
*/

void callEvent(char flag){
    switch(flag){
        case 'D':
        //  call dungeon
        case 'M':
        //  call shop
        case 'B':
        //  call battle
        srand(time(NULL));
        battle(getPlayer(), getMonster(rand()%5));
        return;
        case 'S':
        //  call search
        case 'K':
        //  call boss battle
        case 'F':
        //  call randum event
        case 'I':
        //  call designated event
        default:
        return;
    }
}