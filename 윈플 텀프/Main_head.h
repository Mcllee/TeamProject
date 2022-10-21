#include<windows.h>
#include <tchar.h>
#include <atlimage.h>
#include<mmsystem.h>

void Loop();
extern BOOL keybuffer[256];

void Push();
void Jump();
void Wid_Move();
void Foot();
void Climb();

struct FootHold {
	int x = 0, y = 0;
	int wid = 111, hei = 23;
	bool W_On = FALSE, F_On = FALSE;
};

struct PLAYER {
	int x;
	int y;

	int ground = 730;
	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 50;
	float wid_a = 0;
	float wid_v = 0;
	int dic = 0;

	bool on = TRUE;
	bool is_Move = FALSE;
	bool is_Speed_Down = FALSE;
	bool is_Jumping = FALSE;
	bool is_Push = FALSE;
	bool Down = FALSE;
};

struct REctangle {
	int x;
	int y, dic = 0;

	float g = 4;			// �߷� ������ ���� ���� ����
	float v = 0;
	bool Down = FALSE;
};

struct Hill {
	int x, y, wid, hei;
	int dic;				// 1 : �������� �ö󰡴� ����, -1 : �������� �ö󰡴� ����
};

struct Object {
	int image_x, image_y;
	int x, y;
	int wid = 111, hei = 23;
	bool On = FALSE;
};

extern Object Jewelry[20]; // 0~9���� �Ķ����� 10~19���� ��������
extern Object Trap[90]; // 0~19���� �Ķ� ��� �� 20~29���� �Ķ� ��.�� 30~49���� ���� ��� �� 50~59���� ������ ��.�� 60~79 �ʷ� ��� 80~89 �ʷϿ�.��
extern Object Die;
extern Object blue_door;
extern Object red_door;
extern Object button[5];
extern Object block[5];

extern FootHold Ft[20];
extern PLAYER water;
extern PLAYER fire;

extern REctangle Rt;
extern Hill hill;



void Stage_1(int );
void Stage_2(int);
void Stage_3(int);
void Stage_4(int);
void Stage_5(int);
void Stage_6(int);