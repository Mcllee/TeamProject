#pragma once
#include<wtypes.h>

#define S2CLoading 0
#define S2CChangeStage 1
#define C2SSelectRole 2
#define S2CSelectRole 3
#define S2CChangeRole 4
#define C2SMove 5
#define S2CMove 6
#define C2SExitGame 7
#define S2CExitGame 8
#define C2SRetry 9
#define S2CResetStage 10
#define S2CJewelryVisibility 11
#define S2CDoorOpen 12

#pragma pack(push, 1)

struct S2CLoadingPacket { // �ٸ� Ŭ���̾�Ʈ ��ٸ������� ��Ŷ
	unsigned char size;
	char type;
	char id; // Ŭ���̾�Ʈ ���� id ����
};

struct S2CChangeStagePacket { // ���������� �����ϱ� ���� ��Ŷ
	unsigned char size;
	char type;
	short stageNum; // �������� ������ ���� ����
};

struct C2SSelectRolePacket { // �ɸ��� ���ý� Ŭ���̾�Ʈ => ���� �� ���� ����
	unsigned char size;
	char type;
	//char id; // � Ŭ���̾�Ʈ���� ���� => ���������� socket�� ���� �� �� �ֳ�??
	char role; // ���� ����
};

struct S2CSelectRolePacket { // ���� => Ŭ���̾�Ʈ ���� ������ ����
	unsigned char size;
	char type;
	char id; // � Ŭ���̾�Ʈ���� ������ ���� ����
	char role; // ���� ����
};

struct C2SChangeRolePacket { // ������ �ƴ� �ɸ��� �� ���� �ִ��� �ٸ� Ŭ���̾�Ʈ�� �˾ƾ� �ϴϱ� �ִ� ��Ŷ
	unsigned char size;
	char type;
	char role; //���� ����
};

struct S2CChangeRolePacket { // �ٸ� Ŭ���̾�Ʈ�� � ������ ���� �ִ��� �˷��ֱ� ���� ��Ŷ
	unsigned char size;
	char type;
	char id; // Ŭ���̾�Ʈ ������ ���� ��Ŷ
	char role; // ���� ����
};

struct C2SMovePacket { // ������ ���� ��Ŷ
	unsigned char size;
	char type;
	char id; // Ŭ���̾�Ʈ ���� ��Ŷ
	float x, y; // ���� ��ġ
};

struct S2CMovePacket { //������ ���� ��Ŷ
	unsigned char size;
	char type;
	char id; // Ŭ���̾�Ʈ ���� ��Ŷ
	float x, y; // ���� ��ġ
};

struct C2SExitGamepacket { // Ŭ���̾�Ʈ�� ���� ���Ḧ ���� ��, ����
	unsigned char size;
	char type;	
};

struct S2CExitGamepacket { // �������� �ٸ� Ŭ���̾�Ʈ���� ���� �˸�
	unsigned char size;
	char type;
};

struct C2SRetryPacket { // Ŭ���̾�Ʈ�� �������� �̹� �������� ��õ� ��û ��Ŷ
	unsigned char size;
	char type;
};

struct S2CResetStagePacket { // Ŭ���̾�Ʈ���� �������� ���� �����϶�� ��Ŷ
	unsigned char size;
	char type;
	short stageNum;
};

struct S2CJewelryVisibilityPacket { // �������� ������ �Ծ��ٰ� �Ǵ� ��, Ŭ���̾�Ʈ���� ������ ����
	unsigned char size;
	char type;
	char jewelryType; // � ������ ��������
	int index; // ���° �ε����� ����� ��������
};

struct S2CDoorOpenPacket { // �������°� �˸��� ��Ŷ
	unsigned char size;
	char type;
	char RoleType;// � Ÿ���� ���� ������	
};

#pragma pack(pop)
 