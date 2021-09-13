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

//�ܼ�â �ִ� ũ��
#define Max_Buffer_XSize 100
#define Max_Buffer_YSize 60

//�� ũ��
#define Max_Map_XSize 17
#define Max_Map_YSize 40

//Ű �Է�
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define	SUBMIT 10

//�ڵ���, �÷��̾�, �� ����
#define WALL 1
#define ROAD 0
#define CAR 5
#define CAR_HIGHT 4
#define PLAYER 6

//�� ����
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

//windows ���� �Լ�
void gotoxy(int pos_x, int pos_y);						//Ŀ�� �̵�
void setCursor(int size, bool isNeed);					//Ŀ�� ����
COORD getxy();											//Ŀ�� ��ġ �޾ƿ���
void clear();											//ȭ�� ����
void textcolor(int colorNum);							//�ؽ�Ʈ �� ��ȯ
void consoleSetting();									//�ܼ� â ����
int inputCtrl();										//�÷��̾ �Է��� Ű �޾ƿ���

//���� - ��� x
//void CreatBuffer();										//���� ����
//void WriteBuffer(int x, int y, const char* string);		//���� ����
//void FlipBuffer();										//���� ��ȯ
//void ClearBuffer();										//����ߴ� ���� ������ ���� ����
//void DeleteBuffer();										//���� ���� 
//void BufferCtrl();										//���� �ٲٰ� ����

//���� ȭ�� ���� �Լ�
void title(int x, int y);								//Ÿ��Ʋ ���
int MenuCtrl(int x, int y);								//�޴� ��� �� ���� ó��

//���� ���� ���� �Լ�
void setGame();											//���� �� ����
void creatRandCar();									//�ڵ��� ���� ����
void gameMgr();											//��(��, �ڵ���) ��� �Լ� - ����ϸ鼭 �ڵ��� ��ĭ �ڷ� �̷��
void playerMove();										//�÷��̾� �̵� �Լ� - �̵�, �浹, ���ʽ� ���� �߰�
void gameOver();										//���� ���� - ���� ���ھ�, ���ο� ������� Ȯ��, ����ȭ������ ����
void gameStart();					//���� ����

//���� ��� ���� �Լ�
void howToPlay();					//���� ���

//Ŀ���� ���� 
void customScooter();				//�ž�ī ����