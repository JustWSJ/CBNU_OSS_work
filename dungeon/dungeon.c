#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Character.h"
#include "console_util.h"
#include "Event.h"
#include "key_input.h"
#include "dungeon.h"
#include "saveLoad.h"
#include "Character.h"

#define INDENT 1
#define GAP 1

// 파일 저장 함수
void SaveToFile(const char* filename, char** map, int size) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        gotoxy(0,49);
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
    return;
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

void deleteDungeonFiles1(int floor) {
    char filename_arr1[20];
    // 파일 이름 생성
    sprintf(filename_arr1, "map/Floor%d", floor);
    // arr1 파일 삭제
    if (remove(filename_arr1) == 0) {
        ;
    } else {
        ;
    }
}
void deleteDungeonFiles2(int floor) {
    char filename_arr2[20];
    // 파일 이름 생성
    sprintf(filename_arr2, "map/Floor%dfac", floor);
    // arr1 파일 삭제
    if (remove(filename_arr2) == 0) {
        ;
    } else {
        ;
    }
}

// 던전 탐사
void Dungeon() {
    Character *player = getPlayer();
    loadStatus(player);
    int floor = SelectFloor(player->Maxfloor);

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
            } else if (isClear(floor)) {
                option = DungeonEntrance(floor);
                player->Maxfloor = floor / 10;
                saveStatus(player);
            }
            else {
                DungeonAdventure(floor);
            }
        } else {
            clearScreen();
            printf("마을로 돌아갑니다. ▼\n");
            wait();
            clearScreen();
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
    sprintf(filename_arr1, "map/Floor%d", floor);
    sprintf(filename_arr2, "map/Floor%dfac", floor);

    // 이미 저장된 맵이 있는지 확인
    map = LoadFromFile(filename_arr1, size); // arr1 불러오기
    //map_fac = LoadFromFile(filename_arr2, size); // arr2 불러오기

    if (!map) { // 저장된 맵이 없으면 새로 생성
        if(floor % 10 != 0){
            map = CreateDungeon(floor, size); // arr1 생성
        } else{
            map = CreatebossDungeon(floor, size)
        }
        SaveToFile(filename_arr1, map, size);      // arr1 저장
    }
    deleteDungeonFiles2(floor);
    map_fac = allocationfactor(floor, size, map); // arr2 생성
    SaveToFile(filename_arr2, map_fac, size); // arr2 저장
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
    MoveDungeon(map, map_fac, size, floor);
    SaveToFile(filename_arr1, map, size);
    deleteDungeonFiles2(floor);

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

    printf("던전 입구 선택\n");

    while (1) {
        if (updated) {
            for (int i = 0; i <= MENU_COUNT; i++) { // 메뉴 개수: 0 ~ MENU_COUNT
                gotoxy(INDENT, GAP + i);
                if (i == selected) {
                    SetColor(0x0E); // 선택된 항목 강조
                    printf("> %d", floors[i]);
                    SetColor(0x0F);
                } else {
                    printf("  %d", floors[i]);
                }
            }
            updated = 0; // 화면 업데이트 완료
        }

        if (isKeyPressed(KEY_UP)) {
            selected = (selected - 1 + (MENU_COUNT + 1)) % (MENU_COUNT + 1); // 위로 이동 (순환)
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            selected = (selected + 1) % (MENU_COUNT + 1); // 아래로 이동 (순환)
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            clearScreen();
            return floors[selected]; // 선택된 층 반환
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
    int MENU_COUNT = 2; // 메뉴 개수는 2개

    while (1) {
        if (updated) {
            clearScreen();
            printf(" 던전 %d층\n", Floor);
            for (int i = 0; i < MENU_COUNT; i++) { // 메뉴 개수만큼 반복
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
            choice = (choice - 1 + MENU_COUNT) % MENU_COUNT; // 위로 이동
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_DOWN)) {
            choice = (choice + 1) % MENU_COUNT; // 아래로 이동
            updated = 1;
            Sleep(150);
        } else if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            Sleep(150);
            clearScreen();
            return choice; // 선택한 옵션 반환
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
        return 5;
    } else if (floor / 10 < 1) {
        return 7;
    } else if (floor > 90) {
        return 17;
    } else return 11;
}

char** CreateDungeon(int floor, int size) {
    char** dungeon = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                dungeon[i][j] = 'W'; // 테두리 벽
            } else if (rand() % 5 == 0) { // 내부에 중간 벽 'w' 랜덤 배치
                dungeon[i][j] = 'w';
            } else {
                dungeon[i][j] = 'R'; // 기본 길
            }
        }
    }
    dungeon[1][size / 2] = 'R';
    return dungeon;
}
char** CreatebossDungeon(int floor, int size) {
    char** dungeon = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        dungeon[i] = (char*)malloc(size * sizeof(char));

        for (int j = 0; j < size; j++) {
            if (i == 0 || i == 1 || i == size - 1 || i == size - 1 || j == 0 || j == size - 1) {
                dungeon[i][j] = 'W'; // 테두리 벽
            } else if (rand() % 5 == 0) { // 내부에 중간 벽 'w' 랜덤 배치
                dungeon[i][j] = 'w';
            } else {
                dungeon[i][j] = 'R'; // 기본 길
            }
        }
    }
    dungeon[1][size / 2] = 'R';
    return dungeon;
}

