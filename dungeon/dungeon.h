#ifndef DUNGEON_H
#define DUNGEON_H

void Dungeon();
int SelectFloor(int MENU_COUNT);
int DungeonEntrance(int Floor);
int isClear(int floor);
int DungeonSize(int floor);
char** CreateDungeon(int floor, int size);
void DungeonAdventure(int floor);
void MoveDungeon(char **map, char **map_fac, int size);
int check_P_Event(char c);
int check_W(char c);
int check_w(char c);
void Erase_loc(int locv, int loch);
void draw_loc(int locv, int loch);
char** allocationfactor(int floor, int size, char** map); // 추가: 이벤트 배열 생성 함수
void SaveToFile(const char* filename, char** map, int size); // 추가: 파일 저장 함수
char** LoadFromFile(const char* filename, int size);        // 파일 로드 함수
void place_element(char element, int count, int size, char **map_fac); //요소 랜덤 배치 함수
int isValidPath(char **map, int size, int startX, int startY, int exitX, int exitY);
void deleteDungeonFiles1(int floor);
void deleteDungeonFiles2(int floor);

#endif


