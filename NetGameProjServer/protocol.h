#pragma once
#include<wtypes.h>

#define S2CLoading				0
#define S2CChangeStage			1
#define S2CJewelryVisibility	2

//RolePacket ����
#define C2SSelectRole			3	// �ɸ��� ���ý� Ŭ���̾�Ʈ => ���� �� ���� ����
#define S2CSelectRole			4	// ���� => Ŭ���̾�Ʈ ���� ������ ����
#define C2SChangRole			5	// �ٸ� Ŭ���̾�Ʈ�� � ������ ���� �ִ��� �˷��ֱ� ���� ��Ŷ
#define S2CChangeRole			6	// ������ �ƴ� �ɸ��� �� ���� �ִ��� �ٸ� Ŭ���̾�Ʈ�� �˾ƾ� �ϴϱ� �ִ� ��Ŷ

//MovePacket ����
#define C2SMove					7

//type ����
#define S2CDoorVisible			12	// �������°� �˸��� ��Ŷ => �� ���̴°� �˷���
#define S2CAddPlayer			13	// �ٸ� �÷��̾� ���� �ޱ�

#define S2CStageTimePass		14	// ��� �ð� ��Ŷ
#define S2CStageTimeout			15	//Ÿ�� �ƿ�

// ĳ���� �̵����� ����
#define S2CMove_IDLE			16
#define S2CMove_JUMP			17
#define S2CMove_LEFT			18
#define S2CMove_RIGHT			19
#define S2CBTN_DOWN				20	// ��ư ������ �˷��ִ� ��ŶŸ��
#define S2CBTN_UP				21	// ��ư ������ �˷��ִ� ��ŶŸ��

#define S2CEatJewely			22	// ������ ������ �Ծ����� ���� ������ ����� �˷��ֱ� ���� ��Ŷ
#define S2CIntoDoor				23	// ������ ���� �ִϸ��̼��� ���� ��Ŷ Ÿ��

#define C2SEndout				24
#define S2CEndout				25
#define S2CPlayerOut			26

#define PORT_NUM				9000

#pragma pack(push, 1)

struct S2CPlayerPacket { // �ٸ� Ŭ���̾�Ʈ ��ٸ������� ��Ŷ  -> ���� �����͵� �̰ɷ� ����, Door ���� �͵�
	char type;
	char id; // Ŭ���̾�Ʈ ���� id ����
};

struct S2CChangeStagePacket { // ���������� �����ϱ� ���� ��Ŷ
	char type;
	short stageNum; // �������� ������ ���� ����
};

struct C2SRolePacket {
	char type;
	char role; //���� ����
};

struct S2CRolePacket {
	char type;
	char id;		// � Ŭ���̾�Ʈ���� ������ ���� ����
	char role;		// ���� ����
};

struct MovePacket { // ������ ���� ��Ŷ
	char type;
	char id;		// Ŭ���̾�Ʈ ���� ��Ŷ
	short x, y;		// ���� ��ġ
};

//�������� Ÿ�� �ƿ�

struct typePacket {
	char type;
};


//�������� ��� �ð�
struct S2CStageTimePassPacket {
	char type = S2CStageTimePass;
	int timePassed;
};



#pragma pack(pop)


//TestCommit