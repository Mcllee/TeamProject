#include<iostream>
#include<WS2tcpip.h>
#include<array>
#include<mutex>
#include"protocol.h"

#pragma comment(lib, "ws2_32")

using namespace std;

void Display_Err(int Errcode);
void ConstructPacket(char* recvPacket); // ��Ŷ ������
void ProcessPacket(char* packetStart); // ��Ŷ ������ ��, ���� �ؼ� �� �ൿ
void ChangeRole(); // mutex �ʿ� ������? => change�� ���� ���� ���ٰ� ������
void SelectRole(); // mutex �ʿ� => �� Ŭ���̾�Ʈ�� ���ÿ� ���� �ɸ��� ������ �ع����� �ȵ�
void MovePacket(); // ������ �� ����, ����
void CheckJewelryEat();// ��� ���� Ȯ��
void CheckOpenDoor(); // �� ������ ���� Ȯ��


DWORD WINAPI ClientWorkThread(LPVOID arg);


struct threadInfo {
	HANDLE h = NULL;
	SOCKET clientSocket;
};
array<threadInfo, 3> threadHandles;
//map<socket, Role> �ϴ°� ������?

int main(int argv, char** argc)
{
	wcout.imbue(std::locale("korean"));

	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		Display_Err(WSAGetLastError());
		return 1;
	}

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
		SOCKET clientSocket = accept(listenSocket, reinterpret_cast<sockaddr*>(&cl_addr), &addr_size);
		if (clientSocket == INVALID_SOCKET) {
			Display_Err(WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}
		threadHandles[i].h = CreateThread(NULL, 0, ClientWorkThread, reinterpret_cast<LPVOID>(clientSocket), 0, NULL);//���ڰ� clientSocket�� �ƴ� �� ����
		threadHandles[i].clientSocket = clientSocket;
		if (i == 0) {
			//sendpakcet(loading);
		}
		if (i == 1) {
			//sendpakcet(change Stage - Select); // �� Ŭ���̾�Ʈ ��ο���
		}
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

DWORD WINAPI ClientWorkThread(LPVOID arg)
{
	SOCKET socket = *reinterpret_cast<SOCKET*>(arg);
	while (true) {
		//recv();
	}
	return 0;
}

void ProcessPacket(char* packetStart) // ���� �����ʴ� �Լ� - recv()�ϸ鼭 �ҷ���
{
	//changePacket() => send S2CChangeRolePacket
	//selectPacket() => mutex Role container and send S2CSelectPacket
	//movePacket(); => ���⼭ �浹 üũ, ���� üũ => ���⼭ ������ �� �Ծ��ٸ� �� Ŭ���̾�Ʈ���� �� ���� ��Ŷ ����, �� ����� ��Ŷ�� �����ؾߵǳ�
}