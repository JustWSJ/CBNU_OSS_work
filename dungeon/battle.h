#ifndef BATTLE_H
#define BATTLE_H

#include "Character.h"
#include "Monster.h"

// 함수 선언
void attack(Character *attacker, Character *defender);
int escape(Character *player, Monster *enemy);
int dodge(Character *attacker, Character *defender);
void useItem(Character *player);
void displayStats(Character *character);
void battle(Character *player, Monster *enemy);

#endif



