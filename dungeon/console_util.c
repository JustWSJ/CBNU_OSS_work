#include <windows.h>
#include "console_util.h"

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    DWORD charsWritten;
    DWORD consoleSize;
    COORD topLeft = { 0, 0 };

    // 콘솔 크기 가져오기
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    consoleSize = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

    // 화면을 공백으로 채우기
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &charsWritten);
    FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, consoleSize, topLeft, &charsWritten);

    // 커서를 초기 위치로 이동
    SetConsoleCursorPosition(hConsole, topLeft);
}