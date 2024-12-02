#ifndef MONSTER_H
#define MONSTER_H

//  monster 구조체
typedef struct {
    char name[50];
    int M_hp;
    int M_atk;
    int M_def;
} Monster;

// Getter 함수 선언
Monster* getMonster(int Monster_value);
void updateMonster(const char* stat, int value);

#endif // MONSTER_H
