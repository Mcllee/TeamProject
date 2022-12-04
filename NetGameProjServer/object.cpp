#include"object.h"
#include"ThreadInfo.h"
// �浹 Ȯ�� �Լ�, Player(fire boy or water girl) �Է��� �޾� this Object�� �浹 ��
bool OBJECT::Collision(ThreadInfo& pl) {
	/*if ((abs(x - pl.x) <= (wid + pl.wid) / 2) && (abs(y - pl.y) <= (hei + pl.hei) / 2)) {
		return true;
	}*/
	if (pl.x  > x - wid / 2  && pl.x - 60 < x + wid / 2) { // ���� �ȿ� �ְ�
		if (pl.y - 60 < y && pl.y > y) // �Ӹ��� �ؿ� �������
			return true;
	}
	return false;
}

bool OBJECT::Ft_Collision(ThreadInfo& pl) {
	/*if ((abs(x - pl.x) <= (wid + pl.wid) / 2) && ((y - pl.y) < ((hei + pl.hei) / 3.0f))) {
		return true;
	}*/
	if (pl.x > x - wid / 2 && pl.x - 60 < x + wid / 2) {// ���� �ȿ� �ְ�
		if (pl.y - 60 < y - hei && pl.y > y - hei) // �ٸ��� ���� �������
			return true;
	}
	return false;
}

bool OBJECT::FT_Collide_Fall(ThreadInfo& pl) {
	if (pl.x < x - wid / 2 || pl.x - 60 > x + wid / 2) {
		return true;
	}
	return false;
}

bool OBJECT::OBJECT_Collide(ThreadInfo& pl)
{
	if (pl.x - 60 > x - wid / 2 && pl.x - 60 < x + wid / 2) { // ���� �ȿ� �ְ�
		if (pl.y < y && pl.y > y - hei) 
			return true;
		if (pl.y - 60 < y && pl.y - 60 > y - hei)
			return true;
	}
	if (pl.x > x - wid / 2 && pl.x < x + wid / 2) {
		if (pl.y < y && pl.y > y - hei)
			return true;
		if (pl.y - 60 < y && pl.y - 60 > y - hei)
			return true;
	}
	if (x - wid / 2 > pl.x - 60 && x - wid / 2 < pl.x) {
		if (pl.y - 60< y && pl.y > y)
			return true;
		if (pl.y - 60 < y - hei && pl.y > y - hei)
			return true;
	}
	if (x + wid / 2 > pl.x - 60 && x + wid / 2 < pl.x) {
		if (pl.y - 60 < y && pl.y > y)
			return true;
		if (pl.y - 60 < y - hei && pl.y > y - hei)
			return true;
	}

	return false;
}