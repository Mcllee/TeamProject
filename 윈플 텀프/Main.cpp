#pragma once
#include"stdafx.h"
#include "ImageMgr.h"
#include "StageMgr.h"
#include"protocol.h"
HINSTANCE g_hInst;
ImageMgr myImageMgr;
StageMgr myStageMgr;
Stage currentStage;

WSADATA WSAData;
SOCKET c_socket;

int stageIndex = 0;
int currneClientNum = 1;

int prevSize = 0;
int myId = -1;

char recvBuf[MAX_BUF_SIZE] = { 0 };

HWND g_hWnd;
DWORD WINAPI ClientrecvThread (LPVOID arg);


// ���α׷� ���� ����� ���� �ʱ�ȭ �� ������ ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	LPCTSTR IpszClass = L"fire boy and water girl";
	LPCTSTR IpszWindowName = L"window programming";

	g_hInst = hInstance;

	// ������ �� �ʱ�ȭ
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbWndExtra = 0;
	WndClass.cbClsExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	// ��ü �̹��� �ʱ�ȭ
	myImageMgr.LoadImages();

	// ���� ������ ����
	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 800, NULL, (HMENU)NULL, hInstance, NULL);

	// ���� ������ Set Visible
	ShowWindow(hWnd, nCmdShow);

	// ���� ������ Update Data
	UpdateWindow(hWnd);

	if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0)
		return 1;
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	HANDLE chandle;
	chandle = CreateThread(NULL, 0, ClientrecvThread, reinterpret_cast<LPVOID>(c_socket), 0,NULL);
	

	// �������� ����
	currentStage = myStageMgr.getStage(stageIndex);

	// ������ Main Message Loop
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

