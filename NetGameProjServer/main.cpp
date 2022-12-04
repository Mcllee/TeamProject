#pragma once
#include "stdafx.h"
#include "Stage.h"
#include "Timer.h"
#include<time.h>


array<ThreadInfo, 3> threadHandles;
array<char, 3> playerRole = { 'f', 'f', 'f' };
mutex selectMutex;
array<char, 3> selectPlayerRole = { 'n', 'n', 'n' };
HANDLE multiEvenTthreadHadle[3];
HANDLE jewelyEatHandle;
int stageIndex = -1;

Stage StageMgr;

// ��ö ���� ���ڵ�
int currentJewelyNum = 0; // ���� ���� �̺�Ʈ �ڵ� ��ȣ
bool isVisibleDoor = false; // �� ������ => stage �ȿ� ������ ��� ����
mutex jewelyMutex;

DWORD WINAPI ClientWorkThread(LPVOID arg);
DWORD WINAPI ServerWorkThread(LPVOID arg);

void TimeoutStage();
void StageTimerStart();


Timer _timer;

double timeoutSeconds = 60 * 5;

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

	if (::bind(listenSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
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
		u_long blockingMode = 1;
		ioctlsocket(threadHandles[i].clientSocket, FIONBIO, &blockingMode);
		if (threadHandles[i].clientSocket == INVALID_SOCKET) {
			Display_Err(WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}

		cout << "Accept Client[" << i << "]" << endl;
		threadHandles[i].jumpEventHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
		ResetEvent(threadHandles[i].jumpEventHandle);

		S2CPlayerPacket loadPacket;
		loadPacket.type = S2CLoading;
		loadPacket.id = i;
		threadHandles[i].clientId = i;
		threadHandles[i].threadHandle = CreateThread(NULL, 0, ClientWorkThread, reinterpret_cast<LPVOID>(i), 0, NULL);
		multiEvenTthreadHadle[i] = threadHandles[i].threadHandle;
		send(threadHandles[i].clientSocket, (char*)&loadPacket, sizeof(S2CPlayerPacket), 0);//loading ��Ŷ�� �α��� ��Ŷ���� ����

		loadPacket.type = S2CAddPlayer;
		for (int j = 0; j < 3; j++) {
			if (i != j) {
				if (threadHandles[j].threadHandle != NULL) {
					send(threadHandles[j].clientSocket, (char*)&loadPacket, sizeof(S2CPlayerPacket), 0);//�ٸ� Player ���� ��Ŷ���� ���� // j������ i�� ������

					S2CPlayerPacket addPlayerPacket;
					addPlayerPacket.type = S2CAddPlayer;
					addPlayerPacket.id = j;
					send(threadHandles[i].clientSocket, (char*)&addPlayerPacket, sizeof(S2CPlayerPacket), 0);//�ٸ� Player ���� ��Ŷ���� ���� // i���� j�� ������
				}
			}
		}

		if (i == 2) {
			S2CChangeStagePacket changePacket;
			changePacket.stageNum = STAGE_ROLE;
			changePacket.type = S2CChangeStage;

			for (int x = 0; x < 3; x++) {
				send(threadHandles[x].clientSocket, (char*)&changePacket, sizeof(S2CChangeStagePacket), 0);
			}
			stageIndex = STAGE_ROLE;
		}
	}
	cout << "All Clients Accpet" << endl;

	cout << "Start server Main Thread" << endl;
	jewelyEatHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(jewelyEatHandle);
	HANDLE serverThread = CreateThread(NULL, 0, ServerWorkThread, reinterpret_cast<LPVOID>(1), 0, NULL);

	while (WSA_WAIT_EVENT_0 + 2 != WSAWaitForMultipleEvents(3, multiEvenTthreadHadle, TRUE, WSA_INFINITE, FALSE)) {}
	for (int j = 0; j < 3; j++) {
		CloseHandle(threadHandles[j].threadHandle);
	}
	CloseHandle(serverThread);


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

void ConstructPacket(ThreadInfo& clientInfo, int ioSize)
{
	int restSize = ioSize + clientInfo.prevSize;
	int needSize = 0;
	char* buf = clientInfo.recvBuf;
	while (restSize != 0) {
		needSize = GetPacketSize(reinterpret_cast<char*>(buf)[0]);
		if (restSize < needSize) {
			clientInfo.prevSize = restSize;
			return;
		}
		else {
			ProcessPacket(clientInfo, reinterpret_cast<char*>(buf));
			memcpy(buf, reinterpret_cast<char*>(buf) + needSize, restSize - needSize);
			restSize -= needSize;
		}
	}
}

DWORD WINAPI ClientWorkThread(LPVOID arg)
{
	int myIndex = reinterpret_cast<int>(arg);
	while (true) {
		int recvRetVal = recv(threadHandles[myIndex].clientSocket, threadHandles[myIndex].recvBuf + threadHandles[myIndex].prevSize, MAX_BUF_SIZE - threadHandles[myIndex].prevSize, 0);
		if (recvRetVal > 0) {
			ConstructPacket(threadHandles[myIndex], recvRetVal);
		}
		// ��ö ����: �ݶ��̵� ����, ��
		//���⿡ ���� üũ? => ���ϰ� ������? => ������ �����ѵ� => ������ ���� �Դ°� ���⿡ �ӽô�.		

		//// �ϴ� �̰ɷ� ����
		if (StageMgr.currentVisibleJewely.OBJECT_Collide(threadHandles[myIndex])) {
			S2CPlayerPacket jewelyPacket;
			jewelyPacket.id = -1;
			jewelyPacket.type = S2CEatJewely;
			DWORD retVal = WaitForSingleObject(jewelyEatHandle, 0);
			if (retVal != WAIT_OBJECT_0) {
				threadHandles[myIndex].score++;
				SetEvent(jewelyEatHandle);
				jewelyPacket.id = myIndex;
			}
			//mutex ���� �� �� �־
			if (jewelyPacket.id != -1)
				for (int j = 0; j < 3; j++)
					send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&jewelyPacket), sizeof(S2CPlayerPacket), 0);

		}

		//
		if (isVisibleDoor) {
			if (StageMgr.door.OBJECT_Collide(threadHandles[myIndex])) {
				S2CPlayerPacket intoDoorPacket;
				intoDoorPacket.id = myIndex;
				intoDoorPacket.type = S2CIntoDoor;
				for (int j = 0; j < 3; j++)
					send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&intoDoorPacket), sizeof(S2CPlayerPacket), 0);// ������ ���� ��� => �̰� ���� Ŭ��� ������ ���� �ִϸ��̼�
			}
		}
	}
	return 0;
}

