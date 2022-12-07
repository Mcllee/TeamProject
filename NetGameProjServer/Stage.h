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
	short stage;						// ���� ��������
	bool clear;							// Stage Ŭ���� ����
	int average;
	bool time_over;						// ���� Stage���� Timer Over ����
	int count;							// �ִϸ��̼� ������ ��ȣ
	int red_total;						// ���� ���� �� ����
	int blue_total;						// �Ķ� ���� �� ����
	bool stair;							// Fire boy�� Water girl �� �� �� ����� �ö�

	OBJECT Ground{ WINDOW_WID / 2, WINDOW_HEI, WINDOW_WID, WINDOW_HEI - GROUND_POS_Y, 0, 0, true };
	
	std::queue<OBJECT> jewely;
	std::vector<OBJECT> Trap;
	std::vector<OBJECT> Ft;	

	OBJECT Die;		
	OBJECT door;	
	OBJECT currentVisibleJewely;

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
