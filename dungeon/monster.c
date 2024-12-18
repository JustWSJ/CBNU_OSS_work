#include <stdio.h>
#include "monster.h"

// 일반 몬스터 추가
Monster M_000 = {"연습용 허수아비", 5, 1, 1};
Monster M_001 = {"M_001", 20, 2, 1};
Monster M_002 = {"M_002", 25, 3, 1};
Monster M_003 = {"M_003", 30, 4, 2};
Monster M_004 = {"M_004", 35, 5, 2};
Monster M_005 = {"M_005", 40, 6, 3};
Monster M_006 = {"M_006", 45, 7, 3};
Monster M_007 = {"M_007", 50, 8, 4};
Monster M_008 = {"M_008", 55, 9, 4};
Monster M_009 = {"M_009", 60, 10, 5};
Monster M_010 = {"M_010", 65, 11, 5};
Monster M_011 = {"M_011", 70, 12, 6};
Monster M_012 = {"M_012", 75, 13, 6};
Monster M_013 = {"M_013", 80, 14, 7};
Monster M_014 = {"M_014", 85, 15, 7};
Monster M_015 = {"M_015", 90, 16, 8};
Monster M_016 = {"M_016", 95, 17, 8};
Monster M_017 = {"M_017", 100, 18, 9};
Monster M_018 = {"M_018", 105, 19, 9};
Monster M_019 = {"M_019", 110, 20, 10};
Monster M_020 = {"M_020", 115, 20, 10};
Monster M_021 = {"M_021", 120, 20, 11};
Monster M_022 = {"M_022", 125, 20, 11};
Monster M_023 = {"M_023", 130, 20, 12};
Monster M_024 = {"M_024", 135, 20, 12};
Monster M_025 = {"M_025", 140, 20, 13};
Monster M_026 = {"M_026", 145, 20, 13};
Monster M_027 = {"M_027", 150, 20, 14};
Monster M_028 = {"M_028", 155, 20, 14};
Monster M_029 = {"M_029", 160, 20, 15};
Monster M_030 = {"M_030", 165, 20, 15};
Monster M_031 = {"M_031", 170, 20, 16};
Monster M_032 = {"M_032", 175, 20, 16};
Monster M_033 = {"M_033", 180, 20, 17};
Monster M_034 = {"M_034", 185, 20, 17};
Monster M_035 = {"M_035", 190, 20, 18};
Monster M_036 = {"M_036", 195, 20, 18};
Monster M_037 = {"M_037", 200, 20, 19};
Monster M_038 = {"M_038", 205, 20, 19};
Monster M_039 = {"M_039", 210, 20, 20};
Monster M_040 = {"M_040", 215, 20, 20};
Monster M_041 = {"M_041", 220, 20, 20};
Monster M_042 = {"M_042", 225, 20, 20};
Monster M_043 = {"M_043", 230, 20, 20};
Monster M_044 = {"M_044", 235, 20, 20};
Monster M_045 = {"M_045", 240, 20, 20};
Monster M_046 = {"M_046", 245, 20, 20};
Monster M_047 = {"M_047", 250, 20, 20};
Monster M_048 = {"M_048", 255, 20, 20};
Monster M_049 = {"M_049", 260, 20, 20};
Monster M_050 = {"M_050", 265, 20, 20};

// 보스 몬스터 추가
Monster M_1001 = {"M_1001", 500, 80, 30};
Monster M_1002 = {"M_1002", 600, 100, 40};
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
        //  common
        case 0: return &M_000;
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
        case 36: return &M_036;
        case 37: return &M_037;
        case 38: return &M_038;
        case 39: return &M_039;
        case 40: return &M_040;
        case 41: return &M_041;
        case 42: return &M_042;
        case 43: return &M_043;
        case 44: return &M_044;
        case 45: return &M_045;
        case 46: return &M_046;
        case 47: return &M_047;
        case 48: return &M_048;
        case 49: return &M_049;
        case 50: return &M_050;
        //  boss
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
