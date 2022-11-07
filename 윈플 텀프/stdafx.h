#pragma once
#include <windows.h>
#include <tchar.h>
#include <atlimage.h>
#include <mmsystem.h>
#include <unordered_map>
#include <array>

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
	int x, y;					// ���ϴ� ��ǥ
	int hei = 100, wid = 60;	// ĳ���� ũ��

	int ground = 730;		// Stage�� �ٴ� ���� (����� y = 0, ���������� +)
	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 50;			// �ӵ�
	float wid_a = 0;		// �¿� ���ӵ�
	float wid_v = 0;		// �¿� �ӵ�
	int dic = 0;			// �̵� ����
	short Frame = 0;		// �ִϸ��̼� ������

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
	bool On = FALSE;			// ��� ����

public:
	int image_x{}, image_y{};	// �̹��� ������ ������ (��������Ʈ �̹���)
	int x{}, y{};				// ������ ���� �»�� (x, y) ��ǥ
	int wid{}, hei{};			// ���α���, ���α���

	OBJECT() {};
	OBJECT(int pos_x, int pos_y, int WID, int HEI, bool ON) : x(pos_x), y(pos_y), wid(WID), hei(HEI), On(ON)
	{
		this->image_x = 0;
		this->image_y = 0;
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
};

//client Info
struct clientInfo {
	int id;// �ٸ� Ŭ���̾�Ʈ �ĺ� ����
	short role; // � ĳ���� ����

	//��ǥ�� �ʿ� �ϰ���?
};

extern PLAYER water;
extern PLAYER fire;

extern MCI_PLAY_PARMS	mciPlayParms;
extern BOOL				keybuffer[256];
extern int currneClientNum;