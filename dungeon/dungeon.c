#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "console_util.h"
#include "key_input.h"
#include "dungeon.h"

#define INDENT 1
#define GAP 1

// 파일 저장 함수
void SaveToFile(const char* filename, char** map, int size) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("파일 저장에 실패했습니다: %s\n", filename);
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, "%c", map[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// 파일에서 맵을 불러오는 함수
char** LoadFromFile(const char* filename, int size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL; // 파일이 없으면 NULL 반환
    }

    char** map = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        map[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            fscanf(file, " %c", &map[i][j]); // 파일에서 문자 읽기
        }
    }
    fclose(file);
    return map;
}

// 던전 탐사
void Dungeon() {
    int floor = SelectFloor(10);
    int option = DungeonEntrance(floor);
    while (1) {
        if (option == 0) {
            floor++;
            if (floor == 100) {
                //원래는 100층 보스 호출
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
}

// 던전 탐험
void DungeonAdventure(int floor) {
    clearScreen();
    int size = DungeonSize(floor);
    char** map;
    char** map_fac;

    // 파일 이름 생성
    char filename_arr1[20], filename_arr2[20];
    sprintf(filename_arr1, "map\\Floor%d", floor);
    sprintf(filename_arr2, "map\\Floor%dfac", floor);

    // 이미 저장된 맵이 있는지 확인
    map = LoadFromFile(filename_arr1, size); // arr1 불러오기
    map_fac = LoadFromFile(filename_arr2, size); // arr2 불러오기

    if (!map) { // 저장된 맵이 없으면 새로 생성
        map = CreateDungeon(floor, size); // arr1 생성
        map_fac = allocationfactor(floor, size); // arr2 생성

        SaveToFile(filename_arr1, map, size);      // arr1 저장
        SaveToFile(filename_arr2, map_fac, size); // arr2 저장
    }
    //draw Map
    printf(" 던전 %d층: %dx%d  이동: 방향키, 탐사: ENTER/SPACE", floor, size - 2, size - 2);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gotoxy(INDENT + (j * 2), GAP + i);
            if (map[i][j] == 'W') printf("□");
        }
    }
    gotoxy(INDENT + ((size/2) * 2), GAP + 0);
    printf("●");
    // 탐사 시작
    MoveDungeon(map, map_fac, size);

    // 메모리 해제
    for (int i = 0; i < size; i++) {
        free(map[i]);
        free(map_fac[i]);
    }
    free(map);
    free(map_fac);

    return;
}

// 층 선택
int SelectFloor(int MENU_COUNT) {
    clearScreen();
    const int floors[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    int selected = 0;
    int updated = 1;

    printf("던전 입구 선택");
    while (1) {
        if (updated) {
            for (int i = 0; i < MENU_COUNT; i++) {
                gotoxy(INDENT, GAP + i);
                if (i == selected) {
                    SetColor(0x0E);
                    printf("> %d", floors[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %d", floors[i]);
                }
            }
            updated = 0;
        }

        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + MENU_COUNT) % MENU_COUNT;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % MENU_COUNT;
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            return floors[selected];
        }
    }
}

// 입구 선택
int DungeonEntrance(int Floor) {
    clearScreen();
    printf(" 던전 %d층\n", Floor);
    const char* options[] = {"다음 층으로 가기", "마을로 돌아가기"};
    int choice = 0;
    int updated = 1;
    int menu_count = sizeof(options) / sizeof(options[0]);

    while (1) {
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
            updated = 0;
        }

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
            return choice;
        }
    }
}

// 클리어 확인
int isClear(int floor) {
    if (floor % 10 == 0) {
        return 1;
    } else return 0;
}

// 던전 크기 반환
int DungeonSize(int floor) {
    if (isClear(floor) == 0 && floor % 10 == 0) {
        return -1;
    } else if (floor % 10 == 0) {
        return -2;
    } else if (floor / 10 < 1) {
        return 7;
    } else {
        return 17;
    }
}

// 던전 생성
char** CreateDungeon(int floor, int size) {
    if (size == -1 || size == -2) {
        return NULL;
    }

    char** dungeon = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                dungeon[i][j] = 'W';
            } else {
                dungeon[i][j] = 'R';
            }
        }
    }

    //dungeon[0][size / 2] = 'E';
    return dungeon;
}

