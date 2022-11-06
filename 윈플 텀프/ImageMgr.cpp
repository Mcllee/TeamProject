#pragma once
#include "Stage.h"
#include"ImageMgr.h"

// PNG���� �о����
void ImageMgr::LoadImages() {
	robby.Load(L"Resource\\�κ� �̹��� �ʾ� 2.png");
	buttonimg.Load(L"Resource\\�÷��� ��ư 158.60.png");
	stage1.Load(L"Resource\\�� �⺻.png");
	Jewelry_blue.Load(L"Resource\\�Ķ� ���� 28.24.png");
	Jewelry_red.Load(L"Resource\\���� ���� 29.24.png");
	red_water_center.Load(L"Resource\\���� ����� 21.14.png");
	red_water_left.Load(L"Resource\\���� ���ʹ� 24.25.png");
	red_water_right.Load(L"Resource\\���� �����ʹ� 24.25.png");
	blue_water_center.Load(L"Resource\\�Ķ� ����� 23.14.png");
	blue_water_left.Load(L"Resource\\�Ķ� ���ʹ� 23.23.png");
	blue_water_right.Load(L"Resource\\�Ķ� �����ʹ� 23.23.png");
	green_water_center.Load(L"Resource\\�ʷ� ����� 23.14.png");
	green_water_left.Load(L"Resource\\�ʷ� ���ʹ� 24.25.png");
	green_water_right.Load(L"Resource\\�ʷ� ������ 24.25.png");
	die.Load(L"Resource\\�׾��� �� 159.89.png");
	endimg.Load(L"Resource\\end.png");
	retryimg.Load(L"Resource\\retry.png");
	backimg.Load(L"Resource\\dieimg.png");
	door_red.Load(L"Resource\\���� �� 60.104.png");
	door_blue.Load(L"Resource\\�Ķ� �� 60.104.png");
	button_img.Load(L"Resource\\��ư 42.16.png");
	red_stair.Load(L"Resource\\���� ��� 50.73.png");
	blue_stair.Load(L"Resource\\�Ķ� ��� 54.77.png");
	clear_img.Load(L"Resource\\Ŭ����.png");
	zero.Load(L"Resource\\0.png");
	one.Load(L"Resource\\1.png");
	two.Load(L"Resource\\2.png");
	three.Load(L"Resource\\3.png");
	four.Load(L"Resource\\4.png");
	five.Load(L"Resource\\5.png");
	six.Load(L"Resource\\6.png");
	seven.Load(L"Resource\\7.png");
	eight.Load(L"Resource\\8.png");
	nine.Load(L"Resource\\9.png");
	clock.Load(L"Resource\\�ð�.png");
	timeout.Load(L"Resource\\Ÿ�Ӿƿ�.png");
	fraction.Load(L"Resource\\fraction.png");

	fire.Anim[0].Load(L"Resource\\���� ���� 215.411.png");       // ����
	fire.Anim[1].Load(L"Resource\\���� ���� 215.411.png");       // ���
	fire.Anim[2].Load(L"Resource\\���� ������ 342.271.png");	 // ����
	fire.Anim[3].Load(L"Resource\\���� �ϰ� 215.411.png");       // �ϴ�
	fire.Anim[4].Load(L"Resource\\���� ���� 342.271.png");       // ����
	fire.C_img_X_Size_01 = 215;
	fire.C_img_Y_Size_01 = 411;
	fire.C_img_Frame = 342;
	fire.C_img_X_Size_02 = 342;
	fire.C_img_Y_Size_02 = 271;

	water.Anim[0].Load(L"Resource\\�Ķ� ���� 207.480.png");      // ����
	water.Anim[1].Load(L"Resource\\�Ķ� ���� 207.480.png");      // ���
	water.Anim[2].Load(L"Resource\\�Ķ� ������ 376.480.png");    // ����
	water.Anim[3].Load(L"Resource\\�Ķ� �ϰ� 207.480.png");      // �ϴ�
	water.Anim[4].Load(L"Resource\\�Ķ� ���� 376.480.png");      // ����
	water.C_img_X_Size_01 = 207;
	water.C_img_Y_Size_01 = 480;
	water.C_img_Frame = 376;
	water.C_img_X_Size_02 = 376;
	water.C_img_Y_Size_02 = 480;

	block_w.Load(L"Resource\\block1.png");
	block_h.Load(L"Resource\\block2.png");
	foot_block.Load(L"Resource\\����.png");
	rect.Load(L"Resource\\���� 40.40.png");


	lobby.Load(L"Resource\\�κ� �̹��� �ʾ�.png");
	fireStopImage.Load(L"Resource\\���� ���� 215.411.png");
	waterStopImage.Load(L"Resource\\�Ķ� ���� 215.411.png");
}

