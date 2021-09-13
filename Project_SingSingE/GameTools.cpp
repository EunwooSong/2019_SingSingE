#include "tool.h"

int map[50][25];
long long playerMaxScore = 0;		//�÷��̾��� �ְ�����
int score = 0;						//�÷��̾��� ����
int difficultLevel = 1;				//ȭ��� ������ ����
int ssBonus = 0;					//�ž� ���ʽ� ����
bool isCrash;						//�浹����
bool isAcceleration = false;		//���� ����

struct CarInfo						//�ڵ��� ��ġ, ��
{
	int posX, posY, color = RED;
};

CarInfo playerInfo;

//���۸� �ٲٰ� ����
//void BufferCtrl() {
//	FlipBuffer();
//	ClearBuffer();
//}

//���� ȭ�� =-----------------------------------------------------------------------------------------------------------
//Ÿ��Ʋ ��� �Լ�
void title(int x, int y) {
	gotoxy(x, y);
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("               #                                                                                    \n");
	printf("          #    ##   ##               #                                                              \n");
	printf("    ###   #     #   ## ## ######  ####                                                              \n");
	printf("    ##    ####  ##  ##      #  #### ##  ####  ##                                                    \n");
	printf("    #   ###     ##          # ##  # ##  #  ####                                                     \n");
	printf("    ##### ##   ###  ###           #  #                                                              \n");
	printf("     #         ##  #### ##                                                                          \n");
	printf("                   #####                                                                            \n");
	printf("                                                                                                    \n");
	printf("                                                                                                    \n");
	printf("                                                                                                    \n");
	printf("                                                                                                    \n");
	printf("                                #                 ##                 ##                   ###    ## \n");
	printf("                  ###    ##    ##    ###    ##    ##    ###    ##   ##                    ##     ## \n");
	printf("                 ###    ##     ##   ###    ##    ##    ###    ##    ##                   ###    ### \n");
	printf("                 ####  ##     ###  #####  ##     ##   ####  ###     ##     ####      #   ###    ##  \n");
	printf("                ##  #### #    ##   ##  #### #    ##   ##  ### ##    ##    ######   ###   ##     ##  \n");
	printf("                ##  #### #    ##   ##  #### #    ##   ##  ### ##    ##    ######   ###   ##     ##  \n");
	printf("               #    ##  ##   ##   #    ##  ##   ##  ##    ##  ##   ##   ##    #####     ##     ##   \n");
	printf("                     #    ##   ###     ##    ##    #      ##    ##  # #                  ##     #   \n");
	printf("                              # ##            #  # ##            # ## #                             \n");
	printf("                             ####               ####               ####                 ###    ###  \n");
	printf("                             ##                 ##                 ##                     #         \n");
	printf("----------------------------------------------------------------------------------------------------\n");

}

//����ȭ��(�κ�) ó�� �Լ�
int MenuCtrl(int x, int y) {
	//������ ���, �߽��� ������
	int pointY;
	x -= 8;
	y += 8;
	pointY = y;
	
	title(0, 0);
	gotoxy(x-5, y-4);
	printf("�ְ� ���� : %8d", playerMaxScore);
	gotoxy(x, y);
	printf("����   ����");
	gotoxy(x, y + 1);
	printf("����   ���");
	gotoxy(x, y + 2);
	printf("�ž�ī ����");
	gotoxy(x, y + 3);
	printf("��       ��");
	gotoxy(x - 8, y + 7);
	printf("�̵� : w,a,s,d / ���� : space");

	while (true) {
		//�÷��̾� �޴� ���� �޾ƿ���
		switch (inputCtrl()) {
		case UP:
			if ((y - 1) - pointY >= 0) {
				gotoxy(x-3,y);
				printf("   ");
				gotoxy(x-3, --y);
				printf(">  ");	//Ŀ�� ���
			}
			break;

		case DOWN:
			if ((y + 1) - pointY <= 3) {
				gotoxy(x - 3, y);
				printf("   ");
				gotoxy(x - 3, ++y);
				printf(">  ");	//Ŀ�� ���
			}
			break;

		case SUBMIT:
			return y - pointY; break;

		default:
			gotoxy(x-3, y);
			printf(">  ");
		}
	}
}

//���� ����------------------------------------------------------------------------------------------------------------------

//���� ���࿡ �ʿ��� �������� ����

