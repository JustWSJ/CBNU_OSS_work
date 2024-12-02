#ifndef DUNGEON_H
#define DUNGEON_H

void Dungeon();
int SelectFloor(int MENU_COUNT);
int DungeonEntrance(int Floor);
int isClear(int floor);
int DungeonSize(int floor);
char** CreateDungeon(int floor, int size);
void DungeonAdventure(int floor);
void MoveDungeon(char **map, int size);
int check_P_Event(char c);
int check_W(char c);
void Erase_loc(int locv, int loch);
void draw_loc(int locv, int loch);

#endif
