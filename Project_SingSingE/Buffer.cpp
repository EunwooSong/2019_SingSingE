//#include "tool.h";
//
//HANDLE hBuffer[2];
//int nScreenIndex = 0;
//
////버퍼 생성
//void CreatBuffer() {
//	COORD size = { Max_Buffer_XSize, Max_Buffer_YSize };
//	CONSOLE_CURSOR_INFO ccinfo;
//	SMALL_RECT rect;
//	rect.Bottom = 0;
//	rect.Left = 0;
//	rect.Right = Max_Buffer_XSize;
//	rect.Top = Max_Buffer_YSize;
//
//	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
//	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
//
//	SetConsoleScreenBufferSize(hBuffer[1], size);
//	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);
//
//	SetConsoleCursorInfo(hBuffer[0], &ccinfo);
//	SetConsoleCursorInfo(hBuffer[1], &ccinfo);
//}
//
////버퍼 쓰기
//void WriteBuffer(int x, int y, const char* string)
//{
//	DWORD dw;
//	COORD pos = { x, y };
//
//	WriteConsoleOutputCharacter(hBuffer[nScreenIndex], string, lstrlen(string), pos, &dw);
//}
//
////버퍼 전환
//void FlipBuffer() {
//	//Sleep(33);
//	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);
//	nScreenIndex = !nScreenIndex;
//}
//
////버퍼 내용 지우기
//void ClearBuffer() {
//	COORD Coor = { 0, 0 };
//	DWORD dw;
//	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', Max_Buffer_XSize*Max_Buffer_YSize, Coor, &dw);
//}
//
////버퍼 해제
//void DeleteBuffer() {
//	CloseHandle(hBuffer[0]);
//	CloseHandle(hBuffer[1]);
//}  