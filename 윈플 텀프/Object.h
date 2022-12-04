#pragma once
#include<wtypes.h>
#include"Player.h"
class OBJECT
{
	bool On = FALSE;			// ��� ����

public:
	int x{}, y{};				// ������ ���� �»�� (x, y) ��ġ��ǥ
	int image_x{}, image_y{};	// ����� �̹��� ������ ������ (��������Ʈ �̹���)
	int wid{}, hei{};			// ���α���, ���α���
	int MaxWid{};				// ��ü ��������Ʈ ���α���
	int imageMoveWid{};			// ��������Ʈ �̹��� �̵�

	OBJECT() {};
	OBJECT(int pos_x, int pos_y, int WID, int HEI, int MAXWID, int IMAGEMOVEWID, bool ON)
		: x(pos_x), y(pos_y), wid(WID), hei(HEI), MaxWid(MAXWID), imageMoveWid(IMAGEMOVEWID), On(ON) {}

	// �浹 Ȯ�� �Լ�, Player(fire boy or water girl) �Է��� �޾� this Object�� �浹 ��
	bool Collision(PLAYER& pl) {
		if (
			(abs((x - wid / 2) - (pl.x - pl.wid / 2)) <= (wid + pl.wid) / 2)
			&&
			(abs((y - hei / 2) - (pl.y - pl.hei / 2)) <= (hei + pl.hei) / 2)
			) {
			return true;
		}
		else return false;
	}

	bool Ft_Collision(PLAYER& pl) {
		if (
			(abs((x - wid / 2) - (pl.x - pl.wid / 2)) < (wid + pl.wid) / 2)
			&&
			(abs((y - hei / 2) - (pl.y - pl.hei / 2)) < (hei + pl.hei) / 2)
			) {
			return true;
		}
		else return false;
	}

	void SetVisible(bool in) {
		On = in;
	}

	bool GetVisible() {
		return On;
	}

	bool ChangeFrame(int direction, bool replay) {
		if (MaxWid == image_x + imageMoveWid) {
			if (replay)
				image_x = 0;
			return true;
		}
		else {
			image_x += (imageMoveWid * direction);
			return false;
		}
	}
};

