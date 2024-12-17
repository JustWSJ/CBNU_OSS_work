#ifndef ALLOWSTATUS_H
#define ALLOWSTATUS_H
#include "Character.h"

void updateStat(Character *player, int statID, int delta);
int getStatValue(Character *player, int statID);
void showStatusAllocation(Character *player);

#endif