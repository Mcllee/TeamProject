#pragma once
#include "stdafx.h"
//#include "ImageMgr.h"

class Stage
{
public:
	RECTANGLE Rt;

	int stage;							// ���� ��������
	BOOL clear;							// Stage Ŭ���� ����
	int average;						
	BOOL time_over;						// ���� Stage���� Timer Over ����
	BOOL red_door_open, blue_door_open;	// Stage���� �� ���� ����
	int count;							// �ִϸ��̼� ������ ��ȣ
	int red_total;						// ���� ���� �� ����
	int blue_total;						// �Ķ� ���� �� ����
	BOOL stair;							// Fire boy�� Water girl �� �� �� ����� �ö�

	std::vector<OBJECT> Red_Jewel;
	std::vector<OBJECT> Blue_Jewel;
	std::vector<OBJECT> Trap;

	// OBJECT Trap[90];		// �칰 ���� �ִϸ��̼�(�����ʿ�) 0~19���� �Ķ� ��� �� 20~29���� �Ķ� ��.�� 30~49���� ���� ��� �� 50~59���� ������ ��.�� 60~79 �ʷ� ��� 80~89 �ʷϿ�.��
	OBJECT Die;				// ����� ������ ����
	OBJECT blue_door;
	OBJECT red_door;
	OBJECT button[5];		// ��� ��ư(block1.PNG ����)
	OBJECT block[5];		// 
	FootHold Ft[20];		// ���� ������Ʈ

public:
	void lobby () {}
	void Loading();
	void SelectCharacter();
	void Stage_1();
	void Stage_2();
	void Stage_3();

	void Push();			// ĳ���Ͱ� "�ڽ� ������Ʈ" �б� �Լ� (Fire boy�� Water girl�� ���ÿ� ���ʿ��� �� ��� ó��)
	void Jump();			// ĳ���� ����
	void Wid_Move();		// ĳ���� �¿� �̵�
	void Foot();			// ĳ���Ͱ� ���ǿ� �ö��� ��, �浹ó��
};
