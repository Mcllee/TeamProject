#pragma once
#include "stdafx.h"
#include "Stage.h"

void Stage::Stage_1() {
	threadHandles[0].x = 600;
	threadHandles[0].y = 730;

	threadHandles[1].x = 700;
	threadHandles[1].y = 730;

	threadHandles[2].x = 500;
	threadHandles[2].y = 730;

	Die.SetVisible(false);

	//��ö ����
	//jewely queeue Clear
	for (int i = 0; i < jewely.size(); i++)
		jewely.pop();

	Trap.reserve(3);

	for (auto& t : Trap) {
		t = OBJECT{ 0, 0, 20, 20, 230, 23, FALSE };
	}

	//��ö ����
	//queue�ϱ� �ϴ� ù��° ������ current ���� �ְ�
	currentVisibleJewely = OBJECT{ 300, 450, 28, 25, 1160, 29, TRUE };
	//jewely.emplace(OBJECT{ 300, 450, 28, 25, 1160, 29, TRUE });
	//���� �Ⱥ����� ������ ť�� ����
	jewely.emplace(OBJECT{ 900, 450, 28, 25, 1160, 29, FALSE });

	//���� �ִ� ���� �����ְ�
	maxJewelyNum = 2;

	/*jewely.emplace_back();
	jewely.emplace_back();*/

	door = OBJECT{ 700, 740, 60, 100, 0, 0, TRUE };
	//red_door = OBJECT{ 630, 400, 60, 100, 1260, 60, TRUE };

	Ft.push_back(Ground);
	Ft.emplace_back(OBJECT{ 100, 630, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 300, 550, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 600, 450, 224, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 900, 550, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 1100, 630, 112, 24, 0, 0, TRUE });

}
void Stage::Stage_2() {
	for (int i = 0; i < jewely.size(); i++)
		jewely.pop();
	Ft.clear();
	//door = OBJECT{ 700, 630, 60, 100, 0, 0, TRUE };
	maxJewelyNum = 8;

	threadHandles[0].x = 600;
	threadHandles[0].y = 730;

	threadHandles[1].x = 700;
	threadHandles[1].y = 730;

	threadHandles[2].x = 500;
	threadHandles[2].y = 730;
	door = OBJECT{ 700, 740, 60, 100, 0, 0, TRUE };

	Ft.push_back(Ground);
	Ft.emplace_back(OBJECT{ 100, 500, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 400, 600, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 380, 400, 224, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 700, 600, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 1000, 500, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 150, 300, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 400, 250, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 700, 250, 112, 24, 0, 0, TRUE });
	Ft.emplace_back(OBJECT{ 950, 300, 112, 24, 0, 0, TRUE });

	currentVisibleJewely = OBJECT{ 450, 550, 28, 25, 1160, 29, TRUE };
	//���� �Ⱥ����� ������ ť�� ����
	jewely.emplace(OBJECT{ 150, 450, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 750, 350, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 1000, 250, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 750, 200, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 750, 550, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 1050, 450, 28, 25, 1160, 29, FALSE });
	jewely.emplace(OBJECT{ 450, 350, 28, 25, 1160, 29, FALSE });

	//���� �ִ� ���� �����ְ�
	//maxJewelyNum = 8;

	/*
	Trap[0].x = 200;
	Trap[0].y = 730;

	Trap[20].x = Trap[0].x - 20;
	Trap[20].y = 730;

	Trap[25].x = Trap[0].x + 20;
	Trap[25].y = 730;

	Trap[30].x = 900;
	Trap[30].y = 730;

	Trap[50].x = Trap[30].x - 20;
	Trap[50].y = 730;

	Trap[55].x = Trap[30].x + 20;
	Trap[55].y = 730;

	Trap[60].x = 600;
	Trap[60].y = 730;

	Trap[80].x = Trap[60].x - 20;
	Trap[80].y = 730;

	Trap[85].x = Trap[60].x + 20;
	Trap[85].y = 730;
	*/
}

