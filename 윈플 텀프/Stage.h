#pragma once
#include "stdafx.h"
//#include "ImageMgr.h"

class Stage
{
public:
	RECTANGLE Rt;

	int stage;
	BOOL clear;
	int average;
	BOOL time_over;
	BOOL red_door_open, blue_door_open;
	int count;
	int red_total;
	int blue_total;
	BOOL stair;

	std::unordered_map<int, OBJECT> Red_Jewel;
	std::unordered_map<int, OBJECT> Blue_Jewel;

	OBJECT Trap[90];		// 0~19���� �Ķ� ��� �� 20~29���� �Ķ� ��.�� 30~49���� ���� ��� �� 50~59���� ������ ��.�� 60~79 �ʷ� ��� 80~89 �ʷϿ�.��
	OBJECT Die;
	OBJECT blue_door;
	OBJECT red_door;
	OBJECT button[5];
	OBJECT block[5];
	FootHold Ft[20];

public:
	void Stage_1(int order);
	void Stage_2(int order);
	void Stage_3(int order);

	void Push();
	void Jump();
	void Wid_Move();
	void Foot();
};
