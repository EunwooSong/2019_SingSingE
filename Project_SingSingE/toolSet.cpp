#include "tool.h";

//커서 이동
void gotoxy(int pos_x, int pos_y) {
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos = { pos_x, pos_y };

	SetConsoleCursorPosition(hOutput, Pos);
}

//커서 설정
void setCursor(int size, bool isNeed) {
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	if (size > 225) size = 225;

	cursor.bVisible = isNeed;
	cursor.dwSize = size;

	SetConsoleCursorInfo(hOutput, &cursor);
}

//커서 좌표 받아오기
COORD getxy() {
	COORD Pos;
	CONSOLE_SCREEN_BUFFER_INFO csBuffer;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hOutput, &csBuffer);
	Pos.X = csBuffer.dwCursorPosition.X;
	Pos.Y = csBuffer.dwCursorPosition.Y;

	return Pos;
}

//화면 지우기
void clear() {
	system("cls");
}

//텍스트 색 변경
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//콘솔 설정
void consoleSetting() {
	system("title SingSing~~!!!");
	system("mode con:cols=100 lines=60");
}

int inputCtrl() {
	if (_kbhit()) {
		switch (_getch()) {
			//대소문자 전부 입력 가능
		case 'W':
		case 'w': return UP;

		case 'A':
		case 'a': return LEFT;

		case 'S':
		case 's': return DOWN;

		case 'D':
		case 'd': return RIGHT;

		case ' ': return SUBMIT;
		}
	}
}
