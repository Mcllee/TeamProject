#include "StageMgr.h"
#include"Stage.h"

StageMgr::StageMgr()
{
	myStage[0].lobby();// start lobby ��������
	myStage[0].stage = 0;

	myStage[1].Loading();// �ε� ��������
	myStage[1].stage = 1;

	myStage[2].Stage_1();//ĳ���� ���� ��������
	myStage[2].stage = 2;

	myStage[3].Stage_1();
	myStage[3].stage = 2;

	myStage[4].Stage_2();
	myStage[4].stage = 3;

	myStage[5].Stage_3();
	myStage[5].stage = 4;

	isUse[0] = true;
	isUse[1] = true;
	isUse[2] = true;// ���� ������ �κи�
	isUse[3] = true;
	isUse[4] = false;
	isUse[5] = false;
}

Stage& StageMgr::getStage(int index)
{
	if (isUse[index])
		return myStage[index];
	else myStage[0];
	// TODO: ���⿡ return ���� �����մϴ�.
}

