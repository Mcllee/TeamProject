#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include "object.h"

#define WINDOW_WID			1200
#define WINDOW_HEI			800
#define GROUND_POS_Y		730

class PLAYER {
public:
	int id;						// �ٸ� Ŭ���̾�Ʈ �ĺ� ���� - -1 // ���� �Ⱦ��� ��Ȳ�� -1
	short role;					// � ĳ���� ���� - f w e => fire water earth
	int x, y;					// ���ϴ� ��ǥ
	int hei = 100, wid = 60;	// ĳ���� ũ��

	int direction;				// �̵����� (�ִϸ��̼ǿ��� ���)
	float wid_v{};
	float wid_a{};

	int ground = 730;		// Stage�� �ٴ� ���� (����� y = 0, ���������� +)
	float g = 3.f;			// �߷� ������ ���� ���� ����
	float v = 0;			// �ӵ�
	short Frame = 0;		// �ִϸ��̼� ������

	int C_img_Frame{};
	int C_img_x{}, C_img_y{};
	int C_img_X_Size_01{}, C_img_Y_Size_01{};
	int C_img_X_Size_02{}, C_img_Y_Size_02{};

	bool on = true;
	bool is_Jumping = true;
	bool is_Push = true;
	bool Down = true;

	PLAYER() : id(-1), role('f') {}
	~PLAYER() {

	}
};

class Stage
{
public:
	// RECTANGLE Rt;

	short stage;						// ���� ��������
	bool clear;							// Stage Ŭ���� ����
	int average;
	bool time_over;						// ���� Stage���� Timer Over ����
	int count;							// �ִϸ��̼� ������ ��ȣ
	int red_total;						// ���� ���� �� ����
	int blue_total;						// �Ķ� ���� �� ����
	bool stair;							// Fire boy�� Water girl �� �� �� ����� �ö�

	OBJECT Ground{ WINDOW_WID / 2, WINDOW_HEI, WINDOW_WID, WINDOW_HEI - GROUND_POS_Y, 0, 0, true };
	
	// ��ö ����
	// ������ �ϳ��� ������ ��������
	std::queue<OBJECT> jewely;
		
	std::vector<OBJECT> Trap;
	std::vector<OBJECT> Ft;			// ���� ������Ʈ

	// OBJECT Trap[90];
	OBJECT Die;				// ����� ������ ���� (Max x = 7950, move x = 159)
	OBJECT door;		// (Max x = 1260, move x = 60) // Max = 1296, Move = 54
	//OBJECT red_door;		// (Max x = 1260, move x = 60) // Max = 1250, Move = 50
	OBJECT button[5];		// ��� ��ư(block1.PNG ����)	(Down BTN Max y = 7, move y = 1) else (Up BTN Max y = 15, move y = 1)
	OBJECT block[5];		// (Max x = 40, move x = 2)
	OBJECT currentVisibleJewely;

	//��ö ����	
	// �� ���������� �ִ� ���� ����
	int maxJewelyNum = 0;

public:
	void title() {}
	void lobby() {}
	void getStage(int index)
	{
		switch (index)
		{
		case STAGE_01:
			Stage_1();
			break;
		case STAGE_02:
			Stage_2();
			break;
		case STAGE_03:
			Stage_3();
			break;
		default:
			break;
		}
	}
private:
	void Stage_1();
	void Stage_2();
	void Stage_3();
};

extern Stage currentStage;

/*
// Stage 03�� ������ �ڽ��� ���ʿ��� �о��� �� ó��
void Push() {
	//if (water.is_Push == FALSE && fire.is_Push == FALSE) {
	//	if (water.y == Rt.y && abs(water.x - Rt.x) <= 60) {			// �Ұ� ����
	//		water.is_Push = TRUE;
	//	}
	//	if (fire.y == Rt.y && abs(fire.x - Rt.x) <= 60) {		// ���� ����
	//		fire.is_Push = TRUE;
	//	}
	//}
	//// �浹 üũ
	//if (water.is_Push == TRUE && water.y == Rt.y && abs(water.x - Rt.x) <= 60) {
	//	if (Rt.dic == 0) {
	//		Rt.dic = water.dic;
	//	}

	//	if (Rt.dic == water.dic) {
	//		if (Rt.dic == 1) {
	//			Rt.x = water.x + 60;
	//		}
	//		else if (Rt.dic == -1) {
	//			Rt.x = water.x - 60;
	//		}
	//	}
	//}
	//else if (water.is_Push == TRUE && Rt.dic != water.dic) {
	//	Rt.dic = 0;
	//	water.is_Push = FALSE;
	//	return;
	//}

	//if (fire.is_Push == TRUE && fire.y == Rt.y && abs(fire.x - Rt.x) <= 60) {
	//	if (Rt.dic == 0) {
	//		Rt.dic = fire.dic;
	//	}

	//	if (Rt.dic == fire.dic) {
	//		if (Rt.dic == 1) {
	//			Rt.x = fire.x + 60;
	//		}
	//		else if (Rt.dic == -1) {
	//			Rt.x = fire.x - 60;
	//		}
	//	}
	//}
	//else if (fire.is_Push == TRUE && Rt.dic != fire.dic) {
	//	Rt.dic = 0;
	//	fire.is_Push = FALSE;
	//	return;
	//}

	//for (int i = 0; i < 20 && Ft[i].x != NULL; ++i) {
	//	if ((Rt.y == Ft[i].y && Ft[i].x > Rt.x - 60) || (Rt.y == Ft[i].y && Ft[i].x + Ft[i].wid < Rt.x)) {
	//		Rt.Down = TRUE;
	//	}
	//}
	//if (Rt.Down) {
	//	if (Rt.y + (Rt.v + Rt.g) >= 730) {
	//		Rt.v = 0;
	//		Rt.y = 730;
	//		Rt.Down = FALSE;
	//		return;
	//	}
	//	if (Rt.y <= 730) {
	//		Rt.v = Rt.v + Rt.g;
	//		Rt.y = Rt.y + Rt.v;
	//		return;
	//	}
	//}
}

*/