#pragma once

#include "stdafx.h"
#include "protocol.h"

bool NetworkInit(HWND& hWnd, std::string SERVER_ADDR) {
	std::string buf_addr = SERVER_ADDR;

	// �Է¹��� ���ڿ����� ��� ����(.) ����
	SERVER_ADDR.erase(remove(SERVER_ADDR.begin(), SERVER_ADDR.end(), '.'), SERVER_ADDR.end());

	// Ŭ���̾�Ʈ �۾��� (���� ������ �ʿ��� ��� ����)
	if (SERVER_ADDR.length() == 0) return true;

	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	inet_pton(AF_INET, SERVER_ADDR.c_str(), &server_addr.sin_addr);

	if (connect(c_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
		MessageBox(hWnd, _T("��ȿ���� ���� IP �ּ��Դϴ�."), _T("�����ּ� ����!"), NULL);
		return false;
	}

	// Ŭ���̾�Ʈ ������ â �̸� ����
	SetWindowTextA(hWnd, (buf_addr + " �ּ��� ������ ���� ����!").c_str());

	// Network Todo


	return true;
}

void ProcessPacket(char* buf)
{
	switch (buf[0]) {
	case S2CSelectRole:

		break;
	case S2CChangeRole:

		break;
	case S2CMove:

		break;
	case S2CDoorOpen:

		break;
	case S2CExitGame:

		break;
	case S2CJewelryVisibility:

		break;
	case S2CLoading:
		break;		
	}
}

void SendPacket(void* buf)
{
	if (buf == nullptr)
		return;
	char* packet = nullptr;
	int size = 0;
	switch (reinterpret_cast<char*>(buf)[0]) {
	case C2SSelectRole:
		size = sizeof(C2SRolePacket);
		packet = new char[size];
		memcpy(packet, buf, size);
		break;
	case C2SChangeRole:

		break;
	case C2SMove:

		break;
	case C2SRetry:

		break;
	case C2SExitGame:

		break;		
	}

	if (packet != nullptr) {
		send(c_socket, packet, size, NULL);
		delete[] packet;
	}
}
