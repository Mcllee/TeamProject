#pragma once
#include "Stage.h"
#include"ImageMgr.h"

// PNG파일 읽어오기
void ImageMgr::LoadImages() {
	loading.Load(L"Resource\\로딩중 이미지.png");
	robby.Load(L"Resource\\로비 이미지 초안 2.png");
	buttonimg.Load(L"Resource\\플레이 버튼 158.60.png");
	stage1.Load(L"Resource\\맵 기본.png");
	Jewelry_blue.Load(L"Resource\\파랑 보석 28.24.png");
	Jewelry_red.Load(L"Resource\\빨강 보석 29.24.png");
	red_water_center.Load(L"Resource\\빨강 가운데물 21.14.png");
	red_water_left.Load(L"Resource\\빨강 왼쪽물 24.25.png");
	red_water_right.Load(L"Resource\\빨강 오른쪽물 24.25.png");
	blue_water_center.Load(L"Resource\\파랑 가운데물 23.14.png");
	blue_water_left.Load(L"Resource\\파랑 왼쪽물 23.23.png");
	blue_water_right.Load(L"Resource\\파랑 오른쪽물 23.23.png");
	green_water_center.Load(L"Resource\\초록 가운데물 23.14.png");
	green_water_left.Load(L"Resource\\초록 왼쪽물 24.25.png");
	green_water_right.Load(L"Resource\\초록 오른물 24.25.png");
	die.Load(L"Resource\\죽었을 때 159.89.png");
	endimg.Load(L"Resource\\end.png");
	retryimg.Load(L"Resource\\retry.png");
	backimg.Load(L"Resource\\dieimg.png");
	door_red.Load(L"Resource\\빨강 문 60.104.png");
	door_blue.Load(L"Resource\\파랑 문 60.104.png");
	button_img.Load(L"Resource\\버튼 42.16.png");
	red_stair.Load(L"Resource\\빨강 계단 50.73.png");
	blue_stair.Load(L"Resource\\파랑 계단 54.77.png");
	clear_img.Load(L"Resource\\클리어.png");
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
	clock.Load(L"Resource\\시계.png");
	timeout.Load(L"Resource\\타임아웃.png");
	fraction.Load(L"Resource\\fraction.png");

	players[0].Anim[0].Load(L"Resource\\빨강 정지 215.411.png");       // 정지
	players[0].Anim[1].Load(L"Resource\\빨강 정지 215.411.png");       // 상승
	players[0].Anim[2].Load(L"Resource\\빨강 오른쪽 342.271.png");	 // 우측
	players[0].Anim[3].Load(L"Resource\\빨강 하강 215.411.png");       // 하단
	players[0].Anim[4].Load(L"Resource\\빨강 왼쪽 342.271.png");       // 좌측
	players[0].C_img_X_Size_01 = 215;
	players[0].C_img_Y_Size_01 = 411;
	players[0].C_img_Frame = 342;
	players[0].C_img_X_Size_02 = 342;
	players[0].C_img_Y_Size_02 = 271;

	players[1].Anim[0].Load(L"Resource\\파랑 정지 207.480.png");      // 정지
	players[1].Anim[1].Load(L"Resource\\파랑 정지 207.480.png");      // 상승
	players[1].Anim[2].Load(L"Resource\\파랑 오른쪽 376.480.png");    // 우측
	players[1].Anim[3].Load(L"Resource\\파랑 하강 207.480.png");      // 하단
	players[1].Anim[4].Load(L"Resource\\파랑 왼쪽 376.480.png");      // 좌측
	players[1].C_img_X_Size_01 = 207;
	players[1].C_img_Y_Size_01 = 480;
	players[1].C_img_Frame = 376;
	players[1].C_img_X_Size_02 = 376;
	players[1].C_img_Y_Size_02 = 480;

	players[2].Anim[0].Load(L"Resource\\흙_정지_215.411.png");       // 정지
	players[2].Anim[1].Load(L"Resource\\흙_정지_215.411.png");       // 상승
	players[2].Anim[2].Load(L"Resource\\흙_오른쪽_342.271.png");	 // 우측
	players[2].Anim[3].Load(L"Resource\\흙_하강_215.411.png");       // 하단
	players[2].Anim[4].Load(L"Resource\\흙_왼쪽_342.271.png");       // 좌측
	players[2].C_img_X_Size_01 = 215;
	players[2].C_img_Y_Size_01 = 411;
	players[2].C_img_Frame = 342;
	players[2].C_img_X_Size_02 = 342;
	players[2].C_img_Y_Size_02 = 271;

	block_w.Load(L"Resource\\block1.png");
	block_h.Load(L"Resource\\block2.png");
	foot_block.Load(L"Resource\\발판.png");
	rect.Load(L"Resource\\상자 40.40.png");


	lobby.Load(L"Resource\\로비 이미지 초안.png");
	fireStopImage.Load(L"Resource\\빨강 정지 215.411.png");
	waterStopImage.Load(L"Resource\\파랑 정지 215.411.png");
	earthStopImage.Load(L"Resource\\흙_정지_ 215.411.png");
	
	leftArrow.Load(L"Resource\\left_arrow.png");
	rightArrow.Load(L"Resource\\right_arrow.png");
	me.Load(L"Resource\\me.png");
	player1.Load(L"Resource\\player1.png");
	player2.Load(L"Resource\\player2.png");
	
	selectBtn.Load(L"Resource\\select_btn.png");

}


