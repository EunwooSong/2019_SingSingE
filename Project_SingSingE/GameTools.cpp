#include "tool.h"

int map[50][25];
long long playerMaxScore = 0;		//플레이어의 최고점수
int score = 0;						//플레이어의 점수
int difficultLevel = 1;				//화면상에 보여줄 레벨
int ssBonus = 0;					//씽씽 보너스 점수
bool isCrash;						//충돌감지
bool isAcceleration = false;		//가속 감지

struct CarInfo						//자동차 위치, 색
{
	int posX, posY, color = RED;
};

CarInfo playerInfo;

//버퍼를 바꾸고 비우기
//void BufferCtrl() {
//	FlipBuffer();
//	ClearBuffer();
//}

//메인 화면 =-----------------------------------------------------------------------------------------------------------
//타이틀 출력 함수
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

//메인화면(로비) 처리 함수
int MenuCtrl(int x, int y) {
	//선택지 출력, 중심을 맞춰줌
	int pointY;
	x -= 8;
	y += 8;
	pointY = y;
	
	title(0, 0);
	gotoxy(x-5, y-4);
	printf("최고 점수 : %8d", playerMaxScore);
	gotoxy(x, y);
	printf("게임   시작");
	gotoxy(x, y + 1);
	printf("게임   방법");
	gotoxy(x, y + 2);
	printf("씽씽카 변경");
	gotoxy(x, y + 3);
	printf("종       료");
	gotoxy(x - 8, y + 7);
	printf("이동 : w,a,s,d / 선택 : space");

	while (true) {
		//플레이어 메뉴 선택 받아오기
		switch (inputCtrl()) {
		case UP:
			if ((y - 1) - pointY >= 0) {
				gotoxy(x-3,y);
				printf("   ");
				gotoxy(x-3, --y);
				printf(">  ");	//커서 출력
			}
			break;

		case DOWN:
			if ((y + 1) - pointY <= 3) {
				gotoxy(x - 3, y);
				printf("   ");
				gotoxy(x - 3, ++y);
				printf(">  ");	//커서 출력
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

//게임 시작------------------------------------------------------------------------------------------------------------------

//게임 진행에 필요한 전역변수 선언

//게임 준비 함수
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

	isCrash = false;						//처음에 총돌되었다는 정보 초기화
	playerInfo.posY = Max_Map_YSize - 5;	//플레이어 기본 위치 설정
	playerInfo.posX = 2;					//플레이어 기본 위치 설정
	score = 0;								//스코어 초기화
	difficultLevel = 1;						//난이도 초기화
	ssBonus = 0;							//씽씽점수 초기화
	isAcceleration = false;					//가속 초기화
}

//자동차 랜덤 생성
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


//맵(벽, 자동차) 출력 함수 - 출력되면 자동차 한칸 뒤로 미루기
void gameMgr() {

	CarInfo carInfo[30];
	int carCount = 0;

	gotoxy(0, 0);

	for (int i = 0; i < Max_Map_YSize; i++) {
		for (int j = 0; j < Max_Map_XSize; j++) {
			switch (map[i][j]) {
			case WALL:								//벽 출력
				if (j == 0 || j == Max_Map_XSize - 1)
					textcolor(WHITE);
				else
					textcolor(YELLOW);
				printf("■"); break;

			case ROAD: printf("  "); break;			//길 출력

			case CAR:								//자동차 생성은 맵출력후 진행
				printf("  ");
				carInfo[carCount].posX = j;
				carInfo[carCount].posY = i;
				carCount++;
				break;
			}
		}
		
		printf("  \n");
	 }
	
	//자동차 생성 (한칸 내리고 진행)
	for (int i = 0; i < carCount; i++) {
		map[carInfo[i].posY][carInfo[i].posX] = ROAD;
		map[++carInfo[i].posY][carInfo[i].posX] = CAR;

		gotoxy((carInfo[i].posX-1) * 2, carInfo[i].posY-3);
		printf("  ■  ");
		for (int j = 0; j < 3; j++) {
			gotoxy((carInfo[i].posX - 1) * 2, carInfo[i].posY - (2 - j));
			printf("■■■");
		}
	}

	gotoxy(0, Max_Map_YSize);
	printf("                                                            ");
}


//플레이어 이동 함수 - 이동, 충돌, 보너스 점수 추가
void playerMove() {
	
	//플레이어가 있던 자리 삭제
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+1);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+2);
	printf("      ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+3);
	printf("      ");

	//입력 설정
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

	//해당 위치에 자동차 생성
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY);
	printf("  ●  ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+1);
	printf(" ["); textcolor(playerInfo.color); printf("■"); textcolor(WHITE); printf("] ");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+2);
	printf("  ■");
	gotoxy((playerInfo.posX - 1) * 2, playerInfo.posY+3);
	printf("  ●  ");

	//씽씽보너스
	if (map[playerInfo.posY - 1][playerInfo.posX] == CAR) ssBonus++;

	//충돌 감지
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
		playerMaxScore = score;		//최대기록 저장
		gotoxy(Max_Map_XSize * 2 + 10, 9);
		printf("!*[NEW RECORD]*!");
		gotoxy(Max_Map_XSize * 2 + 9, 10);
		printf("Congratulations!!!");
	}

	gotoxy(Max_Map_XSize * 2 + 8, 12);
	printf("4초뒤 메인화면으로...");

	Sleep(4000);
	clear();
}

