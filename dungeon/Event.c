#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Character.h"
#include "monster.h"
#include "battle.h"
#include "shop.h"
#include "items.h"


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

void solvePuzzle(Character* player);
void unlockBox(Character* player);
void luckybox(Character* player);

void callEvent(char flag, int floor){
    switch(flag){
        case 'D':
        //  call dungeon
        return;

        case 'M':
        //  call shop
        return;

        case 'B':
        //  call battle
        srand(time(NULL));
        battle(getPlayer(), getMonster((rand()%4 + 1) + ((floor / 10) * 10)));
        return;

        case 'S':
        //  call search
        return;

        case 'K':
        //  call boss battle
        battle(getPlayer(), 1000 + (floor / 10));
        return;

        case 'F':
        //  call randum event
        srand(time(NULL));
        int r = rand()%33;
        if(r > 23){
            solvepuzzle(getPlayer());
        }else if(r > 13){
            unlockBox(getplayer());
        } else {
            luckybox(getPlayer());
        }
        return;

        case 'I':
        //  call designated event
        return;
        
        default:
        return;
    }
}

void solvePuzzle(Character* player) {
    srand(time(NULL));
    int puzzleDifficulty = rand()%100 - player->intelligence;  // 퍼즐 난이도
    printf("퍼즐 난이도: %d\n", (puzzleDifficulty / 10));
    printf("당신의 지능 수치: %d\n", player->intelligence);

    if (player->intelligence >= puzzleDifficulty) {
        printf("퍼즐을 성공적으로 풀었습니다!\n");
    } else {
        printf("지능이 부족하여 퍼즐을 풀지 못했습니다.\n");
    }
}

// 자물쇠 해제 함수
void unlockBox(Character* player) {
    srand(time(NULL));
    int lockDifficulty = rand()%100 - player->sensory;  // 자물쇠 난이도
    printf("자물쇠 난이도: %d\n", (lockDifficulty / 10));
    printf("당신의 감각 수치: %d\n", player->sensory);

    if (player->sensory >= lockDifficulty) {
        printf("자물쇠를 성공적으로 열었습니다!\n");
    } else {
        printf("감각이 부족하여 자물쇠를 열지 못했습니다.\n");
    }
}

void luckybox(Character* player){
    srand(time(NULL));
    int luckybox = rand()%100 - player->luck;
    printf("꽝 확률: %d\n", (luckybox / 10));
    printf("당신의 운 수치: %d\n", player->sensory);

    if (player->luck >= luckybox) {
        printf("당첨 되었습니다!\n");
    } else {
        printf("꽝!\n");
    }

}