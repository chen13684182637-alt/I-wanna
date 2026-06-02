

#include"VictoryView.h"
#include "viewManager.h"

void VictoryView::enter()
{
	string backbotton = "点我回到菜单";
	TextButton tempbotton((WINDOW_WIDTH - 192) / 2, 400+100, 192, 60, backbotton.c_str());
	loadimage(&Winview, _T("Assert//images//VictoryView.png"), VICTORY_WIDTH, VICTORY_HEIGHT,true);
	backButton = tempbotton;
	PlayerSpawnInitFlag = 0;
	CurrentMap.GlobalInitLevel();
	CurrentMap.loadMap();

}

void VictoryView::update()
{
	//无逻辑，待以后更新
}

void VictoryView::draw()
{
	putimage_new(
		WINDOW_WIDTH / 2 - VICTORY_WIDTH / 2,
		WINDOW_HEIGHT / 2 - VICTORY_HEIGHT / 2,
		&Winview
	);
	//backButton.drawButton();  
}

void VictoryView::handleInput(ExMessage& msg)
{
	if ((GetAsyncKeyState('M') & 0x8000))
	{
		view_manager.switch_to(ViewManager::ViewType::Menu);
	}
	if (msg.message == WM_LBUTTONDOWN) 
	{
		// 判断是否点击返回按钮
		if (inArea(msg.x, msg.y,
			backButton.x, backButton.y,
			backButton.x + backButton.w, backButton.y + backButton.h)) {
			std::cout << "返回菜单按钮被点击" << std::endl;
			// 切换回菜单视图（调用ViewManager的视图切换功能）
			view_manager.switch_to(ViewManager::ViewType::Menu);
		}
	}
}

void VictoryView::exit()
{
	
}