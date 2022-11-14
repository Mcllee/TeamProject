#include<iostream>
#include<WS2tcpip.h>
#include<array>
#include<mutex>
#include"protocol.h"

#pragma comment(lib, "ws2_32")

using namespace std;

#define MAX_BUF_SIZE 256

#define STAGE_TITLE			0
#define STAGE_LOADING		1
#define STAGE_LOBBY			2
#define STAGE_01			3
#define STAGE_02			4
#define STAGE_03			5

void Display_Err(int Errcode);
void ConstructPacket(char* recvPacket); // ��Ŷ ������
void ProcessPacket(char* packetStart); // ��Ŷ ������ ��, ��� �ؼ� �� �ൿ
void ChangeRole(); // mutex �ʿ� ������? => change�� ���� ���� ���ٰ� ������
void SelectRole(); // mutex �ʿ� => �� Ŭ���̾�Ʈ�� ���ÿ� ���� �ɸ��� ������ �ع����� �ȵ�
void MovePacket(); // ������ �� ����, ����
void CheckJewelryEat();// ��� ���� Ȯ��
void CheckOpenDoor(); // �� ������ ���� Ȯ��




DWORD WINAPI ClientWorkThread(LPVOID arg);

struct threadInfo {
	HANDLE threadHandle = NULL;
	SOCKET clientSocket;
	char recvBuf[MAX_BUF_SIZE] = { 0 };
	int currentSize;
	int prev_size = 0;
};

array<threadInfo, 3> threadHandles;
HANDLE multiEvenTthreadHadle[3];

//HANDLE loadFlag; =>����Ʈ���Ǳ�

//map<socket, Role> �ϴ°� ������?

int main(int argv, char** argc)
{
	wcout.imbue(std::locale("korean"));


	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		Display_Err(WSAGetLastError());
		return 1;
	}

	//loadFlag= CreateEvent(NULL, FALSE, FALSE, NULL);

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET) {
		Display_Err(WSAGetLastError());
		return 1;
	}

	SOCKADDR_IN server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
		Display_Err(WSAGetLastError());
		return 1;
	}

	if (listen(listenSocket, 1) == SOCKET_ERROR) { // ������ Ŭ���̾�Ʈ�� 1��
		Display_Err(WSAGetLastError());
		return 1;
	}

	for (int i = 0; i < 3; i++)
	{
		SOCKADDR_IN cl_addr;
		int addr_size = sizeof(cl_addr);
		threadHandles[i].clientSocket = accept(listenSocket, reinterpret_cast<sockaddr*>(&cl_addr), &addr_size);
		if (threadHandles[i].clientSocket == INVALID_SOCKET) {
			Display_Err(WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}

		cout << "Accept Client[" << i <<"]" << endl;

		S2CPlayerPacket loadPacket;
		loadPacket.type = S2CLoading;
		loadPacket.id = i;

		threadHandles[i].threadHandle = CreateThread(NULL, 0, ClientWorkThread, reinterpret_cast<LPVOID>(i), 0, NULL);
		multiEvenTthreadHadle[i] = threadHandles[i].threadHandle;
		send(threadHandles[i].clientSocket, (char*)&loadPacket, sizeof(S2CPlayerPacket), 0);//loading ��Ŷ�� �α��� ��Ŷ���� ����

		loadPacket.type = S2CAddPlayer;
		for (int j = 0; j < 3; j++) {
			if (i != j) {
				if (threadHandles[j].threadHandle != NULL) {
					send(threadHandles[j].clientSocket, (char*)&loadPacket, sizeof(S2CPlayerPacket), 0);//�ٸ� Player ���� ��Ŷ���� ���� // j������ i�� ������

					S2CPlayerPacket addPlayerPacket;
					loadPacket.type = S2CAddPlayer;
					loadPacket.id = j;
					send(threadHandles[i].clientSocket, (char*)&loadPacket, sizeof(S2CPlayerPacket), 0);//�ٸ� Player ���� ��Ŷ���� ���� // i���� j�� ������
				}
			}
		}

		if (i == 2) {
			S2CChangeStagePacket changePacket;
			changePacket.stageNum = STAGE_LOBBY;
			changePacket.type = S2CChangeStage;

			for (int x = 0; x < 3; x++)
				send(threadHandles[x].clientSocket, (char*)&changePacket, sizeof(S2CChangeStage), 0);
		}
	}

	while (WSA_WAIT_EVENT_0 + 2 != WSAWaitForMultipleEvents(3, multiEvenTthreadHadle, TRUE, WSA_INFINITE, FALSE)) {}
	for (int j = 0; j < 3; j++) {
		CloseHandle(threadHandles[j].threadHandle);
	}

	closesocket(listenSocket);
	WSACleanup();

}

void Display_Err(int Errcode)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, Errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	wcout << "ErrorCode: " << Errcode << " - " << (WCHAR*)lpMsgBuf << endl;
	LocalFree(lpMsgBuf);
}

void ConstructPacket(char* recvPacket)
{

}

DWORD WINAPI ClientWorkThread(LPVOID arg)
{
	//WaitForSingleObject(loadFlag, INFINITE);

	int myIndex = reinterpret_cast<int>(arg);
	while (true) {
		int recvRetVal = recv(threadHandles[myIndex].clientSocket, threadHandles[myIndex].recvBuf + threadHandles[myIndex].prev_size, MAX_BUF_SIZE - threadHandles[myIndex].prev_size, 0);
		if (!recvRetVal) {
			ConstructPacket(threadHandles[myIndex].recvBuf + threadHandles[myIndex].prev_size);
		}
	}
	return 0;
}

void ProcessPacket(char* packetStart) // ���� �����ʴ� �Լ� - recv()�ϸ鼭 �ҷ���
{

	//changePacket() => send S2CChangeRolePacket
	//selectPacket() => mutex Role container and send S2CSelectPacket
	//movePacket(); => ���⼭ �浹 üũ, ���� üũ => ���⼭ ������ �� �Ծ��ٸ� �� Ŭ���̾�Ʈ���� �� ���� ��Ŷ ����, �� ����� ��Ŷ�� �����ؾߵǳ�
}
