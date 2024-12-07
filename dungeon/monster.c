#include <stdio.h>
#include "Monster.h"

//  일반 몬스터
//  {"name", hp, atk, def}
Monster M_001 = {"M_001", 10, 2, 4};
Monster M_002 = {"M_002", 40, 10, 5};
Monster M_003 = {"M_003", 90, 2, 10};
Monster M_004 = {"M_004", 60, 1, 20};
Monster M_005 = {"M_005", 40, 20, 1};
// 새로운 일반 몬스터 추가
Monster M_006 = {"M_006", 20, 5, 3};
Monster M_007 = {"M_007", 50, 8, 8};

// 새로운 보스 몬스터 추가
Monster M_1002 = {"M_1002", 600, 100, 40};


//  boss monster
Monster M_1001 = {"M_1001", 500, 80, 30};

// 위에 정의되어있는 몬스터 정보 구조체 주소를 반환함
Monster* getMonster(int Monster_value) {
    switch(Monster_value){
        case 1:
        return &M_001;
        case 2:
        return &M_002;
        case 3:
        return &M_003;
        case 4:
        return &M_004;
        case 5:
        return &M_005;
        case 1001:
        return &M_1001;
        case 6: 
        return &M_006;
        case 7: 
        return &M_007;
        case 1002: 
        return &M_1002;
        default: 
        return NULL
    }
}