#include <Windows.h>
using namespace std;

void GotoXY(int x, int y)
{   // COORD ����ü ������ ���� �̵��� ��ġ ����
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}