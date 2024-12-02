#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console_util.h"
#include "key_input.h"
#include "dungeon.h"

#define INDENT 1            // 메뉴의 왼쪽 들여쓰기
#define GAP 1

void Dungeon(){
    int floor = SelectFloor(10);
    int option = DungeonEntrance(floor);
    while (1){
        if (option==0) {
            floor++;
            if (floor == 100) {
                clearScreen();
                printf("Dungeon Clear!\n");
                wait();
                exit(0);
            } else if (isClear(floor)) option = DungeonEntrance(floor);
            else DungeonAdventure(floor);

        } else {
            clearScreen();
            printf("마을로 돌아갑니다.\n");
            wait();
            return;
        }
    }
    return;
}

void DungeonAdventure(int floor){
    clearScreen();
    int size = DungeonSize(floor);
    char **map;
    map = CreateDungeon(floor, size);
    if (*map == NULL) {
        printf("NULL");
    } else {
        MoveDungeon(map, size);
    }
    return;
}

int SelectFloor(int MENU_COUNT){
    clearScreen();
    const int floors[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}; // 층수 배열
    int selected = 0;       // 선택된 항목 인덱스
    int updated = 1;        // 화면 갱신 여부 (1: 갱신 필요, 0: 갱신 불필요)

    printf("던전 입구 선택");
    while (1) {
        // 메뉴 출력 (updated가 1일 때만)
        if (updated) {
                for (int i = 0; i < MENU_COUNT; i++) {
                gotoxy(INDENT, GAP + i);
                if (i == selected) {
                    SetColor(0x0E); // 선택된 메뉴: 노란색
                    printf("> %d", floors[i]);
                    SetColor(0x0F); // 기본 색상 흰색으로 복구
                } else {
                    printf("  %d", floors[i]);
                }
            }
            updated = 0; // 출력 후 갱신 플래그 해제
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + MENU_COUNT) % MENU_COUNT; // 위로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % MENU_COUNT; // 아래로 이동
            updated = 1; // 선택 항목 변경, 화면 갱신 필요
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            return floors[selected]; // 선택된 층 반환
        }
    }
}

int DungeonEntrance(int Floor){
    clearScreen();
    printf(" 던전 %d층\n", Floor);
    const char* options[] = {
        "다음 층으로 가기",
        "마을로 돌아가기"
    };
    int choice = 0;    // 선택된 항목 인덱스
    int updated = 1;   // 화면 갱신 여부 (1: 갱신 필요, 0: 갱신 불필요)
    int menu_count = sizeof(options) / sizeof(options[0]);

    while (1) {
        // 메뉴 출력 (updated가 1일 때만)
        if (updated) {
            clearScreen();
            printf(" 던전 %d층\n", Floor);
            for (int i = 0; i < menu_count; i++) {
                gotoxy(INDENT, GAP + i);
                if (i == choice) {
                    SetColor(0x0E);
                    printf("> %s", options[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %s", options[i]);
                }
            }
            updated = 0; // 출력 후 갱신 플래그 해제
        }

        // 키 입력 처리
        if (isKeyPressed(KEY_UP)) {
            choice = (choice - 1 + menu_count) % menu_count;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            choice = (choice + 1) % menu_count;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            clearScreen();
            return choice; // 선택된 메뉴 반환 (0: 다음 층, 1: 마을로 돌아가기)
        }
    } 
}

int isClear(int floor){
    // 나중에 &&으로 조건 추가해야함 일단은 10층 단위가 클리어 된 판정
    if (floor % 10 == 0) {
        return 1;
    } else return 0;
}

int DungeonSize(int floor) {
    if (isClear(floor) == 0 && floor % 10 == 0) {
        // 보스 방 처리
        return -1;
    } else if (floor % 10 == 0) {
        //클리어 된 보스 방
        return -2;
    } else if (floor / 10 < 1) {
        // 저층 던전 처리
        return 7;
    } else {
        // 나머지 층
        return 17;
    }
}

char** CreateDungeon(int floor, int size) {
    
    if (size == -1 || size == -2) {
        return NULL;
    }

    // 이차원 배열 동적 할당
    char** dungeon = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) dungeon[i][j] = 'W'; // 테두리 W로 설정
            else dungeon[i][j] = 'R'; // 나머지 길
        }
    }

    dungeon[0][size/2] = 'E';
    dungeon[size-2][size-2] = 'X'; //테스트용 나중에 랜덤 배정
    dungeon[1][size/2] = 'B';
    dungeon[2][size/2] = 'F';
    dungeon[3][size/2] = 'K';
    dungeon[4][size/2] = 'S';
    dungeon[5][size/2] = 'I';

    //draw Map
    clearScreen();
    printf(" 던전 %d층: %dx%d  이동: 방향키, 탐사: ENTER/SPACE", floor, size - 2, size - 2);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gotoxy(INDENT + (j * 2), GAP + i);
            if (dungeon[i][j] == 'W'){
                printf("□");
            } else if (dungeon[i][j] == 'E') {
                printf("●");
            }
        }
    }

    return dungeon;
}

