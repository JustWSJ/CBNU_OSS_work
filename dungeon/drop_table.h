#ifndef DROP_TABLE_H
#define DROP_TABLE_H

#include "items.h"

// 드롭 테이블 항목 구조체
typedef struct {
    int monsterID;      // 몬스터 ID
    int dropRate;       // 드롭 확률 (0~100)
    Item dropItem;      // 드롭 아이템
} DropTable;

// 드롭 테이블 반환 함수
const DropTable* getDropTable(int monsterID, int* count);

#endif