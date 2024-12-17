#ifndef BATTLE_H
#define BATTLE_H

#include "Character.h"
#include "monster.h"

// 함수 선언
void attackCharacterToMonster(Character *attacker, Monster *defender, int * enemy_cur_hp);
void attackMonsterToCharacter(Monster *attacker, Character *defender);
int escape(Character *player, Monster *enemy);
void useItem(Character *player);
void displayStats(Character *character);
void battle(Character *player, Monster *enemy);

#endif
