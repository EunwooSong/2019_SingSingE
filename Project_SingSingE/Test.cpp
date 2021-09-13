#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void setConsole() {
	system("title test한글");
}

void main() {
	setConsole();
	printf("test 한글 ■");
	getchar();
}