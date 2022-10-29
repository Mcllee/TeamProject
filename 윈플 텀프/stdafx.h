#pragma once
#include <windows.h>
#include <tchar.h>
#include <atlimage.h>
#include <mmsystem.h>
#include <unordered_map>

#pragma comment(lib,"winmm.lib")
#pragma comment (lib, "msimg32.lib")

#define IDC_BUTTON1 100
#define IDC_BUTTON2 200
#define IDC_BUTTON3 300
#define IDC_BUTTON4 350

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
void LoadSound(HWND hWnd);

void Loop(bool keyDown);



struct FootHold {
	int x = 0, y = 0;
	int wid = 111, hei = 23;
	bool W_On = FALSE, F_On = FALSE;
};

class PLAYER {
public:
	int x, y;		// �»�� ��ǥ
	int hei, wid;	// �̹��� ũ��

	int ground = 730;
	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 50;
	float wid_a = 0;
	float wid_v = 0;
	int dic = 0;
	short Frame = 0;

	CImage Anim[5]{};
	int C_img_Frame{};
	int C_img_x{}, C_img_y{};
	int C_img_X_Size_01{}, C_img_Y_Size_01{};
	int C_img_X_Size_02{}, C_img_Y_Size_02{};

	bool on = TRUE;
	bool is_Move = FALSE;
	bool is_Speed_Down = FALSE;
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

public:
	int image_x{}, image_y{};	// �̹��� 
	int x{}, y{};				// ������ ���� �»�� (x, y) ��ǥ
	int wid{}, hei{};			// ���α���, ���α���
	bool On = FALSE;			// ��� ����

	OBJECT() {};
	OBJECT(int pos_x, int pos_y, int WID, int HEI, bool ON) : x(pos_x), y(pos_y), wid(WID), hei(HEI), On(ON)
	{
		image_x = 0;
		image_y = 0;
		On = FALSE;
	}

	// �浹 Ȯ�� �Լ�, Player(fire boy or water girl) �Է��� �޾� this Object�� �浹 ��
	bool Collision(PLAYER* pl) {
		if (x <= pl->x && (pl->x + pl->wid) <= x + wid && (pl->y - pl->hei) - x <= 0.1f) {
			pl->y = y - pl->hei;
			return true;
		}
		if (x <= pl->x && (pl->x + pl->wid) <= x + wid && pl->y - (y + hei) < 0.1f) {
			pl->Down;
			return true;
		}
		return false;
	}
};

extern PLAYER water;
extern PLAYER fire;

extern MCI_PLAY_PARMS	mciPlayParms;
extern BOOL				keybuffer[256];