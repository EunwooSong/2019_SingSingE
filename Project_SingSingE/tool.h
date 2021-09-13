#pragma once
#pragma once
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <stddef.h>
#include <conio.h>

//콘솔창 최대 크기
#define Max_Buffer_XSize 100
#define Max_Buffer_YSize 60

//맵 크기
#define Max_Map_XSize 17
#define Max_Map_YSize 40

//키 입력
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define	SUBMIT 10

//자동차, 플레이어, 벽 설정
#define WALL 1
#define ROAD 0
#define CAR 5
#define CAR_HIGHT 4
#define PLAYER 6

//색 설정
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

//windows 관련 함수
void gotoxy(int pos_x, int pos_y);						//커서 이동
void setCursor(int size, bool isNeed);					//커서 설정
COORD getxy();											//커서 위치 받아오기
void clear();											//화면 비우기
void textcolor(int colorNum);							//텍스트 색 변환
void consoleSetting();									//콘솔 창 설정
int inputCtrl();										//플레이어가 입력한 키 받아오기

//버퍼 - 사용 x
//void CreatBuffer();										//버퍼 생성
//void WriteBuffer(int x, int y, const char* string);		//버퍼 쓰기
//void FlipBuffer();										//버퍼 변환
//void ClearBuffer();										//사용했던 버퍼 재사용을 위해 비우기
//void DeleteBuffer();										//버퍼 삭제 
//void BufferCtrl();										//버퍼 바꾸고 비우기

//메인 화면 관련 함수
void title(int x, int y);								//타이틀 출력
int MenuCtrl(int x, int y);								//메뉴 출력 및 선택 처리

//게임 시작 관련 함수
void setGame();											//게임 맵 생성
void creatRandCar();									//자동차 랜덤 생성
void gameMgr();											//맵(벽, 자동차) 출력 함수 - 출력하면서 자동차 한칸 뒤로 미루기
void playerMove();										//플레이어 이동 함수 - 이동, 충돌, 보너스 점수 추가
void gameOver();										//게임 오버 - 최종 스코어, 새로운 기록인지 확인, 메인화면으로 복귀
void gameStart();					//게임 시작

//게임 방법 관련 함수
void howToPlay();					//게임 방법

//커스텀 관련 
void customScooter();				//씽씽카 변경