// 현재 스테이지에 맞춰 오브젝트와 배경 그리기
void ImageMgr::DrawMap(HDC* memdc, short stageNum, Stage& stage)
{
	switch (stageNum)
	{
	case STAGE_TITLE:
		robby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);
		break;
	case STAGE_LOADING:
		lobby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);
		if (currneClientNum == 1) {
			one.Draw(*memdc, 350, 450, 150, 150, 0, 0, 50, 50);
		}
		else if (currneClientNum == 2) {
			two.Draw(*memdc, 350, 450, 150, 150, 0, 0, 50, 50);
		}
		else if (currneClientNum == 3) {
			three.Draw(*memdc, 350, 450, 150, 150, 0, 0, 50, 50);
		}
		fraction.Draw(*memdc, 450, 450, 150, 150, 0, 0, 48, 48);
		three.Draw(*memdc, 550, 450, 150, 150, 0, 0, 50, 50);

		loading.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);
		break;
	case STAGE_LOBBY:
		 lobby.Draw(*memdc, 0, 0, 1190, 770, 0, 0, 640, 480);
		//me
		me.Draw(*memdc, 150, 100, 150, 150, 0, 0, 403, 317);
		//if(나의 캐릭터에 따라서)
		fireStopImage.Draw(*memdc, 170, 200, 100, 200, 0, 0, 215, 411);
		//waterStopImage.Draw(*memdc, 330, 250, 70, 70, 0, 0, 300, 300);
		//if(player1의 캐릭터에 따라서) => 서버로 부터 받은 데이터에 따라서 캐릭터 달라지게
		player1.Draw(*memdc, 500, 100, 150, 150, 0, 0, 403, 317);
		//if(player2의 캐릭터에 따라서) => 서버로 부터 받은 데이터에 따라서 캐릭터 달라지게
		player2.Draw(*memdc, 900, 100, 150, 150, 0, 0, 403, 317);
		
	break;
	case STAGE_01:
		stage1.Draw(*memdc, 0, 0, 1190, 765, 0, 480 - stage.average, 640, 480);

		for (int i = 0; i < 20 && stage.Ft[i].x != NULL; ++i)
		{
			foot_block.Draw(*memdc, stage.Ft[i].x, stage.Ft[i].y, stage.Ft[i].wid, stage.Ft[i].hei, 0, 0, 111, 23);
		}

		door_red.Draw(*memdc, stage.red_door.x, stage.red_door.y, stage.red_door.wid, stage.red_door.hei, stage.red_door.image_x, stage.red_door.image_y, 60, 104);
		door_blue.Draw(*memdc, stage.blue_door.x, stage.blue_door.y, stage.blue_door.wid, stage.blue_door.hei, stage.blue_door.image_x, stage.blue_door.image_y, 60, 104);
		break;
	case STAGE_02:
		stage1.Draw(*memdc, 0, 0, 1190, 765, 0, 480 - stage.average, 640, 480);

		for (int i = 0; i < 20 && stage.Ft[i].x != NULL; ++i)
		{
			foot_block.Draw(*memdc, stage.Ft[i].x, stage.Ft[i].y, stage.Ft[i].wid, stage.Ft[i].hei, 0, 0, 111, 23);
		}

		door_red.Draw(*memdc, stage.red_door.x, stage.red_door.y, 60, 100, stage.red_door.image_x, stage.red_door.image_y, 60, 104);
		door_blue.Draw(*memdc, stage.blue_door.x, stage.blue_door.y, 60, 100, stage.blue_door.image_x, stage.blue_door.image_y, 60, 104);
		break;
	case STAGE_03:
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
		break;
	}
}

// 스테이지 진행 화면에서 중앙, 상단에 있는 Timer 그리기
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

// Fire boy와 Water girl의 애니메이션 재생 함수
void ImageMgr::DrawPlayers(HDC* memdc, Stage& stage) {
	for (PLAYER& pl : players) {
		if (pl.on)
		{
			if ((pl.Down == TRUE) && pl.direction == 0) {
				pl.Anim[3].Draw(*memdc, pl.x - pl.wid, pl.y - pl.hei + stage.average, pl.wid, pl.hei, 0, 0, pl.C_img_X_Size_01, pl.C_img_Y_Size_01);
			}
			else if (pl.direction == 0) {
				pl.Anim[1].Draw(*memdc, pl.x - pl.wid, pl.y - pl.hei + stage.average, pl.wid, pl.hei, 0, 0, pl.C_img_X_Size_01, pl.C_img_Y_Size_01);
			}
			else if (pl.direction == -1) {
				pl.Anim[4].Draw(*memdc, pl.x - pl.wid, pl.y - pl.hei + stage.average, pl.wid, pl.hei, 0 + pl.C_img_Frame * pl.Frame, 0, pl.C_img_X_Size_02, pl.C_img_Y_Size_02);
			}
			else if (pl.direction == 1) {
				pl.Anim[2].Draw(*memdc, pl.x - pl.wid, pl.y - pl.hei + stage.average, pl.wid, pl.hei, 0 + pl.C_img_Frame * pl.Frame, 0, pl.C_img_X_Size_02, pl.C_img_Y_Size_02);
			}
		}
	}
}