DWORD WINAPI ServerWorkThread(LPVOID arg)
{
	while (true) {
		if (stageIndex == STAGE_ROLE) {
			bool isFinish = true;
			for (int i = 0; i < 3; i++) {
				if (selectPlayerRole[i] == 'n') {
					isFinish = false;
					break;
				}
			}
			if (isFinish) {
				// Stage 1 �� ���� ȹ��
				StageMgr.Stage_1();
				// ���� ��ġ ����
				MovePacket setPosition;
				setPosition.type = S2CMove_IDLE;
				for (int i = 0; i < 3; ++i) {
					setPosition.id = i;
					setPosition.x = threadHandles[i].x;
					setPosition.y = threadHandles[i].y;
					for (int j = 0; j < 3; ++j) {
						threadHandles[j].onBoard = StageMgr.Ground;
						send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&setPosition), sizeof(MovePacket), 0);
					}
				}

				S2CChangeStagePacket changePacket;
				changePacket.stageNum = STAGE_01;
				changePacket.type = S2CChangeStage;
				for (int x = 0; x < 3; x++) {
					send(threadHandles[x].clientSocket, (char*)&changePacket, sizeof(S2CChangeStagePacket), 0);
				}
				stageIndex = STAGE_01;
				StageTimerStart();
			}
		}
		else if (stageIndex >= STAGE_01) { // � �� ���� ���������� ���� �̰� �����̴ϱ� == -> >= ���� ����
			DWORD jewelyRetVal = WaitForSingleObject(jewelyEatHandle, 0);
			if (jewelyRetVal == WAIT_OBJECT_0) {
				if (!StageMgr.jewely.empty()) {
					StageMgr.currentVisibleJewely = StageMgr.jewely.front();
					StageMgr.jewely.pop();
					ResetEvent(jewelyEatHandle);
				}
				currentJewelyNum++;
			}
			//��ö ����: �ð� ������ ���������̶� ��ȭ�ؼ� �غ���
			//���� ���� ���� == StageMgr.MaxJewelyNum && ���� ���� 1�� �̻� �������� -> �� ���̰� �ϱ� ����

			if (!isVisibleDoor) {
				if (currentJewelyNum == StageMgr.maxJewelyNum) {
					typePacket visibleDoor;
					visibleDoor.type = S2CDoorVisible;
					if (!isVisibleDoor && currentJewelyNum == StageMgr.maxJewelyNum) {// ������ �ð��� ���� �������� 1�� �̻� ���Ҵٸ� ������ �� ����� �� ��ġ ���̰� ����
						//isVisibleDoor => �� ������ ���ְ� => �̰� Ű�� �� ��ġ�� �˰� �� �� �ְ� ����\					
						for (int i = 0; i < 3; i++)
							send(threadHandles[i].clientSocket, reinterpret_cast<char*>(&visibleDoor), sizeof(typePacket), 0);
						isVisibleDoor = true;
					}
				}
			}


			for (int i = 0; i < 3; i++) {
				if (!threadHandles[i].Falling) {
					if (threadHandles[i].onBoard.FT_Collide_Fall(threadHandles[i])) {
						SetEvent(threadHandles[i].jumpEventHandle);
						threadHandles[i].isJump = true;
						threadHandles[i].Falling = true;
						threadHandles[i].jumpStartTime = high_resolution_clock::now();
						threadHandles[i].jumpCurrentTime = high_resolution_clock::now();
					}
				}

				DWORD retVal = WaitForSingleObject(threadHandles[i].jumpEventHandle, 0);
				if (retVal == WAIT_OBJECT_0) {
					if (!threadHandles[i].isJump) {
						cout << "jump start" << endl;
						threadHandles[i].isJump = true;
						threadHandles[i].jumpStartTime = high_resolution_clock::now();
						threadHandles[i].jumpCurrentTime = high_resolution_clock::now();
						threadHandles[i].v = 0.f;
						threadHandles[i].y = threadHandles[i].ground;
					}

					auto startDuration = high_resolution_clock::now() - threadHandles[i].jumpStartTime;		// ����� ���� ���ۺ��� ����ð�
					auto currentDuration = high_resolution_clock::now() - threadHandles[i].jumpCurrentTime;	// ������ ���� ���� �ð�����
					MovePacket mPacket;
					mPacket.id = threadHandles[i].clientId;
					mPacket.type = S2CMove_JUMP;

					// ���� ���� (���� or for��)�� �ʿ�� ���� ���̴� ������ ���� �����ּ���!
					if (threadHandles[i].Falling || duration_cast<milliseconds>(startDuration).count() > 300) {
						if (threadHandles[i].v < FLT_EPSILON)
							threadHandles[i].v = 0.f;

						if (duration_cast<milliseconds>(currentDuration).count() > 30/* && ((threadHandles[i].y) < threadHandles[i].ground)*/) {//30ms���� �Ǵ� y�� ���� �� ������
							if (threadHandles[i].direction == DIRECTION::LEFT) {
								threadHandles[i].x -= 10;
							}
							else if (threadHandles[i].direction == DIRECTION::RIGHT) {
								threadHandles[i].x += 10;
							}
							mPacket.x = threadHandles[i].x;
							threadHandles[i].v += threadHandles[i].g;
							threadHandles[i].y += threadHandles[i].v;

							for (OBJECT& ft : StageMgr.Ft) {// ���ǿ� ����
								if (ft.Ft_Collision(threadHandles[i]) /*&& (threadHandles[i].y > ft.y - ft.hei * 2)*/) { // ���� �ݶ��̵�� �浹 Ȯ�� && ���� �ɷȴٸ�
									cout << "collide on Board" << endl;
									ResetEvent(threadHandles[i].jumpEventHandle); // ������ �� �̻����� ���� - ���߿� ���� �ʴ´�
									threadHandles[i].direction = DIRECTION::NONE;
									threadHandles[i].v = 0.f;
									threadHandles[i].isJump = false;
									threadHandles[i].Falling = false;
									threadHandles[i].onBoard = ft;
									threadHandles[i].y = threadHandles[i].ground = ft.y - ft.hei; //��ġ ����ֱ�
									cout << "resetEvent: jump" << endl;
									mPacket.type = S2CMove_IDLE;
									break;
								}
							}
							mPacket.y = threadHandles[i].y;
							threadHandles[i].jumpCurrentTime = high_resolution_clock::now(); // ������ �����ð��� ���� ���� ������ �ð� ����
							for (int j = 0; j < 3; j++) {
								send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&mPacket), sizeof(MovePacket), 0);
							}
						}
						//if (threadHandles[i].y > threadHandles[i].ground) {// ĳ���Ͱ� ���� ��Ҵٸ�
						//	cout << "resetEvent: jump" << endl;
						//	ResetEvent(threadHandles[i].jumpEventHandle);
						//	threadHandles[i].direction = DIRECTION::NONE;
						//	threadHandles[i].v = 0.f;
						//	threadHandles[i].isJump = false;
						//	threadHandles[i].Falling = false;							
						//	mPacket.x = threadHandles[i].x;
						//	mPacket.y = threadHandles[i].y = threadHandles[i].ground; // ��ġ �����ֱ�
						//	mPacket.type = S2CMove_IDLE;
						//	for (int j = 0; j < 3; j++) {
						//		send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&mPacket), sizeof(MovePacket), 0);
						//	}
						//}
					}
					else if (duration_cast<milliseconds>(currentDuration).count() > 30 && !threadHandles[i].Falling) { //���
						if (threadHandles[i].direction == DIRECTION::LEFT) {
							threadHandles[i].x -= 10;
						}
						else if (threadHandles[i].direction == DIRECTION::RIGHT) {
							threadHandles[i].x += 10;
						}
						mPacket.x = threadHandles[i].x;
						threadHandles[i].v -= threadHandles[i].g;
						threadHandles[i].y += threadHandles[i].v;

						for (OBJECT& ft : StageMgr.Ft) {
							if ((ft.y < threadHandles[i].y) && ft.Collision(threadHandles[i])) {//�ö󰡴ٰ� ���ǿ� �ɷȴٸ� �������� �Ӹ� �浹
								cout << "collide head" << endl;

								threadHandles[i].v = 0.f;
								threadHandles[i].Falling = true;
								break;
							}
						}
						mPacket.y = threadHandles[i].y += threadHandles[i].v;
						threadHandles[i].jumpCurrentTime = high_resolution_clock::now();
						for (int j = 0; j < 3; j++) {
							send(threadHandles[j].clientSocket, reinterpret_cast<char*>(&mPacket), sizeof(MovePacket), 0);
						}
					}

				}
			}
		}
	}
	return 0;
}

