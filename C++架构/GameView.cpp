#pragma once
#include "GameView.h"
#include "Trap.h"
#include "Player.h"
#include "easyx.h"
#include "viewManager.h"

bool RFlag = 1; //防止按住R无限重生

/*测试用例*/
//NormalGround ground1 = NormalGround(0, 400, WINDOW_WIDTH, 200);		// 地基
//NormalGround ground2 = NormalGround(500, 240,93,300);		// 右侧柱子
//NormalGround ground3 = NormalGround(230, 240, 93, 93);
//
//Rect trapimgRect = Rect(400, 400-31, 31, 31);
//TriangleTrap trap1 = TriangleTrap(Rect2Tri(trapimgRect), trapimgRect, TRIANGLE_DIRECT_UP);
//TriangleTrap trap2 = TriangleTrap(Rect(400 + 31, 400 - 31, 31, 31), 1);
//
//SavePoint savepoint1 = SavePoint(100, 400 - 31, 31, 31);
//
//EndPoint endpoint1 = EndPoint(750, 240, 31, 31);
/*测试用例*/

// 游戏界面初始化， 地图角色信息均保存在全局变量中，只需设置暂停游戏按钮
void GameView::enter() {
	setfillcolor(SKYBLUE);
	
	TextButton pause(0, 0, 30, 25, "Esc");
	kid.ReInitDownBoundary();
	kid.ReInitUpBoundary();
	kid.ReInitLeftBoundary();
	kid.ReInitRightBoundary();
	CurrentMap.GlobalInitLevel();
	CurrentMap.loadMap();

	
}

// 根据角色的速度信息更新角色位置，处理隐藏陷阱的触发
void GameView::update() {
}


//  遍历地图绘制地图元素和陷阱，以及人物
void GameView::draw() {
	// CurrentMap.drawMap();
	fillrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	/*测试用例*/
	
	/*if (savepoint1.checkPlayerCollision())
	{
		savepoint1.setIsSaved(true);
		savepoint1.draw(false);
		
	}
	else
		savepoint1.draw(true);*/
	/*测试用例*/
	CurrentMap.drawMap();
	kid.PlayerDraw();
	/*测试用例*/
	/*ground1.draw();
	ground2.draw();
	ground3.draw();
	trap1.draw();
	trap2.draw();
	endpoint1.draw();*/
	/*测试用例*/
}


void GameView::handleInput(ExMessage& msg) {
	
	
	kid.PlayerMove(msg);
	int playerVelX = kid.GetKidVelX();
	int playerVelY = kid.GetKidVelY();
	CurrentMap.updateMap(kid.getPlayerRectBox(), playerVelX, playerVelY);

			if (msg.vkcode == VK_ESCAPE)
			{
				view_manager.switch_to(ViewManager::ViewType::Pause);
			}
			if (msg.vkcode == 'K') {
				kid.Death();
				view_manager.switch_to(ViewManager::ViewType::Death);
			}

	//若角色不存活
    if(!kid.isAlive()) view_manager.switch_to(ViewManager::ViewType::Death);


	/* 测试用例 */
	// 陷阱判断 
		//if (trap1.checkCollision(kid.getPlayerRectBox()) || trap2.checkCollision(kid.getPlayerRectBox()))
		//{
		//	kid.Death();
		//	view_manager.switch_to(ViewManager::ViewType::Death);
		//}

		//// 终点
		//if (endpoint1.checkPlayerReach())
		//{
		//	kid.Revive();
		//	view_manager.switch_to(ViewManager::ViewType::Menu);
		//}
		
	/* 测试用例 */


	// 按R键，角色重置回复活点
	
	
}

// 退出游戏界面 (切换)
void GameView::exit() {

	CurrentMap.GlobalInitLevel();
}