//게임 시작 함수
void gameStart() {
	int carSpawnTime = 1500;			//자동차 생성 딜레이 시간
	int carMoveTime = 100;				//자동차 속도
	int saveMoveTime = carMoveTime;		//플레이어 가속을 위한 변수
	int difficultCut = 50;				//난이도 증가 점수 컷
	int time = 0;						//흐른 시간
	
	
	clear();			

	setGame();	//게임 초기화
	gameMgr();	//화면 출력

	while (true) {
		gotoxy(Max_Map_XSize * 2 + 4, 19);
		printf("■ 난  이  도  : %6d ■", difficultLevel);
		gotoxy(Max_Map_XSize * 2 + 4, 20);
		printf("■ 점       수 : %6d ■", score);
		gotoxy(Max_Map_XSize * 2 + 4, 21);
		printf("■ 씽씽 보너스 : %6d ■", ssBonus);
		gotoxy(Max_Map_XSize * 2 + 4, 22);
		printf("■ 최종 점수 : %8d ■", score + ssBonus + difficultLevel * 10);
		playerMove();

		//플레이어가 가속시 movetime 절반으로
		if (isAcceleration) {
			gotoxy(Max_Map_XSize * 2+10, 24);
			printf("* 가      속 *");
			carMoveTime = saveMoveTime / 2;
		}
		else {
			gotoxy(Max_Map_XSize * 2+10, 24);
			printf("                ");
			carMoveTime = saveMoveTime;
		}

		//자동차 랜덤 생성
		if (time % carSpawnTime == 0) {
			creatRandCar();
		}
		
		//자동차 속도(자동차가 한칸 내려옴)
		if (time % carMoveTime == 0) {
			gameMgr();						//자동차 이동, 화면 출력
			score++;
		}

		//스코어가 증가하면 난이도 증가
		if (score%difficultCut == 0) {
			difficultLevel++;
			score++;
			//최대 스폰속도 설정
			(carSpawnTime > 200) ? carSpawnTime -= 55 : carSpawnTime = carSpawnTime;
			//자동차 최대속도 설정
			(saveMoveTime > 10) ? saveMoveTime -= 5 : saveMoveTime = saveMoveTime;
		}
		
		if (isCrash) break;

		Sleep(1);
		time++;
	}

	gameOver();
}





//씽씽카 커스텀=------------------------------------------------------------------------------------------------

//기능 : 색 변경..?(프로그램 재시작시 색 초기화...   ㄴ(ㅇㅁㅇ)ㄱ)