char** allocationfactor(int floor, int size, char** map, Character* player) {
    char** map_fac = (char**)malloc(size * sizeof(char*));
    if(floor % 10 != 0){
        for (int i = 0; i < size; i++) {
            map_fac[i] = (char*)malloc(size * sizeof(char)); // 각 행에 메모리 할당
        }

        int startX = 0, startY = size / 2; // 입구 위치
        int exitX  = rand() % (size - 2) + 1, exitY = rand() % (size - 2) + 1; // 출구 랜덤 위치
        

        int validPath = 0; // 경로 유효성 플래그
        while (!validPath) {
            // 요소 초기화
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    map_fac[i][j] = 'R'; // 기본 길
                }
            }

            // 입구와 출구 배치
            exitX  = rand() % (size - 2) + 1;
            exitY = rand() % (size - 2) + 1;
            while (map[exitX][exitY] == 'w' || map[exitX][exitY] == 'W') {
                exitX = rand() % (size - 2) + 1;
                exitY = rand() % (size - 2) + 1;
            }
            map_fac[startX][startY] = 'E'; // 입구
            map_fac[exitX][exitY] = 'X';   // 출구

            // 랜덤 요소 배치
            place_element('B', floor / 10 + 2, size, map_fac); // 전투 요소
            place_element('F', floor / 15 + 1, size, map_fac); // 강제 이벤트
            //place_element('I', floor / 20 + 1, size, map_fac); // 아이템 수색
            //place_element('S', floor / 10 + 3, size, map_fac); // 수색 후 전투

            // 경로 유효성 검사
            validPath = isValidPath(map_fac, size, startX, startY, exitX, exitY);

            if (!validPath) {
                // 경로가 유효하지 않으면 메모리 해제
                for (int i = 0; i < size; i++) free(map_fac[i]);
                free(map_fac);
            }
        }
    }
    //  make boss room
    else if(player->Maxfloor <= floor){
        for (int i = 0; i < size; i++) {
            map_fac[i] = (char*)malloc(size * sizeof(char)); // 각 행에 메모리 할당
        }

        int startX = 0, startY = size / 2; // 입구 위치
        int exitX  = 3, exitY = 3; // 출구 랜덤 위치
        

        int validPath = 0; // 경로 유효성 플래그
        while (!validPath) {
            // 요소 초기화
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    map_fac[i][j] = 'R'; // 기본 길
                }
            }

            // 입구와 출구 배치
            exitX  = 3;
            exitY = 3;
            
            map_fac[startX][startY] = 'E'; // 입구
            map_fac[exitX][exitY] = 'X';   // 출구

            // 랜덤 요소 배치
            place_element('K', floor / 10 + 2, size, map_fac); // boss
            //place_element('F', floor / 15 + 1, size, map_fac); // 강제 이벤트
            //place_element('I', floor / 20 + 1, size, map_fac); // 아이템 수색
            //place_element('S', floor / 10 + 3, size, map_fac); // 수색 후 전투

            // 경로 유효성 검사
            validPath = isValidPath(map_fac, size, startX, startY, exitX, exitY);

            if (!validPath) {
                // 경로가 유효하지 않으면 메모리 해제
                for (int i = 0; i < size; i++) free(map_fac[i]);
                free(map_fac);
            }
        }
    }

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
void MoveDungeon(char **map, char **map_fac, int size, int floor) {
    int locv = 0;                 // 플레이어의 현재 세로 위치 (행)
    int loch = size / 2;          // 플레이어의 현재 가로 위치 (열)

    // 초기 위치 출력
    draw_loc(locv, loch);

    // **6. 최초 이동 시작 조건 처리**
    while(1){
        if (isKeyPressed(KEY_DOWN) && locv + 1 < size - 1) { // 최초로 아래 방향 이동을 요구
            int next_locv = locv + 1;
            if (map[next_locv][loch] != 'W' && map[next_locv][loch] != 'w') {
                Erase_loc(locv, loch);
                locv = next_locv;
                draw_loc(locv, loch);
                Sleep(150);
                break; // 아래로 이동 후 게임 진행
            }
        }
    }

    while (1) {
        // **1. 현재 위치 이벤트 확인**
        int P_Event = check_P_Event(map_fac[locv][loch]);
        if (P_Event) {
            if (P_Event == 4) { // 출구 이벤트
                gotoxy(1, size + 2);
                printf("You found the exit!      ");
                gotoxy(1, size + 3);
                printf("Exiting floor...▼        \n");
                wait();
                return; // 던전 탐험 종료
            } else {
                gotoxy(1, size + 2);
                //printf("Processing event: %c...  \n", map_fac[locv][loch]);
                callEvent(map_fac[locv][loch], floor);
                map_fac[locv][loch] = 'R'; // 이벤트 완료 후 기본 길로 변경
            }
        }

        // 이동 키 입력 처리
        if (isKeyPressed(KEY_UP)) { // 위쪽 키 입력
            int next_locv = locv - 1;
            int next_loch = loch;
            if (next_locv > 0 && map[next_locv][next_loch] != 'W' && map[next_locv][next_loch] != 'w') {
                Erase_loc(locv, loch);
                locv = next_locv;
                draw_loc(locv, loch);
                Sleep(150);
            } else if (map[next_locv][next_loch] == 'w') {
                map[next_locv][next_loch] = 'W';
                gotoxy((next_loch * 2) + INDENT, next_locv + GAP);
                printf("□");
                Sleep(150);
            }
        }

        if (isKeyPressed(KEY_DOWN)) { // 아래쪽 키 입력
            int next_locv = locv + 1;
            int next_loch = loch;
            if (next_locv < size - 1 && map[next_locv][next_loch] != 'W' && map[next_locv][next_loch] != 'w') {
                Erase_loc(locv, loch);
                locv = next_locv;
                draw_loc(locv, loch);
                Sleep(150);
            } else if (map[next_locv][next_loch] == 'w') {
                map[next_locv][next_loch] = 'W';
                gotoxy((next_loch * 2) + INDENT, next_locv + GAP);
                printf("□");
                Sleep(150);
            }
        }

        if (isKeyPressed(KEY_LEFT)) { // 왼쪽 키 입력
            int next_locv = locv;
            int next_loch = loch - 1;
            if (next_loch > 0 && map[next_locv][next_loch] != 'W' && map[next_locv][next_loch] != 'w') {
                Erase_loc(locv, loch);
                loch = next_loch;
                draw_loc(locv, loch);
                Sleep(150);
            } else if (map[next_locv][next_loch] == 'w') {
                map[next_locv][next_loch] = 'W';
                gotoxy((next_loch * 2) + INDENT, next_locv + GAP);
                printf("□");
                Sleep(150);
            }
        }

        if (isKeyPressed(KEY_RIGHT)) { // 오른쪽 키 입력
            int next_locv = locv;
            int next_loch = loch + 1;
            if (next_loch < size - 1 && map[next_locv][next_loch] != 'W' && map[next_locv][next_loch] != 'w') {
                Erase_loc(locv, loch);
                loch = next_loch;
                draw_loc(locv, loch);
                Sleep(150);
            } else if (map[next_locv][next_loch] == 'w') {
                map[next_locv][next_loch] = 'W';
                gotoxy((next_loch * 2) + INDENT, next_locv + GAP);
                printf("□");
                Sleep(150);
            }
        }

        /*
        // **5. 탐사 키 입력 처리**
        if (isKeyPressed(KEY_ENTER) || isKeyPressed(KEY_SPACE)) {
            if (map_fac[locv][loch] != 'R') { // 현재 위치가 탐사 가능한 이벤트라면
                gotoxy(1, size + 2);
                //printf("Exploring: %c...         \n", map_fac[locv][loch]);
                //callEvent(map_fac[locv][loch]);
                printf("212");
                wait();
                map_fac[locv][loch] = 'R'; // 탐사 완료 후 기본 길로 변경
            } else {
                gotoxy(1, size + 2);
                printf("Nothing to explore here. \n");
            }
            Sleep(190);
        }*/
    }
}

int isValidPath(char **map, int size, int startX, int startY, int exitX, int exitY) {
    int visited[size][size];
    memset(visited, 0, sizeof(visited));

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    int stackX[size * size], stackY[size * size];
    int top = -1;
    stackX[++top] = startX + 1;
    stackY[top] = startY;

    while (top >= 0) {
        int x = stackX[top];
        int y = stackY[top--];

        if (x == exitX && y == exitY) return 1;

        if (visited[x][y]) continue;
        visited[x][y] = 1;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx > 0 && nx < size && ny > 0 && ny < size &&
                !visited[nx][ny] && map[nx][ny] != 'W' && map[nx][ny] != 'w') {
                stackX[++top] = nx;
                stackY[top] = ny;
            }
        }
    }
    return 0; // 경로 없음
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
// *F (Force): 강제 이벤트
// *K (King): 보스 전투
// *X (eXit): 출구