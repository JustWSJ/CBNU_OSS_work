#include <windows.h>
#include "key_input.h"

// 특정 키가 눌렸는지 확인하는 함수
int isKeyPressed(int key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}
