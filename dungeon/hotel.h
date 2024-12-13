#ifndef HOTEL_H
#define HOTEL_H

#include <stdbool.h>
#include "character.h"

// 함수 선언
void createPortalToTown(const char* dungeonName, int currentFloor);
void restAtHotel(Character* player);
bool checkFloorClear(int currentFloor);
void saveProgress(const char* dungeonName, int clearedFloor);
Character loadProgress(void);

#endif // HOTEL_H