//���� �غ� �Լ�
void setGame() {
	for (int i = 0; i < Max_Map_YSize; i++)
		for (int j = 0; j < Max_Map_XSize; j++) {
			if(j == 0 || j == Max_Map_XSize-1)
				map[i][j] = 1;
			else if (j % 4 == 0 && !(i % 5 == 0))
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}

	isCrash = false;						//ó���� �ѵ��Ǿ��ٴ� ���� �ʱ�ȭ
	playerInfo.posY = Max_Map_YSize - 5;	//�÷��̾� �⺻ ��ġ ����
	playerInfo.posX = 2;					//�÷��̾� �⺻ ��ġ ����
	score = 0;								//���ھ� �ʱ�ȭ
	difficultLevel = 1;						//���̵� �ʱ�ȭ
	ssBonus = 0;							//�ž����� �ʱ�ȭ
	isAcceleration = false;					//���� �ʱ�ȭ
}

//�ڵ��� ���� ����
void creatRandCar() {
	int carCount = rand() % 3 + 1;
	int carInfo = 0;
	
	for (int i = 0; i < carCount; i++) {
		carInfo = rand() % 4;
		switch(carInfo) {
		case 0: 
			if (map[0][2] == CAR) {
				i--;
				continue;
			}
			map[0][2] = CAR;
			break;

		case 1 : 
			if (map[0][6] == CAR) {
				i--;
				continue;
			}
			map[0][6] = CAR;
			break;

		case 2:
			if (map[0][10] == CAR) {
				i--;
				continue;
			}
			map[0][10] = CAR;
			break;

		case 3 :
			if (map[0][14] == CAR) {
				i--;
				continue;
			}
			map[0][14] = CAR;
			break;
		}
	}

}


//��(��, �ڵ���) ��� �Լ� - ��µǸ� �ڵ��� ��ĭ �ڷ� �̷��
void gameMgr() {

	CarInfo carInfo[30];
	int carCount = 0;

	gotoxy(0, 0);

	for (int i = 0; i < Max_Map_YSize; i++) {
		for (int j = 0; j < Max_Map_XSize; j++) {
			switch (map[i][j]) {
			case WALL:								//�� ���
				if (j == 0 || j == Max_Map_XSize - 1)
					textcolor(WHITE);
				else
					textcolor(YELLOW);
				printf("��"); break;

			case ROAD: printf("  "); break;			//�� ���

			case CAR:								//�ڵ��� ������ ������� ����
				printf("  ");
				carInfo[carCount].posX = j;
				carInfo[carCount].posY = i;
				carCount++;
				break;
			}
		}
		
		printf("  \n");
	 }
	
	//�ڵ��� ���� (��ĭ ������ ����)
	for (int i = 0; i < carCount; i++) {
		map[carInfo[i].posY][carInfo[i].posX] = ROAD;
		map[++carInfo[i].posY][carInfo[i].posX] = CAR;

		gotoxy((carInfo[i].posX-1) * 2, carInfo[i].posY-3);
		printf("  ��  ");
		for (int j = 0; j < 3; j++) {
			gotoxy((carInfo[i].posX - 1) * 2, carInfo[i].posY - (2 - j));
			printf("����");
		}
	}

	gotoxy(0, Max_Map_YSize);
	printf("                                                            ");
}


//�÷��̾� �̵� �Լ� - �̵�, �浹, ���ʽ� ���� �߰�
void playerMove() {
	
	//�÷��̾ �ִ� �ڸ� ����
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+1);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+2);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+3);
	printf("      ");

	//�Է� ����
	switch (inputCtrl()) {
	case LEFT :
		if (playerInfo.posX - 4 > 0)
		{
			playerInfo.posX -= 4;
		}break;

	case RIGHT :
		if (playerInfo.posX + 4 < Max_Map_XSize) {
			playerInfo.posX += 4;
		}break;

	case UP :
		isAcceleration = true;
		break;

	case DOWN:
		isAcceleration = false;
		break;
	}

	//�ش� ��ġ�� �ڵ��� ����
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY);
	printf("  ��  ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+1);
	printf(" ["); textcolor(playerInfo.color); printf("��"); textcolor(WHITE); printf("] ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+2);
	printf("  ��");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+3);
	printf("  ��  ");

	//�žź��ʽ�
	if (map[playerInfo.posY - 1][playerInfo.posX] == CAR) ssBonus++;

	//�浹 ����
	if (map[playerInfo.posY][playerInfo.posX] == CAR) isCrash = true;
	else if (map[playerInfo.posY+1][playerInfo.posX] == CAR) isCrash = true;
	else if (map[playerInfo.posY+2][playerInfo.posX] == CAR) isCrash = true;
	else if (map[playerInfo.posY+3][playerInfo.posX] == CAR) isCrash = true;
}

