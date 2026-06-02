//暂停界面的函数定义
#include"PauseView.h"
#include"viewManager.h"
const int continueButton_X = WINDOW_WIDTH / 2 - IMAGE_PAUSE_WIDTH / 2 + IMAGE_PAUSE_BOTTON_HEIGHT;
const int continueButton_Y = WINDOW_HEIGHT / 2 - IMAGE_PAUSE_HEIGHT / 2 + IMAGE_PAUSE_BOTTON_HEIGHT;
const int menuButton_X = WINDOW_WIDTH / 2 - IMAGE_PAUSE_WIDTH / 2 + IMAGE_PAUSE_BOTTON_HEIGHT;
const int menuButton_Y = WINDOW_HEIGHT / 2 - IMAGE_PAUSE_HEIGHT / 2 + 2 * IMAGE_PAUSE_BOTTON_HEIGHT + IMAGE_BOTTON_DIS;

/*
* 负责：残念筠
* 功能：初始化暂停界面，设置按钮位置等
*/

void PauseView::enter() {
	loadimage(&PAUSE, _T(PAUSE_PATH), IMAGE_PAUSE_WIDTH, IMAGE_PAUSE_HEIGHT);
	ImageButton continueButton(continueButton_X, continueButton_Y,IMAGE_PAUSE_BOTTON_WIDTH, IMAGE_PAUSE_BOTTON_HEIGHT,"");
	ImageButton menuButton(menuButton_X, menuButton_Y,IMAGE_PAUSE_BOTTON_WIDTH, IMAGE_PAUSE_BOTTON_HEIGHT, "");
}

// 更新暂停界面逻辑，无需更新
void PauseView::update() {

}

/*
* 负责：残念筠
* 功能：绘制暂停界面
*/
void PauseView::draw() {
	putimage_new(WINDOW_WIDTH / 2 - IMAGE_PAUSE_WIDTH / 2, WINDOW_HEIGHT / 2 - IMAGE_PAUSE_HEIGHT / 2, &PAUSE);
	menuButton.drawButton();
	continueButton.drawButton();
}

/*
* 负责：残念筠
* 功能：处理暂停界面输入，主要处理各个按钮的点击事件
*/
void PauseView::handleInput(ExMessage& msg) {
	if (msg.lbutton)
	{
		if(inArea(msg.x,msg.y,continueButton_X, continueButton_Y, 
			continueButton_X+ IMAGE_PAUSE_BOTTON_WIDTH, continueButton_Y+ IMAGE_PAUSE_BOTTON_HEIGHT))
			view_manager.switch_to(ViewManager::ViewType::Game);
				
		if(inArea(msg.x, msg.y, menuButton_X, menuButton_Y,
			menuButton_X + IMAGE_PAUSE_BOTTON_WIDTH, menuButton_Y + IMAGE_PAUSE_BOTTON_HEIGHT))
			view_manager.switch_to(ViewManager::ViewType::Menu); 
	}
}


// 退出暂停界面，释放资源
void PauseView::exit() {
}
