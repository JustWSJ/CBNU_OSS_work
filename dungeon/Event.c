#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Character.h"
#include "monster.h"
#include "battle.h"
#include "shop.h"


// *B (Battle): 강제 전투
// 1E (Entrance): 입구
// *F (Force): 강제 이벤트
// .I (Inventory): 수색 후 아이템(이나 스테이터스?) 얻는 이벤트
// *K (King): 보스 전투
// (L) (Location): 플레이어의 현재 위치 (사용할지는 미지수, 다른 창 넘기는 방식이면 써야 함)
// R (Road): 수색 불가능한 길
// .S (Search): 수색 후 전투
// 0W (Wall): 벽. 막힘
// *X (eXit): 출구

void callEvent(char flag){
    switch(flag){
        case 'D':
        //  call dungeon
        case 'M':
        //  call shop
        case 'B':
        //  call battle
        srand(time(NULL));
        //battle(getPlayer(), getMonster(rand()%5));
        //battle(getPlayer(), getPlayer());
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