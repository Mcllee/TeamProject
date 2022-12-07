#pragma once
#include "stdafx.h"
#include "../NetGameProjServer/protocol.h"
#include "Stage.h"

void Move()
{
	if (stageIndex == 6 || !myCharacterOn) {
		return;
	}
	
	MovePacket move;
	move.type = C2SMove;
	move.id = myId;

	/*DWORD retVal = WaitForSingleObject(jumpEvent, 0);
	if (WAIT_OBJECT_0 == retVal)
		return;*/
	if (keybuffer[VK_UP]) {
		SetEvent(jumpEvent);
		move.y = SHRT_MAX;
	}
	if (keybuffer[VK_LEFT]) {		
		DWORD retVal = WaitForSingleObject(idleStateEvent, 0);
		if (WAIT_OBJECT_0 == retVal)
			ResetEvent(idleStateEvent);		
		move.x = -1;
	}
	else if (keybuffer[VK_RIGHT]) {
		DWORD retVal = WaitForSingleObject(idleStateEvent, 0);
		if (WAIT_OBJECT_0 == retVal)
			ResetEvent(idleStateEvent);		
		move.x = 1;
	}

	if ((!keybuffer[VK_UP] && !keybuffer[VK_RIGHT] && !keybuffer[VK_LEFT])
		|| (keybuffer[VK_RIGHT] && keybuffer[VK_LEFT])) {
		DWORD retVal = WaitForSingleObject(idleStateEvent, 0);
		if (WAIT_OBJECT_0 == retVal)
			return;
		SetEvent(idleStateEvent);
		move.y = SHRT_MIN;
	}
	SendPacket(&move);

}

// WAV���� ���� �м� �Լ� (LoadSound()�Լ������� ȣ��)
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	MCI_OPEN_PARMS	mciOpenParms;
	UINT			wDeviceID = 0;

	DWORD Result;
	mciOpenParms.lpstrDeviceType = L"MPEGvideo";
	mciOpenParms.lpstrElementName = lpszWave;
	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);
	if (Result)
		return Result;
	wDeviceID = mciOpenParms.wDeviceID;
	mciPlayParms.dwCallback = (DWORD)hWnd;
	if (Result)
		return Result;
	return 0;
}

// WAV���� ���� ���������� �°� ����ϱ� (Main.cpp���� �������� ����� ȣ�� �ʿ�)
void LoadSound(HWND hWnd)
{
	DWORD SelectBGM{};

	//if (stage == 0)
	//{
	//	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
	//	SelectBGM = LoadWAV(hWnd, L"BGM\\���1.mp3");//���⿡ ����ϰ���� mp3������ ��θ� �Է��ϸ� �ȴ�.
	//	SelectBGM = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	//}
	//else if (stage == 1)
	//{
	//	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
	//	SelectBGM = LoadWAV(hWnd, L"BGM\\���2.mp3");//���⿡ ����ϰ���� mp3������ ��θ� �Է��ϸ� �ȴ�.
	//	SelectBGM = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	//}
	//else if (stage == 2)
	//{
	//	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
	//	SelectBGM = LoadWAV(hWnd, L"BGM\\���3.mp3");//���⿡ ����ϰ���� mp3������ ��θ� �Է��ϸ� �ȴ�.
	//	SelectBGM = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	//}
	//else if (stage == 3)
	//{
	//	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
	//	SelectBGM = LoadWAV(hWnd, L"BGM\\���4.mp3");//���⿡ ����ϰ���� mp3������ ��θ� �Է��ϸ� �ȴ�.
	//	SelectBGM = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	//}
	//else if (stage == 4)
	//{
	//	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
	//	SelectBGM = LoadWAV(hWnd, L"BGM\\���5.mp3");//���⿡ ����ϰ���� mp3������ ��θ� �Է��ϸ� �ȴ�.
	//	SelectBGM = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	//}
}

