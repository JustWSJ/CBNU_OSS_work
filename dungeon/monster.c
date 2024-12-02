#include <stdio.h>
#include "Monster.h"

//  일반 몬스터
//  {"name", hp, atk, def}
Monster M_001 = {"M_001", 10, 2, 4};
Monster M_002 = {"M_002", 40, 10, 5};
Monster M_003 = {"M_003", 90, 2, 10};
Monster M_004 = {"M_004", 60, 1, 20};
Monster M_005 = {"M_005", 40, 20, 1};

// 위에 정의되어있는 몬스터 정보 구조체 주소를 반환함
Monster* getMonster(int Monster_value) {
    if(Monster_value == 1){
        return &M_001;
    } else if (Monster_value == 2){
        return &M_002;
    } else if (Monster_value == 3){
        return &M_003;
    } else if (Monster_value == 4){
        return &M_004;
    } else if (Monster_value == 5){
        return &M_005;
    }
}