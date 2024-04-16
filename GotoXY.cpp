#include <Windows.h>
using namespace std;

void GotoXY(int x, int y)
{   // COORD 구조체 변수를 통해 이동할 위치 설정
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}