// ���� ���������� ���� ������Ʈ�� ��� �׸���
void ImageMgr::DrawMap(HDC* memdc, short stageNum, Stage& stage)
{
	if (stageNum == 0)//start ��ư
	{
		robby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);

	}
	else if (stageNum == 1) {
		lobby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);
		if (currneClientNum == 1) {
			one.Draw(*memdc, 350, 450, 150, 150, 0, 0, 50, 50);

		}
		else if (currneClientNum == 2) {
			two.Draw(*memdc, 0, 0, 60, 100, 0, 0, 60, 104);

		}
		else if (currneClientNum == 3) {
			three.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);

		}
		fraction.Draw(*memdc, 450, 450, 150, 150, 0, 0, 48, 48);
		three.Draw(*memdc, 550, 450, 150, 150, 0, 0, 50, 50);
	}
	else if (stageNum == 2) {
		lobby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);

	}
	else if (stageNum == 3)
	{
		stage1.Draw(*memdc, 0, 0, 1190, 765, 0, 480 - stage.average, 640, 480);

		for (int i = 0; i < 20 && stage.Ft[i].x != NULL; ++i)
		{
			foot_block.Draw(*memdc, stage.Ft[i].x, stage.Ft[i].y, stage.Ft[i].wid, stage.Ft[i].hei, 0, 0, 111, 23);
		}

		door_red.Draw(*memdc, stage.red_door.x, stage.red_door.y, 60, 100, stage.red_door.image_x, stage.red_door.image_y, 60, 104);
		door_blue.Draw(*memdc, stage.blue_door.x, stage.blue_door.y, 60, 100, stage.blue_door.image_x, stage.blue_door.image_y, 60, 104);
	}
	else if (stageNum == 4)
	{
		stage1.Draw(*memdc, 0, 0, 1190, 765, 0, 480 - stage.average, 640, 480);

		for (int i = 0; i < 20 && stage.Ft[i].x != NULL; ++i)
		{
			foot_block.Draw(*memdc, stage.Ft[i].x, stage.Ft[i].y, stage.Ft[i].wid, stage.Ft[i].hei, 0, 0, 111, 23);
		}

		door_red.Draw(*memdc, stage.red_door.x, stage.red_door.y, 60, 100, stage.red_door.image_x, stage.red_door.image_y, 60, 104);
		door_blue.Draw(*memdc, stage.blue_door.x, stage.blue_door.y, 60, 100, stage.blue_door.image_x, stage.blue_door.image_y, 60, 104);
	}
	else if (stageNum == 5)
	{
		stage1.Draw(*memdc, 0, 0, 1190, 765, 0, 480 - stage.average, 640, 480);

		for (int i = 0; i < 20 && stage.Ft[i].x != NULL; ++i)
		{
			foot_block.Draw(*memdc, stage.Ft[i].x, stage.Ft[i].y, stage.Ft[i].wid, stage.Ft[i].hei, 0, 0, 111, 23);
		}

		rect.Draw(*memdc, stage.Rt.x - 50, stage.Rt.y - 50, 50, 50, 0, 0, 40, 40);


		block_w.Draw(*memdc, stage.block[0].x + stage.block[0].image_x, stage.block[0].y, 100 + stage.block[0].image_x, 30, -stage.block[0].image_x, 0, 83 + stage.block[0].image_x, 25);

		door_red.Draw(*memdc, stage.red_door.x, stage.red_door.y, 60, 100, stage.red_door.image_x, stage.red_door.image_y, 60, 104);
		door_blue.Draw(*memdc, stage.blue_door.x, stage.blue_door.y, 60, 100, stage.blue_door.image_x, stage.blue_door.image_y, 60, 104);

		button_img.Draw(*memdc, stage.button[0].x, stage.button[0].y - stage.button[0].image_y, 40, stage.button[0].image_y, 0, 0, stage.button[0].image_x, stage.button[0].image_y);
	}
}

// �������� ���� ȭ�鿡�� �߾�, ��ܿ� �ִ� Timer �׸���
void ImageMgr::DrawTimer(HDC* memdc, short time) {
	clock.Draw(*memdc, 525, 0, 150, 50, 0, 0, 154, 54);
	switch (time / 60) {
	case 0:
		zero.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 1:
		one.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 2:
		two.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 3:
		three.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 4:
		four.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 5:
		five.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 6:
		six.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 7:
		seven.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 8:
		eight.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 9:
		nine.Draw(*memdc, 530, 0, 50, 50, 0, 0, 50, 50);
		break;
	}
	switch ((time % 60) / 10) {
	case 0:
		zero.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 1:
		one.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 2:
		two.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 3:
		three.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 4:
		four.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 5:
		five.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 6:
		six.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 7:
		seven.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 8:
		eight.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 9:
		nine.Draw(*memdc, 585, 0, 50, 50, 0, 0, 50, 50);
		break;
	}
	switch ((time % 60) % 10) {
	case 0:
		zero.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 1:
		one.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 2:
		two.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 3:
		three.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 4:
		four.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 5:
		five.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 6:
		six.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 7:
		seven.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 8:
		eight.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	case 9:
		nine.Draw(*memdc, 620, 0, 50, 50, 0, 0, 50, 50);
		break;
	}
}

// Fire boy�� Water girl�� �ִϸ��̼� ��� �Լ�
void ImageMgr::DrawPlayer(HDC* memdc, short Frame, PLAYER* pl, Stage& stage) {
	if (pl->on)
	{
		if ((pl->Down == TRUE) && pl->dic == 0) {
			pl->Anim[3].Draw(*memdc, pl->x - pl->wid, pl->y - pl->hei + stage.average, pl->wid, pl->hei, 0, 0, pl->C_img_X_Size_01, pl->C_img_Y_Size_01);
		}
		else if (pl->dic == 0) {
			pl->Anim[1].Draw(*memdc, pl->x - pl->wid, pl->y - pl->hei + stage.average, pl->wid, pl->hei, 0, 0, pl->C_img_X_Size_01, pl->C_img_Y_Size_01);
		}
		else if (pl->dic == -1) {
			pl->Anim[4].Draw(*memdc, pl->x - pl->wid, pl->y - pl->hei + stage.average, pl->wid, pl->hei, 0 + pl->C_img_Frame * pl->Frame, 0, pl->C_img_X_Size_02, pl->C_img_Y_Size_02);
		}
		else if (pl->dic == 1) {
			pl->Anim[2].Draw(*memdc, pl->x - pl->wid, pl->y - pl->hei + stage.average, pl->wid, pl->hei, 0 + pl->C_img_Frame * pl->Frame, 0, pl->C_img_X_Size_02, pl->C_img_Y_Size_02);
		}
	}
}