void gameOver() {
	gotoxy(0, 0);
	printf("IsCrash!");

	gotoxy(Max_Map_XSize * 2 + 14, 5);
	printf("GameOver!!");

	gotoxy(Max_Map_XSize * 2 + 8, 6);
	score = score + ssBonus + difficultLevel * 10;
	printf("YourScore : %8d", score);

	if (playerMaxScore < score) {
		playerMaxScore = score;		//�ִ��� ����
		gotoxy(Max_Map_XSize * 2 + 10, 9);
		printf("!*[NEW RECORD]*!");
		gotoxy(Max_Map_XSize * 2 + 9, 10);
		printf("Congratulations!!!");
	}

	gotoxy(Max_Map_XSize * 2 + 8, 12);
	printf("4�ʵ� ����ȭ������...");

	Sleep(4000);
	clear();
}

//���� ���� �Լ�
void gameStart() {
	int carSpawnTime = 1500;			//�ڵ��� ���� ������ �ð�
	int carMoveTime = 100;				//�ڵ��� �ӵ�
	int saveMoveTime = carMoveTime;		//�÷��̾� ������ ���� ����
	int difficultCut = 50;				//���̵� ���� ���� ��
	int time = 0;						//�帥 �ð�
	
	
	clear();			

	setGame();	//���� �ʱ�ȭ
	gameMgr();	//ȭ�� ���

	while (true) {
		gotoxy(Max_Map_XSize * 2 + 4, 19);
		printf("�� ��  ��  ��  : %6d ��", difficultLevel);
		gotoxy(Max_Map_XSize * 2 + 4, 20);
		printf("�� ��       �� : %6d ��", score);
		gotoxy(Max_Map_XSize * 2 + 4, 21);
		printf("�� �ž� ���ʽ� : %6d ��", ssBonus);
		gotoxy(Max_Map_XSize * 2 + 4, 22);
		printf("�� ���� ���� : %8d ��", score + ssBonus + difficultLevel * 10);
		playerMove();

		//�÷��̾ ���ӽ� movetime ��������
		if (isAcceleration) {
			gotoxy(Max_Map_XSize * 2+10, 24);
			printf("* ��      �� *");
			carMoveTime = saveMoveTime / 2;
		}
		else {
			gotoxy(Max_Map_XSize * 2+10, 24);
			printf("                ");
			carMoveTime = saveMoveTime;
		}

		//�ڵ��� ���� ����
		if (time % carSpawnTime == 0) {
			creatRandCar();
		}
		
		//�ڵ��� �ӵ�(�ڵ����� ��ĭ ������)
		if (time % carMoveTime == 0) {
			gameMgr();						//�ڵ��� �̵�, ȭ�� ���
			score++;
		}

		//���ھ �����ϸ� ���̵� ����
		if (score%difficultCut == 0) {
			difficultLevel++;
			score++;
			//�ִ� �����ӵ� ����
			(carSpawnTime > 200) ? carSpawnTime -= 55 : carSpawnTime = carSpawnTime;
			//�ڵ��� �ִ�ӵ� ����
			(saveMoveTime > 10) ? saveMoveTime -= 5 : saveMoveTime = saveMoveTime;
		}
		
		if (isCrash) break;

		Sleep(1);
		time++;
	}

	gameOver();
}





//�ž�ī Ŀ����=------------------------------------------------------------------------------------------------

//��� : �� ����..?(���α׷� ����۽� �� �ʱ�ȭ...   ��(������)��)

//gotoxy(((Max_Map_XSize / 2) / 2 + 3) * 2, Max_Map_YSize / 2 - 1);
//printf(" ["); textcolor(playerInfo.color); printf("��"); textcolor(WHITE); printf("] ");

