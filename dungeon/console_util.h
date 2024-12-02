#ifndef CONSOLE_UTIL_H
#define CONSOLE_UTIL_H
#include <stdlib.h>
#include <windows.h>
#define pause system("pause > nul")

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
void clearScreen();

#endif // CONSOLE_UTIL_H