//gotoxy(((Max_Map_XSize / 2) / 2 + 3) * 2, Max_Map_YSize / 2 - 1);
//printf(" ["); textcolor(playerInfo.color); printf("■"); textcolor(WHITE); printf("] ");

void customScooter() {
	int cursorY;

	clear();
	
	//테두리 생성
	gotoxy((Max_Buffer_XSize /2)/2/2/2/2 + 1, (Max_Buffer_YSize /2)/2/2);

	for (int i = 0; i < (Max_Buffer_YSize / 2)/2 + (Max_Buffer_YSize / 2); i++) {
		for (int j = 0; j < 46; j++) {
			if (i == 0 || i == (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 1 )
				printf("■");
			else if (j == 0 || j == 45)
				printf("■");
			else
				printf("  ");
		}
		printf("\n    ");
	}

	//자동차 위치 출력
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 - 2);
	printf("  ●  ");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 - 1);
	printf(" ["); textcolor(playerInfo.color); printf("■"); textcolor(WHITE); printf("] "); printf("      [씽씽카 색 변경]");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2);
	printf("  ■  ");
	gotoxy(Max_Buffer_XSize / 2 / 2 / 2 / 2 + 10, Max_Buffer_YSize / 2 + 1);
	printf("  ●  "); printf("        [space 선택]");

	
	//색상 출력
	for (int i = BLACK; i <= WHITE; i++) {
		gotoxy(Max_Buffer_XSize-45, (Max_Buffer_YSize / 2) / 2 + (i * 2));
		textcolor(i); printf("■"); textcolor(WHITE);

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

	//커서 조정
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
		printf(" ["); textcolor(playerInfo.color); printf("■"); textcolor(WHITE); printf("] ");
	}
}


//게임 방법 =------------------------------------------------------------------------------
void howToPlay() {
	clear();
	int posX, posY;
	posX = (Max_Buffer_XSize / 2) / 2 / 2 / 2 / 2 + 1;
	posY = (Max_Buffer_YSize / 2) / 2 / 2;
	
	//테두리 생성
	gotoxy(posX, posY);
	for (int i = 0; i < (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2); i++) {
		for (int j = 0; j < 46; j++) {
			if (i == 0 || i == (Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 1)
				printf("■");
			else if (j == 0 || j == 45)
				printf("■");
			else
				printf("  ");
		}
		printf("\n    ");
	}

	gotoxy(posX + 6, posY + 4);
	printf("[게임 설명]");
	gotoxy(posX + 6, posY + 6);
	printf("씽씽카를 타고 신나게 달려보자!!");
	gotoxy(posX + 6, posY + 8);
	printf("w : 가속, a : 왼쪽으로 이동, s : 가속 해제, d : 오른쪽으로 이동");
	gotoxy(posX + 6, posY + 10);
	printf("난이도는 증가함에 따라 플레이어의 이동속도와 자동차 생성속도가 빨라집니다.");

	gotoxy(posX + 6, posY + 16);
	printf("[점수 설명]");
	gotoxy(posX + 6, posY + 18);
	printf("1. 화면상에 보이는 자동차가 한 칸 아래로 내려올 때마다 점수가 1 증가 합니다.");
	gotoxy(posX + 6, posY + 20);
	printf("2. 점수가 50의 배수가 되면 난이도가 증가합니다.");
	gotoxy(posX + 6, posY + 22);
	printf("3. 증가한 난이도에 10을 곱한 후 최종 점수에 추가합니다.");
	gotoxy(posX + 6, posY + 24);
	printf("4. 자동차를 바로 앞에 놓고 이동시키면 추가 점수가 발생합니다.");

	gotoxy(posX + 6, posY + 30);
	printf("[게임 오버]");
	gotoxy(posX + 6, posY + 32);
	printf("플레이어가 자동차와 충돌 시 게임이 종료되며, 메인 화면으로 돌아갑니다.");

	gotoxy(posX + 27, posY+(Max_Buffer_YSize / 2) / 2 + (Max_Buffer_YSize / 2) - 4);
	system("pause");

	clear();
}