void StageTimerStart()
{
	if (_timer.IsRunning() == true)
	{
		return;
	}

	_timer.Start(std::chrono::milliseconds(1000), [=]
		{
			S2CStageTimePassPacket packet;
			packet.timePassed = _timer.GetElapsedTime() / (double)1000;

			for (int x = 0; x < 3; x++) {
				send(threadHandles[x].clientSocket, (char*)&packet, sizeof(S2CStageTimePassPacket), 0);
			}

			if (timeoutSeconds <= packet.timePassed)
			{
				TimeoutStage();
				typePacket timeoutPacket;
				for (int x = 0; x < 3; x++) {
					send(threadHandles[x].clientSocket, (char*)&timeoutPacket, sizeof(typePacket), 0);
				}
			}
			if (packet.timePassed >= 60 * 4) {
				if (!isVisibleDoor) {
					typePacket visibleDoorPacket;
					visibleDoorPacket.type = S2CDoorVisible;
					for (int x = 0; x < 3; x++) {
						send(threadHandles[x].clientSocket, (char*)&visibleDoorPacket, sizeof(typePacket), 0);
					}
					isVisibleDoor = true;
				}
			}
		});
}

void TimeoutStage()
{
	_timer.Stop();
}

void ProcessPacket(ThreadInfo& clientInfo, char* packetStart) // ���� �����ʴ� �Լ� - recv()�ϸ鼭 �ҷ���
{
	if (packetStart == nullptr)
		return;
	switch (reinterpret_cast<char*>(packetStart)[0]) {
	case C2SSelectRole:
	{
		C2SRolePacket* packet = reinterpret_cast<C2SRolePacket*>(packetStart);
		bool change = true;
		//already Exist Role Check

		//non exist Role
		selectMutex.lock();
		for (int i = 0; i < 3; i++) { // ������ ��������? ��� ����?
			if (selectPlayerRole[i] == packet->role) {
				change = false;
				break;
			}
		}
		if (change)
			selectPlayerRole[clientInfo.clientId] = packet->role;
		selectMutex.unlock();
		if (change) {
			//send SelectPacket for all Client
			S2CRolePacket sendPacket;
			sendPacket.id = clientInfo.clientId;
			sendPacket.role = packet->role;
			sendPacket.type = S2CSelectRole;
			for (int i = 0; i < 3; i++) {
				send(threadHandles[i].clientSocket, reinterpret_cast<char*>(&sendPacket), sizeof(S2CRolePacket), 0);
			}
		}
	}
	break;
	case C2SChangRole:
	{
		C2SRolePacket* packet = reinterpret_cast<C2SRolePacket*>(packetStart);
		playerRole[clientInfo.clientId] = packet->role; // ĳ���� �ѷ����� �� ������ ��ȣ���� �ʿ� ���ٰ� ������
		//send changePacekt for all Client
		S2CRolePacket sendPacket;
		sendPacket.id = clientInfo.clientId;
		sendPacket.role = packet->role;
		sendPacket.type = S2CChangeRole;
		for (int i = 0; i < 3; i++) {
			send(threadHandles[i].clientSocket, reinterpret_cast<char*>(&sendPacket), sizeof(S2CRolePacket), 0);
		}
	}
	break;
	case C2SMove:
	{
		MovePacket* packet = reinterpret_cast<MovePacket*>(packetStart);
		DWORD retVal = WaitForSingleObject(clientInfo.jumpEventHandle, 0);
		if (retVal == WAIT_OBJECT_0) {
			return;
		}
		if (packet->y == SHRT_MAX) {
			cout << "setEvent: jump" << endl;
			SetEvent(clientInfo.jumpEventHandle);
			packet->type = S2CMove_JUMP;
		}
		else if (packet->y == SHRT_MIN) {
			clientInfo.direction = DIRECTION::NONE;
			packet->type = S2CMove_IDLE;
		}
		else if (packet->x == 1) {
			if (clientInfo.wid_a <= 10.f)
				clientInfo.wid_a += 0.1f;
			if (clientInfo.wid_v <= 10.f)
				clientInfo.wid_v += clientInfo.wid_a;
			clientInfo.x += clientInfo.wid_v;
			clientInfo.direction = DIRECTION::RIGHT;
			packet->type = S2CMove_RIGHT;
		}
		else if (packet->x == -1) {
			if (clientInfo.wid_a <= 10.f)
				clientInfo.wid_a += 0.1f;
			if (clientInfo.wid_v <= 10.f)
				clientInfo.wid_v += clientInfo.wid_a;
			clientInfo.x -= clientInfo.wid_v;
			clientInfo.direction = DIRECTION::LEFT;
			packet->type = S2CMove_LEFT;
		}
		/*	if (packet->x == 0 && packet->y == 0) {
				clientInfo.wid_v = 0.f;
				clientInfo.wid_a = 0.f;
			}*/

		packet->x = clientInfo.x;
		packet->y = clientInfo.y;

		for (int i = 0; i < 3; i++) {
			send(threadHandles[i].clientSocket, reinterpret_cast<char*>(packet), sizeof(MovePacket), 0);
		}
	}
	break;
	case C2SEndout:
	{
		S2CEndPacket* packet = reinterpret_cast<S2CEndPacket*>(packetStart);
		S2CEndPacket sendPacket;
		sendPacket.type = S2CEndout;

		for (int i = 0; i < 3; i++) {
			send(threadHandles[i].clientSocket, reinterpret_cast<char*>(&sendPacket), sizeof(S2CEndPacket), 0);
		}
	}
	break;

	case C2SRetry:
	{

	}
	break;
	default:
		// Packet Error
		break;
	}
}

int GetPacketSize(char packetType)
{
	int retVal = -1;
	switch (packetType)
	{
	case C2SChangRole:
	case C2SSelectRole:
		retVal = sizeof(C2SRolePacket);
		break;
	case C2SMove:
		retVal = sizeof(MovePacket);
		break;
	case C2SRetry:
	case C2SEndout:
		retVal = sizeof(C2SEndPacket);
		break;
	default:
		break;
	}
	return retVal;
}
