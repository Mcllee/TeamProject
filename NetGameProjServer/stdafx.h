#pragma once
#include<iostream>
#include<WS2tcpip.h>
#include<array>
#include<mutex>
#include<chrono>
#include"protocol.h"

#pragma comment(lib, "ws2_32")

using namespace std;
using namespace chrono;
#define MAX_BUF_SIZE 256

#define STAGE_TITLE			0
#define STAGE_LOADING		1
#define STAGE_ROLE			2
#define STAGE_01			3
#define STAGE_02			4
#define STAGE_03			5

struct threadInfo {
	HANDLE threadHandle = NULL;
	SOCKET clientSocket;
	char recvBuf[MAX_BUF_SIZE] = { 0 };
	int currentSize;
	int prevSize = 0;
	char clientId = -1;
	short x, y, ground = 730;	// ��ǥ�� ĳ���� �߽�
	short hei = 100, wid = 60;	// ĳ���� ũ��

	int direction;
	float wid_v{};
	float wid_a{};

	float g = 4.f;
	float v = 0.f;

	HANDLE jumpEventHandle = NULL;
	high_resolution_clock::time_point jumpStartTime;
	high_resolution_clock::time_point jumpCurrentTime;
	bool isJump = false;
};

void Display_Err(int Errcode);
void ConstructPacket(threadInfo& clientInfo, int ioSize); // ��Ŷ ������
void ProcessPacket(threadInfo& clientInfo, char* packetStart); // ��Ŷ ������ ��, ��� �ؼ� �� �ൿ
int GetPacketSize(char packetType);

void ChangeRole(); // mutex �ʿ� ������? => change�� ���� ���� ���ٰ� ������
void SelectRole(); // mutex �ʿ� => �� Ŭ���̾�Ʈ�� ���ÿ� ���� �ɸ��� ������ �ع����� �ȵ�
//void MovePacket(); // ������ �� ����, ����
void CheckJewelryEat();// ��� ���� Ȯ��
void CheckOpenDoor(); // �� ������ ���� Ȯ��


extern array<threadInfo, 3> threadHandles;
extern array<char, 3> playerRole;
extern mutex selectMutex;
extern array<char, 3> selectPlayerRole;
extern HANDLE multiEvenTthreadHadle[3];

extern int stageIndex;

//HANDLE loadFlag; =>����Ʈ���Ǳ