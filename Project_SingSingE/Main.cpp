#include "tool.h"

//게임 초기화
void Init() {
	srand(time(NULL));
	consoleSetting();
	setCursor(1, false);
	//CreatBuffer();
}

//플레이어가 선택한 값 반환
int MainScene() {
	return MenuCtrl(50, 25);
}

//게임 종료시 버퍼 종료
void Stop() {
	//DeleteBuffer();
}

int main() {
	Init();

	while (true) {
		switch (MainScene()) {
		case 0: gameStart(); break;				//게임 시작
		case 1: howToPlay(); break;				//게임 방법
		case 2: customScooter(); break;			//씽씽카 색 변경
		case 3: return 0;//Stop(); return 0;		//종료
		}
	}
}