/*
	[���� ������ �۾� �Լ�]
	1. WM_CREATE : ���� �ʱ�ȭ

	2. WM_COMMAND : Ű �Է�
					(IDC_BUTTON1 : Title ȭ�� ���� ��ư,
					 IDC_BUTTON2 : Game Over ȭ�鿡�� ����� ��ư)
					 IDC_BUTTON3 : Game Over ȭ�鿡�� ���α׷� ���� ��ư,
					 IDC_BUTTON4 : Stage Clear ������ ���� ���������� �̵�)

	3. WM_TIMER : Ÿ�̸� ȣ��� ����, ���� switch������ timer�� ID�� ����� �ش� �۾��� ����
					(Timer ID : case WM_CREATE �� �ִ� SetTimer �Լ��� 2��° �Ķ����)
					(Timer ID 1 : User �Է¿� ���� ĳ���� �̵��� �浹üũ,
					 Timer ID 2 : ĳ����(Fire boy, Water girl)�� �ִϸ��̼� ������ (�� 8��)
					 Timer ID 3 : ������Ʈ �ִϸ��̼� ����
					 Timer ID 4 : ĳ���� �ⱸ, Stage_03�� �̵� ���� �ִϸ��̼� (Timer ID 3 �� ȣ�� �ð��� �ٸ�)
					 Timer ID 5 : ���� �ð� (time����) �ʰ��� ��� ȭ�� ���� ()

	4. WM_KEYDOWN : Ű�� ������ �� ����

	5. WM_KEYUP : Ű�� (���ȴٰ�) �ö� �� ����

	6. WM_PAINT : ���� �����쿡 ������Ʈ �׸���

	6. WM_DESTROY : ���� ������ ���� (== ���α׷� ����)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static HDC memdc;
	static HBITMAP hbitmap;

	g_hWnd = hWnd;

	static HWND start_button, retry_button, end_button, next_button, server_addr;
	static HWND selectRoleLeftArrow;
	static HWND selectRoleRightArrow;
	static HWND selectBtn;
	static BOOL back = FALSE;
	static BOOL isArrow = true;

	static int time = 300;

	
	currentStage = myStageMgr.getStage(stageIndex);

	switch (uMsg) {
	case WM_CREATE: {	// ���α׷� ���� ���࿡�� 1ȸ ����
		start_button = CreateWindow(L"button", L"123123", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 450, 600, 158, 60, hWnd, (HMENU)BTN_START, g_hInst, NULL);
		SendMessage(start_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.buttonimg));

		static HFONT s_hFont = (HFONT)NULL;
		NONCLIENTMETRICS nonClientMetrics;
		ZeroMemory(&nonClientMetrics, sizeof(nonClientMetrics));
		nonClientMetrics.cbSize = sizeof(NONCLIENTMETRICS);
		s_hFont = CreateFontIndirect(&nonClientMetrics.lfCaptionFont);

		server_addr = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 550, 158, 30, hWnd, (HMENU)EDIT_SERVER_ADDR, g_hInst, NULL);
		SendMessage(server_addr, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

		SetTimer(hWnd, 1, 30, NULL);
		SetTimer(hWnd, 2, 100, NULL);
		SetTimer(hWnd, 3, 50, NULL);
		SetTimer(hWnd, 4, 50, NULL);
		SetTimer(hWnd, 5, 1000, NULL);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case BTN_START:
			wchar_t wc_s_addr[256];
			char c_s_addr[256];
			size_t t;
			GetWindowText(server_addr, wc_s_addr, 256);
			wcstombs_s(&t, c_s_addr, wc_s_addr, 256);

			if (NetworkInit(hWnd, c_s_addr)) {
				DestroyWindow(start_button);
				DestroyWindow(server_addr);
				if(stageIndex < STAGE_ROLE)
					stageIndex = STAGE_LOADING;
				currentStage = myStageMgr.getStage(stageIndex);
			}
			else {
				SetWindowText(server_addr, LPCWSTR());
			}
			break;
		case BTN_RESTART:
			time = 300;
			for (PLAYER& pl : players)
				pl.on = true;


			SetTimer(hWnd, 1, 30, NULL);
			SetTimer(hWnd, 2, 100, NULL);
			SetTimer(hWnd, 3, 50, NULL);
			SetTimer(hWnd, 4, 50, NULL);
			SetTimer(hWnd, 5, 1000, NULL);
			back = FALSE;
			currentStage.time_over = FALSE;
			DestroyWindow(retry_button);
			DestroyWindow(end_button);
			break;

		case BTN_LEFT_ARROW:
		{	
			C2SRolePacket makePacket;
			makePacket.type = C2SChangeRole;
			makePacket.role = 'f'; // ���� ���� �� «
			players[0].role = 'e';
			SendPacket(&makePacket);
		}
		break;
		case BTN_RIGHT_ARROW:
		{
			C2SRolePacket makePacket;
			makePacket.type = C2SChangeRole;
			makePacket.role = 'f'; 
			players[0].role = 'w';// ���� ���� �� «
			SendPacket(&makePacket);
		}
		break;
		case BTN_SELECT:
		{
			C2SRolePacket makePacket;
			makePacket.type = C2SSelectRole;
			makePacket.role = 'f'; // ���� ���� �� « �����ؾߵ�
			SendPacket(&makePacket);

			
			currentStage = myStageMgr.getStage(stageIndex = STAGE_01);
		}
		break;
		case BTN_QUIT:
			back = FALSE;
			currentStage.time_over = FALSE;
			DestroyWindow(retry_button);
			DestroyWindow(end_button);
			PostQuitMessage(0);
			DeleteObject(hbitmap);
			DeleteDC(memdc);
			break;

		case BTN_NEXT_STAGE:
			back = FALSE;
			currentStage.clear = FALSE;
			for (PLAYER& pl : players)
				pl.on = true;
			time = 300;
			currentStage = myStageMgr.getStage(++stageIndex);

			currentStage.red_total = currentStage.Red_Jewel.size();
			currentStage.blue_total = currentStage.Blue_Jewel.size();
			currentStage.count = 0;
			SetTimer(hWnd, 1, 30, NULL);
			SetTimer(hWnd, 2, 100, NULL);
			SetTimer(hWnd, 3, 50, NULL);
			SetTimer(hWnd, 4, 50, NULL);
			SetTimer(hWnd, 5, 1000, NULL);
			DestroyWindow(next_button);
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			// ĳ���� �̵��� �浹üũ
			for (PLAYER& pl : players) {
				for (auto& bj : currentStage.Blue_Jewel) {
					if (bj.Collision(pl)) {
						bj.SetVisible(false);
					}
				}
			}

			if (STAGE_01 <= currentStage.stage)
			{
				for (PLAYER& pl : players) {
					for (auto& t : currentStage.Trap) {
						if (t.Collision(pl)) {
							pl.on = FALSE;
							currentStage.Die.SetVisible(true);
							currentStage.Die.x = t.x;
							currentStage.Die.y = t.y - 100;
						}
					}
				}
			}
			break;
		case 2:				// ĳ���� ������
			for (PLAYER& pl : players) pl.Frame = (pl.Frame + 1) % 9;
			break;
		case 3:				// ����, ����, ���, �� �ִϸ��̼� ó���� �������� Ŭ���� ���� ������ ��ó��(Next ������� ���ó��)
			for (OBJECT& bj : currentStage.Blue_Jewel)
				if (bj.GetVisible() && bj.ChangeFrame(1, true))
					bj.image_x = 0;

			for (OBJECT& rj : currentStage.Red_Jewel)
				if (rj.GetVisible() && rj.ChangeFrame(1, true))
					rj.image_x = 0;

			for (OBJECT& t : currentStage.Trap)
				if (t.GetVisible())
					t.ChangeFrame(1, true);

			// Fire bot, Water girl �� 1���̶� ��� && ���� Stage�� 1 �̻��� ��� (Stage 0�� Title ȭ��)
			if (currentStage.Die.GetVisible() && STAGE_01 <= currentStage.stage)
			{
				if (currentStage.Die.ChangeFrame(1, false))
				{
					back = TRUE;
					currentStage.Die.SetVisible(FALSE);
					currentStage.Die.image_x = 0;

					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
					KillTimer(hWnd, 3);
					KillTimer(hWnd, 4);
					KillTimer(hWnd, 5);

					retry_button = CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 300, 500, 200, 100, hWnd, (HMENU)BTN_RESTART, g_hInst, NULL);
					SendMessage(retry_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.retryimg));
					end_button = CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 700, 500, 200, 100, hWnd, (HMENU)BTN_QUIT, g_hInst, NULL);
					SendMessage(end_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.endimg));
					mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
				}
			}

			// �����̽� Ŭ���� �� ������ ���� �ִϸ��̼�
			// if (currentStage.red_door.Collision(players[1]) && currentStage.blue_door.Collision(players[0]))
			//{
			//	// if (currentStage.red_door.ChangeFrame(1) && currentStage.blue_door.ChangeFrame(1)) {
			//	if (currentStage.blue_door.ChangeFrame(1)) {
			//		currentStage.stair = FALSE;
			//		currentStage.red_door.image_x = 0;
			//		currentStage.blue_door.image_x = 0;
			//		next_button = CreateWindow(L"button", L"123123", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 500, 400, 200, 100, hWnd, (HMENU)BTN_NEXT_STAGE, g_hInst, NULL);
			//		SendMessage(next_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.clear_img));
			//	}
			//}

			for (PLAYER& pl : players) {
				for (OBJECT& btn : currentStage.button)
					if (btn.GetVisible() && btn.Collision(pl))
						btn.ChangeFrame(1, false);
			}
			break;
		case 4:
			/*if (currentStage.red_door.GetVisible())
				currentStage.red_door.ChangeFrame(1);
			else
				currentStage.red_door.ChangeFrame(-1);*/

			if (currentStage.blue_door.Collision(players[1]))
				currentStage.blue_door.ChangeFrame(1, false);
			else if (currentStage.blue_door.image_x != 0) {

				if (currentStage.blue_door.image_x + currentStage.blue_door.imageMoveWid == currentStage.blue_door.MaxWid)
					currentStage.blue_door.image_x -= currentStage.blue_door.imageMoveWid;

				currentStage.blue_door.ChangeFrame(-1, false);
			}

			// Stage_03() ���� ������ X�� �̵� �� (block1.PNG ���� ����)
			for (OBJECT& block : currentStage.block)
				if (block.GetVisible())
					block.ChangeFrame(-1, false);
				else
					block.ChangeFrame(1, false);
			break;

		case 5:
			//Ÿ�Ӿƿ��� �� ����

			if (--time == 0)
			{
				currentStage.time_over = TRUE;
				back = TRUE;
				retry_button = CreateWindow(L"button", L"123123", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 300, 500, 200, 100, hWnd, (HMENU)BTN_RESTART, g_hInst, NULL);
				SendMessage(retry_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.retryimg));
				end_button = CreateWindow(L"button", L"123123", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 700, 500, 200, 100, hWnd, (HMENU)BTN_QUIT, g_hInst, NULL);
				SendMessage(end_button, BM_SETIMAGE, 0, (LPARAM)((HBITMAP)myImageMgr.endimg));
				mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
				KillTimer(hWnd, 5);
			}

			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		keybuffer[wParam] = TRUE;
		Move();
		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYUP:
		hDC = GetDC(hWnd);
		keybuffer[wParam] = FALSE;
		Move();
		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		hbitmap = CreateCompatibleBitmap(hDC, 1200, 800);
		memdc = CreateCompatibleDC(hDC);
		SelectObject(memdc, hbitmap);

		myImageMgr.DrawMap(&memdc, currentStage.stage, currentStage);

		if (STAGE_ROLE == currentStage.stage) {
			if (isArrow) {
				selectRoleLeftArrow = CreateWindow(L"button", L"RoleSelect", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 50, 280, 80, 41, hWnd, (HMENU)BTN_LEFT_ARROW, g_hInst, NULL);
				selectRoleRightArrow = CreateWindow(L"button", L"RoleSelect", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 330, 280, 80, 41, hWnd, (HMENU)BTN_RIGHT_ARROW, g_hInst, NULL);
				selectBtn = CreateWindow(L"button", L"RoleSelect", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 500, 620, 120, 45, hWnd, (HMENU)BTN_SELECT, g_hInst, NULL);
				SendMessage(selectRoleLeftArrow, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)((HBITMAP)myImageMgr.leftArrow));
				SendMessage(selectRoleRightArrow, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)((HBITMAP)myImageMgr.rightArrow));
				SendMessage(selectBtn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)((HBITMAP)myImageMgr.selectBtn));
				isArrow = false;
			}
		}
		else if (STAGE_ROLE < currentStage.stage) {
			if (selectRoleLeftArrow != nullptr) {
				DestroyWindow(selectRoleLeftArrow);
				DestroyWindow(selectRoleRightArrow);
				DestroyWindow(selectBtn);
			}

			myImageMgr.DrawPlayers(&memdc, currentStage);
			myImageMgr.DrawTimer(&memdc, time);

			for (auto& rj : currentStage.Red_Jewel) {
				if (rj.GetVisible())
					myImageMgr.Jewelry_red.Draw(memdc, rj.x, rj.y, rj.wid, rj.hei, rj.image_x, 0, 28, 24);
			}
			for (auto& bj : currentStage.Blue_Jewel) {
				if (bj.GetVisible()) {
					myImageMgr.Jewelry_blue.Draw(memdc, bj.x, bj.y, bj.wid, bj.hei, bj.image_x, 0, 28, 24);
				}
			}

			// ����� ���� Anim
			if (currentStage.Die.GetVisible())	myImageMgr.die.Draw(memdc, currentStage.Die.x, currentStage.Die.y, 100, 100, currentStage.Die.image_x, currentStage.Die.image_y, 159, 89);
			if (currentStage.clear)	back = TRUE;
			if (currentStage.time_over) myImageMgr.timeout.Draw(memdc, 400, 200, 400, 250, 0, 0, 486, 286);
			if (currentStage.stair)
			{
				myImageMgr.red_stair.Draw(memdc, currentStage.red_door.x, currentStage.red_door.y + 30, 50, 80, currentStage.red_door.image_x, 0, 50, 73);
				myImageMgr.blue_stair.Draw(memdc, currentStage.blue_door.x, currentStage.red_door.y + 30, 50, 80, currentStage.red_door.image_x, 0, 54, 77);
				for (PLAYER& pl : players)
					pl.on = false;
			}
			if (back)
			{
				myImageMgr.backimg.Draw(memdc, 0, 0, 1200, 800, 0, 0, 1200, 800);
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
				currentStage.clear = FALSE;
				mciSendCommand(1, MCI_CLOSE, 0, (DWORD)NULL);
			}
		}

		//if (currentStage.clear == FALSE && back == FALSE)
		//{
		//	for (int i = 0; i < 90; i++) // 0~19���� �Ķ� ��� �� 20~29���� �Ķ� ��.�� |||| 30~49���� ���� ��� �� 50~59���� ������ ��.�� 60~79 �ʷ� ��� 80~89 �ʷϿ�.��
		//	{
		//		if (currentStage.Trap[i].GetVisible())
		//		{
		//			
		//			if (i < 20)
		//			{
		//				myImageMgr.blue_water_center.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 23, 14);
		//			}
		//			if (i >= 20 && i < 25)
		//			{
		//				myImageMgr.blue_water_left.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 23, 23);
		//			}
		//			if (i >= 25 && i < 30)
		//			{
		//				myImageMgr.blue_water_right.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 23, 23);
		//			}
		//			
		//			if (i >= 30 && i < 50)
		//			{
		//				myImageMgr.red_water_center.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 21, 14);
		//			}
		//			if (i >= 50 && i < 55)
		//			{
		//				myImageMgr.red_water_left.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 24, 25);
		//			}
		//			if (i >= 55 && i < 60)
		//			{
		//				myImageMgr.red_water_right.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 24, 25);
		//			}
		//			
		//			if (i >= 60 && i < 80)
		//			{
		//				myImageMgr.green_water_center.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 23, 14);
		//			}
		//			if (i >= 80 && i < 85)
		//			{
		//				myImageMgr.green_water_left.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 24, 25);
		//			}
		//			if (i >= 85 && i < 90)
		//			{
		//				myImageMgr.green_water_right.Draw(hDC, currentStage.Trap[i].x, currentStage.Trap[i].y, 25, 25, currentStage.Trap[i].image_x, currentStage.Trap[i].image_y, 24, 25);
		//			}
		//		}
		//	}
		//}

		BitBlt(hDC, 0, 0, 1200, 800, memdc, 0, 0, SRCCOPY);
		DeleteObject(hbitmap);
		DeleteDC(memdc);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(hbitmap);
		DeleteDC(memdc);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI ClientrecvThread(LPVOID arg)
{
	
	while (true) {
		int recvRetVal = recv(c_socket, recvBuf + prevSize, MAX_BUF_SIZE - prevSize, 0);
		if (recvRetVal != 0 && recvRetVal != -1) {
			ConstructPacket(recvBuf, recvRetVal);
		}
		else {
			WSAGetLastError();
		}
	}
	return 0;
}