#include <iostream>
#include <list>
#include <thread>
using namespace std;

#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 30;

struct sSnakeSegment {
	int x;
	int y;
};

int main()
{
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	list <sSnakeSegment> snake = { {60,15}, {61,15}, {62,15}, {63,15} };
	int nFoodX = 30;
	int nFoodY = 15;
	int nScore = 0;
	int nSnakeDirection = 3;
	bool bDead = false;

	while (1) {

		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
			screen[i] = L' ';
		}

		for (int i = 0; i < nScreenWidth; i++) {
			screen[i] = L'=';
			screen[2 * nScreenWidth + i] = L'=';
		}
		wsprintf(&screen[nScreenWidth + 5], L"- - - SNAKE - - -              score: %d", nScore);

		for (auto s : snake) {
			screen[s.y * nScreenWidth + s.x] = bDead ? L'+' : L'o';
		}

		screen[snake.front().y * nScreenWidth + snake.front().x] = bDead ? L'X' : L'O';

		screen[nFoodY * nScreenWidth + nFoodX] = L'$';

		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
}
