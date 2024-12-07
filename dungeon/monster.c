#include <stdio.h>
#include "Monster.h"

// 일반 몬스터 추가
Monster M_008 = {"M_008", 70, 15, 10};
Monster M_009 = {"M_009", 30, 12, 7};
Monster M_010 = {"M_010", 55, 18, 5};
Monster M_011 = {"M_011", 65, 20, 8};
Monster M_012 = {"M_012", 80, 25, 12};
Monster M_013 = {"M_013", 45, 10, 15};
Monster M_014 = {"M_014", 75, 22, 10};
Monster M_015 = {"M_015", 60, 15, 20};

// 보스 몬스터 추가
Monster M_1003 = {"M_1003", 700, 120, 50};
Monster M_1004 = {"M_1004", 800, 150, 60};
Monster M_1005 = {"M_1005", 900, 180, 70};
Monster M_1006 = {"M_1006", 1000, 200, 80};
Monster M_1007 = {"M_1007", 1100, 220, 90};
Monster M_1008 = {"M_1008", 1200, 250, 100};
Monster M_1009 = {"M_1009", 1300, 280, 110};
Monster M_1010 = {"M_1010", 1500, 300, 120};

// 기존 몬스터 정의 및 반환 함수
Monster* getMonster(int Monster_value) {
    switch (Monster_value) {
        case 1: return &M_001;
        case 2: return &M_002;
        case 3: return &M_003;
        case 4: return &M_004;
        case 5: return &M_005;
        case 6: return &M_006;
        case 7: return &M_007;
        case 8: return &M_008;
        case 9: return &M_009;
        case 10: return &M_010;
        case 11: return &M_011;
        case 12: return &M_012;
        case 13: return &M_013;
        case 14: return &M_014;
        case 15: return &M_015;
        case 1001: return &M_1001;
        case 1002: return &M_1002;
        case 1003: return &M_1003;
        case 1004: return &M_1004;
        case 1005: return &M_1005;
        case 1006: return &M_1006;
        case 1007: return &M_1007;
        case 1008: return &M_1008;
        case 1009: return &M_1009;
        case 1010: return &M_1010;
        default: return NULL;
    }
}