void MoveDungeon(char **map, int size){
    int locv, loch;
    locv = 0;
    loch = size/2;
    waitKeyDown();
    gotoxy((loch*2) + INDENT, locv + GAP);
    printf("□");
    gotoxy((loch*2) + INDENT, (++locv) + GAP);
    printf("●");
    Sleep(150);
    //여기서부터 반복에, 강제이벤트/보스 체크 후 아니면 이벤트 진행 확인 및 무빙(벽 확인)
    while(1){
        int P_Event = check_P_Event(map[locv][loch]);
        if (P_Event) {
            if (map[locv][loch] == 'X') break;
            else {
                gotoxy(40,1); //테스트용
                printf("%c scaned.", map[locv][loch]); // 테스트용
                //콜이벤트(char);
                map[locv][loch] = 'R';
            }
        }
        while(map[locv][loch] == 'R' || map[locv][loch] == 'S'|| map[locv][loch] == 'I'){
            if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
                //R이면 뭐 없음
                if (map[locv][loch]=='R') {
                    gotoxy(40,1);
                    printf("%c scaned.", map[locv][loch]); //테스트용
                } else if (map[locv][loch] == 'S') {
                    //S이면 전투
                    gotoxy(40,1);
                    printf("%c scaned.", map[locv][loch]); //테스트용
                    map[locv][loch] = 'R';
                } else if (map[locv][loch] == 'I') {
                    //I이면 랜덤 이벤트
                    gotoxy(40,1);
                    printf("%c scaned.", map[locv][loch]); //테스트용
                    map[locv][loch] = 'R';
                }
                Sleep(150);
            }
            // 이동위치한 곳 벽인지 확인 후 브레이크! 
            if (isKeyPressed(KEY_UP) && locv - 1 > 0 && !check_W(map[locv - 1][loch])) {
                Erase_loc(locv, loch);
                locv--;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_DOWN) && locv + 1 < size - 1 && !check_W(map[locv + 1][loch])){
                Erase_loc(locv, loch);
                locv++;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_LEFT) && loch - 1 > 0 && !check_W(map[locv][loch - 1])){
                Erase_loc(locv, loch);
                loch--;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_RIGHT) && loch + 1 < size - 1 && !check_W(map[locv][loch + 1])){
                Erase_loc(locv, loch);
                loch++;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
        }
    }
    return;
}

int check_P_Event(char c){
    if (c == 'B') return 1;
    else if (c == 'F') return 2;
    else if (c == 'K') return 3;
    else if (c == 'X') return 4;
    else return 0;
}

int check_W(char c){
    if (c == 'W') {
        return 1;
    } else return 0;
}

void Erase_loc(int locv, int loch){
    gotoxy((loch*2) + INDENT, locv + GAP);
    printf("  ");
    return;
}

void draw_loc(int locv, int loch){
    gotoxy((loch*2) + INDENT, locv + GAP);
    printf("●");
    return;
}

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