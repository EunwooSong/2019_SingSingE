#include "tool.h"

//���� �ʱ�ȭ
void Init() {
	srand(time(NULL));
	consoleSetting();
	setCursor(1, false);
	//CreatBuffer();
}

//�÷��̾ ������ �� ��ȯ
int MainScene() {
	return MenuCtrl(50, 25);
}

//���� ����� ���� ����
void Stop() {
	//DeleteBuffer();
}

int main() {
	Init();

	while (true) {
		switch (MainScene()) {
		case 0: gameStart(); break;				//���� ����
		case 1: howToPlay(); break;				//���� ���
		case 2: customScooter(); break;			//�ž�ī �� ����
		case 3: return 0;//Stop(); return 0;		//����
		}
	}
}