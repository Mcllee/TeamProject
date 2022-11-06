#pragma once
#include "stdafx.h"
#include"Stage.h"

#define MAX_STAGE 5

class StageMgr
{
	//���� ��������
	//1. start��ư ��������
	//2. �ε� ��������
	//3. ��������1
	//4. ��������2
	//5. ��������3

	//�� 5����
	Stage myStage[MAX_STAGE];
public:
	StageMgr();
	Stage& getStage(int index);

private:
	bool isUse[MAX_STAGE] = { false };
};