// 이벤트 배열 생성
char** allocationfactor(int floor, int size) {
    char** map_fac = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        map_fac[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            map_fac[i][j] = 'R'; // 기본적으로 길로 채움
        }
    }

    // 난이도 조절을 위한 요소 수 계산
    int num_battle = floor / 10 + 2; // B 요소 개수 (최소 2개, 층수 증가마다 추가)
    int num_force = floor / 15 + 1; // F 요소 개수 (최소 1개, 층수 증가마다 추가)
    int num_inventory = floor / 20 + 1; // I 요소 개수 (최소 1개, 층수 증가마다 추가)
    int num_search = floor / 10 + 3; // S 요소 개수 (최소 3개, 층수 증가마다 추가)
    int num_wall = floor / 8 + 3; // w 요소 개수 (최소 3개, 층수 증가마다 추가)
    int num_exit = 1; // X 요소는 항상 1개

    // 요소 배치
    srand((unsigned)time(NULL)); // 랜덤 시드 설정

    place_element('B', num_battle, size, map_fac);     // 강제 전투
    place_element('F', num_force, size, map_fac);     // 강제 이벤트
    place_element('I', num_inventory, size, map_fac); // 수색 후 아이템
    place_element('S', num_search, size, map_fac);    // 수색 후 전투
    place_element('w', num_wall, size, map_fac);      // 미로 중간의 벽
    place_element('X', num_exit, size, map_fac);      // 출구 (항상 1개)

    return map_fac;
}

// 요소를 랜덤하게 배치
void place_element(char element, int count, int size, char **map_fac) {
    while (count > 0) {
        int i = rand() % size;
        int j = rand() % size;
        if (map_fac[i][j] == 'R' && i > 0 && i < size - 1 && j > 0 && j < size - 1) { // 빈 공간 중앙에만 배치
            map_fac[i][j] = element;
            count--;
        }
    }
}

// 플레이어 이동
void MoveDungeon(char **map, char **map_fac, int size){
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
        int P_Event = check_P_Event(map_fac[locv][loch]);
        if (P_Event) {
            if (map_fac[locv][loch] == 'X') {
                gotoxy(40,1);
                printf("%c scaned.", map_fac[locv][loch]); //테스트용
                wait();
                break;
            } else {
                gotoxy(40,1); //테스트용
                printf("%c scaned.", map_fac[locv][loch]); // 테스트용
                //콜이벤트(char);
                map_fac[locv][loch] = 'R';
            }
        }
        while(map_fac[locv][loch] == 'R' || map_fac[locv][loch] == 'S'|| map_fac[locv][loch] == 'I'){
            if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
                //R이면 뭐 없음
                if (map_fac[locv][loch]=='R') {
                    gotoxy(40,1);
                    printf("%c scaned.", map_fac[locv][loch]); //테스트용
                } else if (map_fac[locv][loch] == 'S') {
                    //S이면 전투
                    gotoxy(40,1);
                    printf("%c scaned.", map_fac[locv][loch]); //테스트용
                    map_fac[locv][loch] = 'R';
                } else if (map_fac[locv][loch] == 'I') {
                    //I이면 랜덤 이벤트
                    gotoxy(40,1);
                    printf("%c scaned.", map_fac[locv][loch]); //테스트용
                    map_fac[locv][loch] = 'R';
                }
                Sleep(150);
            }
            // 이동위치한 곳 벽인지 확인 후 브레이크! 
            if (isKeyPressed(KEY_UP) && locv - 1 > 0 && !check_W(map[locv - 1][loch]) && !check_w(map_fac[locv - 1][loch])) {
                Erase_loc(locv, loch);
                locv--;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_DOWN) && locv + 1 < size - 1 && !check_W(map[locv + 1][loch])&& !check_w(map_fac[locv + 1][loch])){
                Erase_loc(locv, loch);
                locv++;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_LEFT) && loch - 1 > 0 && !check_W(map[locv][loch - 1])&& !check_w(map_fac[locv][loch - 1])){
                Erase_loc(locv, loch);
                loch--;
                draw_loc(locv, loch);
                Sleep(150);
                break;
            }
            if (isKeyPressed(KEY_RIGHT) && loch + 1 < size - 1 && !check_W(map[locv][loch + 1])&& !check_w(map_fac[locv][loch + 1])){
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

int check_w(char c){
    if (c == 'w') {
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