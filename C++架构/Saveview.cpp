#pragma once
#include"viewManager.h"
#include "SaveView.h"

extern ViewManager view_manager;


// 进入存档视图，初始化按钮位置等
void SaveView::enter() {

	saveButton1 = ImageButton(310, 158, 179, 75, "./Assert/Button/Save1.png");

	saveButton2 = ImageButton(310, 262, 179, 75, "./Assert/Button/Save2.png");

	saveButton3 = ImageButton(310, 367, 179, 75, "./Assert/Button/Save3.png");



	//初始话存档按钮的坐标与长宽
	loadSaveButton.h = 60;
	loadSaveButton.w = 360;
	loadSaveButton.x = 320;
	loadSaveButton.y = 110;

	//初始化离开按钮的坐标与长宽
	quitButton.h = 10;
	quitButton.w = 360;
	quitButton.x = 320;
	quitButton.y = 300;


}

// 更新存档视图逻辑，无需更新 (空)
void SaveView::update() {

}

// 绘制存档视图，绘制各个存档信息和读取存档和退出按钮
void SaveView::draw() {

	string savetext = "存档1";
	string quittext = "按下ESC返回游戏菜单";

	//初始化存档按钮
	TextButton savebutton(loadSaveButton.x, loadSaveButton.y, loadSaveButton.x +
		loadSaveButton.w, loadSaveButton.y + loadSaveButton.h, savetext.c_str());

	//初始化离开按钮
	TextButton quitbutton(quitButton.x, quitButton.y, quitButton.x +
		quitButton.w, quitButton.y + quitButton.h, quittext.c_str());
	setbkcolor(RGB(135, 206, 235));
	cleardevice();

	putimage_new(0, 0, &menu_bk_image);

	//绘画存档按钮
	//savebutton.drawButton();

	//绘画离开按钮
	//quitbutton.drawButton();

	saveButton1.drawButton();
	saveButton2.drawButton();
	saveButton3.drawButton();

	settextcolor(RED);

	outtextxy(345, 480, _T("按 ESC 返回菜单"));

}

// 处理存档视图输入，主要处理存档选择和读取存档按钮以及退回主菜单点击事件
void SaveView::handleInput(ExMessage& msg) {

	if (msg.vkcode == VK_ESCAPE)
	{
		view_manager.switch_to(ViewManager::ViewType::Menu);
		//		return;
	}
	if (msg.message == WM_LBUTTONDOWN)
	{
		if (saveButton1.ButtonClicked(msg))
		{
			ChosenCurrentMap = 1;
			PlayerSpawnInitFlag = 0;
			view_manager.switch_to(ViewManager::ViewType::Game);
			return;
		}
		if (saveButton2.ButtonClicked(msg))
		{
			ChosenCurrentMap = 2;
			PlayerSpawnInitFlag = 0;
			view_manager.switch_to(ViewManager::ViewType::Game);
			
			return;
		}
		if (saveButton3.ButtonClicked(msg))
		{
			ChosenCurrentMap = 3;
			PlayerSpawnInitFlag = 0;
			view_manager.switch_to(ViewManager::ViewType::Game);
			return;
		}


		//点击到起开按钮
		if (msg.x >= quitButton.x && msg.x <= quitButton.x + quitButton.w
			&& msg.y >= quitButton.y && msg.y <= quitButton.y + quitButton.h)
		{
			view_manager.switch_to(ViewManager::ViewType::Menu);
			return;
		}
	}


	//switch (msg.message)
	//{
	//
	//
	////鼠标点击
	//case WM_LBUTTONDOWN:
	//{
	//			
	//	if (saveButton1.ButtonClicked(msg))
	//	{
	//		view_manager.switch_to(ViewManager::ViewType::Game);
	//		return;
	//	}
	//	if (saveButton2.ButtonClicked(msg))
	//	{
	//		view_manager.switch_to(ViewManager::ViewType::Game);
	//		return;
	//	}
	//	if (saveButton3.ButtonClicked(msg))
	//	{
	//		view_manager.switch_to(ViewManager::ViewType::Game);
	//		return;
	//	}


	//	//点击到起开按钮
	//	if (msg.x >= quitButton.x && msg.x <= quitButton.x + quitButton.w
	//		&& msg.y >= quitButton.y && msg.y <= quitButton.y + quitButton.h)
	//	{
	//		view_manager.switch_to(ViewManager::ViewType::Menu);
	//		return;
	//	}
	//	
	//}
	//
	//}



}

// 退出存档界面，释放资源 
void SaveView::exit()
{
	cleardevice();
}



