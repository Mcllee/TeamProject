#pragma once
#include "MapMgr.h"

RECTANGLE Rt;

BOOL playsound;
int stage;
BOOL clear;
int average;
BOOL time_over;
BOOL red_door_open, blue_door_open;
int count;
int red_total;
int blue_total;
BOOL stair;

OBJECT Jewelry[20];	// 0~9���� �Ķ����� 10~19���� ��������
OBJECT Trap[90];	// 0~19���� �Ķ� ��� �� 20~29���� �Ķ� ��.�� 30~49���� ���� ��� �� 50~59���� ������ ��.�� 60~79 �ʷ� ��� 80~89 �ʷϿ�.��
OBJECT Die;
OBJECT blue_door;
OBJECT red_door;
OBJECT button[5];
OBJECT block[5];
FootHold Ft[20];