void Stage::Stage_3() {
	{
		//	water.x = 100;
		//	water.y = 730;
		//	fire.x = 1100;
		//	fire.y = 730;

		//	fire.on = TRUE;
		//	water.on = TRUE;

		//	{
		//		Die.On = FALSE;
		//		Die.On = FALSE;
		//		for (int i = 0; i < 20; i++)
		//		{
		//			Jewelry[i].On = FALSE;
		//			Jewelry[i].image_x = 0;
		//			Jewelry[i].image_y = 0;
		//			Jewelry[i].x = 0;
		//			Jewelry[i].y = 0;
		//			Jewelry[i].wid = 50;
		//			Jewelry[i].hei = 50;
		//		}

		//		for (int i = 0; i < 90; i++)
		//		{
		//			Trap[i].On = FALSE;
		//			Trap[i].image_x = 0;
		//			Trap[i].image_y = 0;
		//			Trap[i].x = 0;
		//			Trap[i].y = 0;
		//			Trap[i].wid = 20;
		//			Trap[i].hei = 20;
		//		}

		//		for (int i = 0; i < 20; i++)
		//		{
		//			Ft[i].x = 0;
		//			Ft[i].y = 0;
		//		}

		//		blue_door.image_x = 0;
		//		blue_door.image_y = 0;
		//		blue_door.x = 0;
		//		blue_door.y = 0;

		//		red_door.image_x = 0;
		//		red_door.image_y = 0;
		//		red_door.x = 0;
		//		red_door.y = 0;

		//		Jewelry[0].On = TRUE;
		//		Jewelry[0].x = 450;
		//		Jewelry[0].y = 550;

		//		Jewelry[1].On = TRUE;
		//		Jewelry[1].x = 150;
		//		Jewelry[1].y = 450;

		//		Jewelry[2].On = TRUE;
		//		Jewelry[2].x = 750;
		//		Jewelry[2].y = 350;

		//		Jewelry[3].On = TRUE;
		//		Jewelry[3].x = 1000;
		//		Jewelry[3].y = 250;

		//		Jewelry[4].On = TRUE;
		//		Jewelry[4].x = 750;
		//		Jewelry[4].y = 200;

		//		Jewelry[10].On = TRUE;
		//		Jewelry[10].x = 750;
		//		Jewelry[10].y = 550;

		//		Jewelry[11].On = TRUE;
		//		Jewelry[11].x = 1050;
		//		Jewelry[11].y = 450;

		//		Jewelry[12].On = TRUE;
		//		Jewelry[12].x = 450;
		//		Jewelry[12].y = 350;

		//		Jewelry[13].On = TRUE;
		//		Jewelry[13].x = 200;
		//		Jewelry[13].y = 250;

		//		Jewelry[14].On = TRUE;
		//		Jewelry[14].x = 450;
		//		Jewelry[14].y = 200;
		//		// 0~19���� �Ķ� ��� 20~24 �Ķ��� 25~29�Ķ��� 30~49 ���� ��� 50~54~������ 55~59������ 60~79�ʷ� ��� 80~84�ʷϿ� 85~89�ʷϿ�
		//		Trap[31].On = TRUE;
		//		Trap[31].x = 200;
		//		Trap[31].y = 730;

		//		Trap[51].On = TRUE;
		//		Trap[51].x = Trap[31].x - 20;
		//		Trap[51].y = 730;

		//		Trap[56].On = TRUE;
		//		Trap[56].x = Trap[31].x + 20;
		//		Trap[56].y = 730;

		//		Trap[30].On = TRUE;
		//		Trap[30].x = 900;
		//		Trap[30].y = 730;

		//		Trap[50].On = TRUE;
		//		Trap[50].x = Trap[30].x - 20;
		//		Trap[50].y = 730;

		//		Trap[55].On = TRUE;
		//		Trap[55].x = Trap[30].x + 20;
		//		Trap[55].y = 730;

		//		Trap[60].On = TRUE;
		//		Trap[60].x = 600;
		//		Trap[60].y = 730;

		//		Trap[80].On = TRUE;
		//		Trap[80].x = Trap[60].x - 20;
		//		Trap[80].y = 730;

		//		Trap[85].On = TRUE;
		//		Trap[85].x = Trap[60].x + 20;
		//		Trap[85].y = 730;

		//		Ft[0].x = 150, Ft[0].y = 200;
		//		Ft[1].x = 100, Ft[1].y = 600;

		//		Ft[2].x = 380, Ft[2].y = 400, Ft[2].wid = 450;

		//		Ft[3].x = 700, Ft[3].y = 600;
		//		Ft[4].x = 1000, Ft[4].y = 500;
		//		// 1�� 
		//		Ft[5].x = 150, Ft[5].y = 300;
		//		Ft[6].x = 400, Ft[6].y = 250;

		//		Ft[7].x = 700, Ft[7].y = 250;
		//		Ft[8].x = 950, Ft[8].y = 300;

		//		Ft[9].x = 900, Ft[9].y = 200;

		//		blue_door.On = FALSE;
		//		blue_door.image_x = 0;
		//		blue_door.image_y = 0;
		//		blue_door.x = 950;
		//		blue_door.y = 0;

		//		red_door.On = FALSE;
		//		red_door.image_x = 0;
		//		red_door.image_y = 0;
		//		red_door.x = 200;
		//		red_door.y = 0;

		//		block[0].On = FALSE;
		//		block[0].x = 0;
		//		block[0].y = 600;
		//		block[0].image_x = 0;
		//		block[0].image_y = 0;

		//		button[0].On = FALSE;
		//		button[0].x = 600;
		//		button[0].y = 730;
		//		button[0].image_x = 42;
		//		button[0].image_y = 15;

		//		Rt.x = 800;
		//		Rt.y = 730;
		//	}
		//}
	}
}
