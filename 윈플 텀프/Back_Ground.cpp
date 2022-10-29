#pragma once
#include"stdafx.h"

// ������ ���α׷��ֿ��� Ű ���� �Է��� ���� �Լ� (���� ����)
void Loop(bool keyDown)
{
	if (true == keyDown) {
		//����Ű �Է��� ���ؼ� ���� if�� �ۼ������� [ ] �ȿ� ���ϴ� Ű�� �ൿ�� ������ �۵��Ѵ�.
		if (keybuffer[VK_LEFT])
		{
			fire.wid_a += 1;
			if (fire.wid_a > 5) {
				fire.wid_a = 10;
			}
			fire.dic = -1;
			fire.is_Move = TRUE;
		}
		if (keybuffer[VK_RIGHT])
		{
			fire.wid_a += 1;
			if (fire.wid_a > 5) {
				fire.wid_a = 10;
			}
			fire.dic = 1;
			fire.is_Move = TRUE;
		}
		if (keybuffer[VK_UP])
		{
			fire.is_Jumping = TRUE;
		}
		if (keybuffer[VK_DOWN])
		{
			//	button[0].On = FALSE;
			//	block[0].On = TRUE;
		}
		if (keybuffer['d'] || keybuffer['D'])
		{
			water.wid_a += 1;
			if (water.wid_a > 5) {
				water.wid_a = 10;
			}
			water.dic = 1;
			water.is_Move = TRUE;
		}
		if (keybuffer['a'] || keybuffer['A'])
		{
			water.wid_a += 1;
			if (water.wid_a > 5) {
				water.wid_a = 10;
			}
			water.dic = -1;
			water.is_Move = TRUE;
		}
		if (keybuffer['s'] || keybuffer['S'])
		{
			//	button[0].On = TRUE;
		}
		if (keybuffer['w'] || keybuffer['W'])
		{
			water.is_Jumping = TRUE;
		}
	}
	else if (false == keyDown) {
		water.is_Move = FALSE;
		water.wid_a = 0;
		water.is_Speed_Down = TRUE;
		fire.is_Move = FALSE;
		fire.wid_a = 0;
		water.Frame = 0;
		fire.Frame = 0;
		fire.is_Speed_Down = TRUE;
	}
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

