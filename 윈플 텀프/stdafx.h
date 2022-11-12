#pragma once

#include <WinSock2.h>
#include <windows.h>
#include <tchar.h>
#include <atlimage.h>
#include <mmsystem.h>
#include <unordered_map>
#include <array>

#pragma comment(lib,"winmm.lib")
#pragma comment (lib, "msimg32.lib")

#define BTN_START			100
#define BTN_RESTART			200
#define BTN_QUIT			300
#define BTN_NEXT_STAGE		400
#define EDIT_SERVER_ADDR	500
#define BTN_LEFT_ARROW		600
#define BTN_RIGHT_ARROW		700
#define BTN_SELECT			800

#define STAGE_TITLE			0
#define STAGE_LOADING		1
#define STAGE_LOBBY			2
#define STAGE_01			3
#define STAGE_02			4
#define STAGE_03			5


// Network Module
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")
extern WSADATA	WSAData;
extern SOCKET	c_socket;
//===============

void Move();

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
void LoadSound(HWND hWnd);

struct FootHold {
	int x = 0, y = 0;
	int wid = 111, hei = 23;
	bool W_On = FALSE, F_On = FALSE;
};

class PLAYER {
public:
	int x, y;					// ���ϴ� ��ǥ
	int hei = 100, wid = 60;	// ĳ���� ũ��
	int direction;				// �̵����� (�ִϸ��̼ǿ��� ���)

	int ground = 730;		// Stage�� �ٴ� ���� (����� y = 0, ���������� +)
	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 50;			// �ӵ�
	short Frame = 0;		// �ִϸ��̼� ������

	CImage Anim[5]{};
	int C_img_Frame{};
	int C_img_x{}, C_img_y{};
	int C_img_X_Size_01{}, C_img_Y_Size_01{};
	int C_img_X_Size_02{}, C_img_Y_Size_02{};

	bool on = TRUE;
	bool is_Jumping = FALSE;
	bool is_Push = FALSE;
	bool Down = FALSE;

	PLAYER() {

	}
	~PLAYER() {

	}
};

struct RECTANGLE {
	int x;
	int y, dic = 0;

	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 0;			// �̵� �ӵ�
	bool Down = FALSE;
};

class OBJECT {
	bool On = FALSE;			// ��� ����

public:
	int x{}, y{};				// ������ ���� �»�� (x, y) ��ġ��ǥ
	int image_x{}, image_y{};	// ����� �̹��� ������ ������ (��������Ʈ �̹���)
	int wid{}, hei{};			// ���α���, ���α���
	int MaxWid{};				// ��ü ��������Ʈ ���α���
	int imageMoveWid{};			// ��������Ʈ �̹��� �̵�

	OBJECT() {};
	OBJECT(int pos_x, int pos_y, int WID, int HEI, int MAXWID, int IMAGEMOVEWID, bool ON)
		: x(pos_x), y(pos_y), wid(WID), hei(HEI), MaxWid(MAXWID), imageMoveWid(IMAGEMOVEWID), On(ON)
	{
		image_x = 0;
		image_y = 0;
	}

	// �浹 Ȯ�� �Լ�, Player(fire boy or water girl) �Է��� �޾� this Object�� �浹 ��
	bool Collision(PLAYER& pl) {
		if  (
			(abs((x - wid / 2) - (pl.x - pl.wid / 2)) <= (wid + pl.wid) / 2)
			&& 
			(abs((y - hei / 2) - (pl.y - pl.hei / 2)) <= (hei + pl.hei) / 2)
			) {
			return true;
		}
		else return false;
	}

	void SetVisible(bool in) {
		On = in;
	}

	bool GetVisible() {
		return On;
	}

	bool ChangeFrame(int direction) {
		if (image_x + wid == MaxWid) {
			image_x = 0;
			return true;
		}
		else {
			image_x += imageMoveWid * direction;
			return false;
		}
	}
};

//client Info
struct clientInfo {
	int id;// �ٸ� Ŭ���̾�Ʈ �ĺ� ����
	short role; // � ĳ���� ����

	//��ǥ�� �ʿ� �ϰ���?
};

extern PLAYER players[3];

extern MCI_PLAY_PARMS	mciPlayParms;
extern BOOL				keybuffer[256];
extern int currneClientNum;

bool NetworkInit(HWND& hWnd, std::string input_addr);
void ProcessPacket(char* buf);
void SendPacket(void* buf);