void customScooter() {
	int cursorY;

	clear();
	
	//�׵θ� ����
	gotoxy((Max_Buffer_XSize /2)/2/2/2/2 + 1, (Max_Buffer_YSize /2)/2/2);

	for (int i = 0; i < (Max_Buffer_YSize / 2)/2 + (Max_Buffer_YSize / 2); i++) {
		for (int j = 0; j < 46; j++) {
			if (i == 0 || i == (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 1 )
				printf("��");
			else if (j == 0 || j == 45)
				printf("��");
			else
				printf("  ");
		}
		printf("\n    ");
	}

	//�ڵ��� ��ġ ���
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 - 2);
	printf("  ��  ");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 - 1);
	printf(" ["); textcolor(playerInfo.color); printf("��"); textcolor(WHITE); printf("] "); printf("      [�ž�ī �� ����]");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2);
	printf("  ��  ");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 + 1);
	printf("  ��  "); printf("        [space ����]");

	
	//���� ���
	for (int i = BLACK; i <= WHITE; i++) {
		gotoxy(Max_Buffer_XSize-45, (Max_Buffer_YSize / 2) / 2 + (i * 2));
		textcolor(i); printf("��"); textcolor(WHITE);

		switch (i)
		{
			case BLACK: printf("   Black"); break;
			case BLUE: printf("   Blue"); break;
			case GREEN: printf("   Green"); break;
			case CYAN: printf("   Cyan"); break;
			case RED: printf("   Red"); break;
			case MAGENTA: printf("   Magenta"); break;
			case BROWN: printf("   Brown"); break;
			case LIGHT_GRAY: printf("   Light Gray"); break;
			case DARK_GRAY: printf("   Dark Grady"); break;
			case LIGHT_BLUE: printf("   Light Blue"); break;
			case LIGHT_GREEN: printf("   Light Green"); break;
			case LIGHT_CYAN: printf("   Light Cyan"); break;
			case LIGHT_RED: printf("   Light Red"); break;
			case LIGHT_MAGENTA: printf("   Light Magenta"); break;
			case YELLOW: printf("   Yellow"); break;
			case WHITE: printf("   White"); break;
		}
	}

	//Ŀ�� ����
	cursorY = Max_Buffer_YSize/2/2;

	while (true) {
		switch (inputCtrl()) {
		case UP:
			if (((cursorY - 2) - Max_Buffer_YSize / 2 / 2) / 2 >= 0)
			{
				gotoxy(Max_Buffer_XSize - 50, cursorY);
				printf("   "); cursorY -= 2;
				gotoxy(Max_Buffer_XSize - 50, cursorY);
				printf(">  ");
			} break;

		case DOWN:
			if (((cursorY + 2) - Max_Buffer_YSize / 2 / 2) / 2 <= 15)
			{
				gotoxy(Max_Buffer_XSize - 50, cursorY);
				printf("   "); cursorY += 2;
				gotoxy(Max_Buffer_XSize - 50, cursorY);
				printf(">  ");
			} break;

		case SUBMIT:
			clear();
			return;

		default :
			gotoxy(Max_Buffer_XSize - 50, cursorY);
			printf(">  ");
		}

		playerInfo.color = (cursorY - Max_Buffer_YSize / 2 / 2) / 2;
		gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 - 1);
		printf(" ["); textcolor(playerInfo.color); printf("��"); textcolor(WHITE); printf("] ");
	}
}


//���� ��� =------------------------------------------------------------------------------
void howToPlay() {
	clear();
	int posX, posY;
	posX = (Max_Buffer_XSize / 2) / 2 / 2 / 2 / 2 + 1;
	posY = (Max_Buffer_YSize / 2) / 2 / 2;
	
	//�׵θ� ����
	gotoxy(posX, posY);
	for (int i = 0; i < (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2); i++) {
		for (int j = 0; j < 46; j++) {
			if (i == 0 || i == (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 1)
				printf("��");
			else if (j == 0 || j == 45)
				printf("��");
			else
				printf("  ");
		}
		printf("\n    ");
	}

	gotoxy(posX + 6, posY + 4);
	printf("[���� ����]");
	gotoxy(posX + 6, posY + 6);
	printf("�ž�ī�� Ÿ�� �ų��� �޷�����!!");
	gotoxy(posX + 6, posY + 8);
	printf("w : ����, a : �������� �̵�, s : ���� ����, d : ���������� �̵�");
	gotoxy(posX + 6, posY + 10);
	printf("���̵��� �����Կ� ���� �÷��̾��� �̵��ӵ��� �ڵ��� �����ӵ��� �������ϴ�.");

	gotoxy(posX + 6, posY + 16);
	printf("[���� ����]");
	gotoxy(posX + 6, posY + 18);
	printf("1. ȭ��� ���̴� �ڵ����� �� ĭ �Ʒ��� ������ ������ ������ 1 ���� �մϴ�.");
	gotoxy(posX + 6, posY + 20);
	printf("2. ������ 50�� ����� �Ǹ� ���̵��� �����մϴ�.");
	gotoxy(posX + 6, posY + 22);
	printf("3. ������ ���̵��� 10�� ���� �� ���� ������ �߰��մϴ�.");
	gotoxy(posX + 6, posY + 24);
	printf("4. �ڵ����� �ٷ� �տ� ���� �̵���Ű�� �߰� ������ �߻��մϴ�.");

	gotoxy(posX + 6, posY + 30);
	printf("[���� ����]");
	gotoxy(posX + 6, posY + 32);
	printf("�÷��̾ �ڵ����� �浹 �� ������ ����Ǹ�, ���� ȭ������ ���ư��ϴ�.");

	gotoxy(posX + 27, posY+(Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 4);
	system("pause");

	clear();
}
