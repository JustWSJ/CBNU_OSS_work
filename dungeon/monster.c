#include <stdio.h>
#include "Monster.h"

// 일반 몬스터 추가
Monster M_001 = {"Goblin", 10, 2, 4};
Monster M_002 = {"Orc", 40, 10, 5};
Monster M_003 = {"Slime", 90, 2, 10};
Monster M_004 = {"Skeleton", 60, 1, 20};
Monster M_005 = {"Bandit", 40, 20, 1};
Monster M_006 = {"Wolf", 20, 5, 3};
Monster M_007 = {"Giant Bat", 50, 8, 8};
Monster M_008 = {"M_008", 70, 15, 10};
Monster M_009 = {"M_009", 30, 12, 7};
Monster M_010 = {"M_010", 55, 18, 5};
Monster M_011 = {"M_011", 65, 20, 8};
Monster M_012 = {"M_012", 80, 25, 12};
Monster M_013 = {"M_013", 45, 10, 15};
Monster M_014 = {"M_014", 75, 22, 10};
Monster M_015 = {"M_015", 60, 15, 20};
Monster M_016 = {"M_016", 70, 18, 12};
Monster M_017 = {"M_017", 35, 15, 20};
Monster M_018 = {"M_018", 85, 25, 15};
Monster M_019 = {"M_019", 50, 20, 10};
Monster M_020 = {"M_020", 120, 30, 25};
Monster M_021 = {"M_021", 60, 22, 18};
Monster M_022 = {"M_022", 90, 28, 22};
Monster M_023 = {"M_023", 40, 18, 30};
Monster M_024 = {"M_024", 80, 26, 20};
Monster M_025 = {"M_025", 70, 20, 25};
Monster M_026 = {"M_026", 55, 15, 8};
Monster M_027 = {"M_027", 45, 17, 18};
Monster M_028 = {"M_028", 65, 23, 20};
Monster M_029 = {"M_029", 75, 20, 25};
Monster M_030 = {"M_030", 85, 28, 18};
Monster M_031 = {"M_031", 110, 35, 15};
Monster M_032 = {"M_032", 50, 12, 25};
Monster M_033 = {"M_033", 100, 25, 30};
Monster M_034 = {"M_034", 90, 32, 28};
Monster M_035 = {"M_035", 95, 30, 22};

// 보스 몬스터 추가
Monster M_1001 = {"Dark Lord", 500, 80, 30};
Monster M_1002 = {"Fire Dragon", 600, 100, 40};
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
        case 16: return &M_016;
        case 17: return &M_017;
        case 18: return &M_018;
        case 19: return &M_019;
        case 20: return &M_020;
        case 21: return &M_021;
        case 22: return &M_022;
        case 23: return &M_023;
        case 24: return &M_024;
        case 25: return &M_025;
        case 26: return &M_026;
        case 27: return &M_027;
        case 28: return &M_028;
        case 29: return &M_029;
        case 30: return &M_030;
        case 31: return &M_031;
        case 32: return &M_032;
        case 33: return &M_033;
        case 34: return &M_034;
        case 35: return &M_035;
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
