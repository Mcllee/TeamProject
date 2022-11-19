#pragma once
#include "stdafx.h"
//#include "ImageMgr.h"

class Stage
{
public:
	RECTANGLE Rt;

	short stage;						// ���� ��������
	BOOL clear;							// Stage Ŭ���� ����
	int average;						
	BOOL time_over;						// ���� Stage���� Timer Over ����
	int count;							// �ִϸ��̼� ������ ��ȣ
	int red_total;						// ���� ���� �� ����
	int blue_total;						// �Ķ� ���� �� ����
	BOOL stair;							// Fire boy�� Water girl �� �� �� ����� �ö�

	// 	OBJECT(int pos_x, int pos_y, int WID, int HEI, int MAXWID, int IMAGEMOVEWID, bool ON)
	OBJECT Ground{0, GROUND_POS_Y, WINDOW_WID, WINDOW_HEI - GROUND_POS_Y, 0, 0, TRUE};
	std::vector<OBJECT> Red_Jewel;
	std::vector<OBJECT> Blue_Jewel;
	std::vector<OBJECT> Trap;
	std::vector<OBJECT> Ft;			// ���� ������Ʈ

	// OBJECT Trap[90];		
	OBJECT Die;				// ����� ������ ���� (Max x = 7950, move x = 159)
	OBJECT blue_door;		// (Max x = 1260, move x = 60) // Max = 1296, Move = 54
	OBJECT red_door;		// (Max x = 1260, move x = 60) // Max = 1250, Move = 50
	OBJECT button[5];		// ��� ��ư(block1.PNG ����)	(Down BTN Max y = 7, move y = 1) else (Up BTN Max y = 15, move y = 1)
	OBJECT block[5];		// (Max x = 40, move x = 2)

public:
	void title() {}
	void lobby() {}
	void Loading();
	void SelectCharacter();
	void Stage_1();
	void Stage_2();
	void Stage_3();

	void Push();			// ĳ���Ͱ� "�ڽ� ������Ʈ" �б� �Լ� (Fire boy�� Water girl�� ���ÿ� ���ʿ��� �� ��� ó��)
	void Jump();			// ĳ���� ����
	void Foot();			// ĳ���Ͱ� ���ǿ� �ö��� ��, �浹ó��
};

extern Stage currentStage;
