#include"DeathView.h"
#include"viewManager.h"
#include"Map.h"
// 死亡界面初始化
// 需要载入死亡原因，设置重新开始按钮位置等
void DeathView::enter() {
    // 1. 载入死亡原因:没有找到哪个类里面有这个

    // 2. 设置重新开始按钮的位置
    loadimage(&m_gameOverBg, _T("Assert/images/sprGAMEOVER.png"));
    restartButton.x = 250, restartButton.y = 300;
    restartButton.w = 220, restartButton.h = 70;

    mciSendString("stop music", 0, 0, 0);
    mciSendString("seek deathMusic to start",0,0,0);
    mciSendString("play deathMusic", 0, 0, 0);
    
}

// 死亡界面更新逻辑，无需更新
void DeathView::update() {
}

// 死亡界面绘制， 将死亡背景图，死亡信息，重新开始按钮绘制出来
void DeathView::draw() {
    
    /*setbkmode(TRANSPARENT);
    setfont(28, 0, _T("微软雅黑"));
    settextcolor(RED);
    outtextxy(200, 400, "游戏失败！");
    std::string deathInfo = "死亡原因：" + deathMessage;
    outtextxy(200, 460, deathInfo.c_str());
    restartButton.drawButton();*/
    putimage_new(WINDOW_WIDTH/2-DEATH_WIDTH/2, WINDOW_HEIGHT/2-DEATH_HEIGHT/2, &m_gameOverBg);
    
}


// 死亡界面输入处理， 主要处理重新开始按钮的点击事件
// 点击任意按钮重开游戏
void DeathView::handleInput(ExMessage& msg) {
    //if (msg.message == WM_LBUTTONDOWN) { // 判断是否是鼠标左键按下事件
    //    // 重新开始按钮点击判断：
    //    if (inArea(
    //        msg.x, msg.y,
    //        restartButton.x, restartButton.y,
    //        restartButton.x + restartButton.w, restartButton.y + restartButton.h
    //    )) {

    //        std::cout << "重新开始按钮被点击" << std::endl;
    //        
    //        // 点击后切换回游戏视图
    //        view_manager.switch_to(ViewManager::ViewType::Game);
    //    }
    //}
    if ((GetAsyncKeyState('R') & 0x8000) )
    {
        view_manager.switch_to(ViewManager::ViewType::Game);
        mciSendString("stop deathMusic",0,0,0);
        mciSendString("play music repeat", 0, 0, 0);
        kid.Revive();
    }
}


// 死亡界面退出，释放资源，释放死亡现象字符串即可。
void DeathView::exit() {

    CurrentMap.GlobalInitLevel();
    CurrentMap.loadMap();
}

