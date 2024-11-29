#ifndef KEY_INPUT_H
#define KEY_INPUT_H

// 키 상수 정의
#define KEY_UP    VK_UP
#define KEY_DOWN  VK_DOWN
#define KEY_LEFT  VK_LEFT
#define KEY_RIGHT VK_RIGHT
#define KEY_SPACE VK_SPACE
#define KEY_ESCAPE VK_ESCAPE
#define KEY_ENTER VK_RETURN

// 키 입력 확인 함수 선언
int isKeyPressed(int key);
void wait();

#endif
