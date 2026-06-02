#include"PlayIntroduceView.h"
#include"viewManager.h"

void PlayIntroduceView::enter()
{
	string backbotton = "点我回到菜单";
	TextButton tempbotton((WINDOW_WIDTH - 192) / 2, 400 , 192, 60, backbotton.c_str());
    loadimage(&EndPic, _T("Assert\\images\\sprWarp.png"));
	CntinueButton = tempbotton;

    loadimage(&intrbkpic, _T("Assert\\images\\bg1.png"), WINDOW_WIDTH, WINDOW_HEIGHT, true);
}

void PlayIntroduceView::update()
{
	//无逻辑，待以后更新
}

void PlayIntroduceView::draw()
{
    
    putimage_new(0,0,&intrbkpic);

    settextstyle(40, 0, _T("微软雅黑"));

    settextcolor(RGB(0, 0, 0)); // 黑色文本

    // 团队名称
    int name_width = textwidth(_T("游戏玩法介绍"));
    outtextxy((WINDOW_WIDTH - name_width) / 2 + 11-100, 60, _T("游戏玩法介绍"));


    std::string playintroduce[9] = { "向左行走：A",
                                    "向右边行走：D",
                                    "起跳：空格" ,
                                    "重生：R",
                                    "碰到尖刺/碰到陷阱/超出视图都会死亡",
                                    "进入终点则进入下一张地图",
                                   "当通关最后一张地图时，游戏结束",
                                    "游戏中，按下Esc暂停，可退出",
                                    "这是终点的样子：",
                                    };
    // 成员列表
    settextstyle(30, 0,_T( "微软雅黑"));
    for (int i = 0; i < 9; ++i) {
        // wstring t = StringToWString(playintroduce[i]);
        string t = playintroduce[i];
        int member_width = textwidth(t.c_str());
        outtextxy(200, 132 + i * 24, t.c_str());

    }

    putimage_new(380, 334, &EndPic);
	CntinueButton.drawButton();
}

void PlayIntroduceView::handleInput(ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		// 判断是否点击返回按钮
		if (inArea(msg.x, msg.y,
			CntinueButton.x, CntinueButton.y,
			CntinueButton.x + CntinueButton.w, CntinueButton.y + CntinueButton.h)) {
			std::cout << "返回菜单按钮被点击" << std::endl;
			// 切换回菜单视图（调用ViewManager的视图切换功能）
			view_manager.switch_to(ViewManager::ViewType::Menu);
		}
	}
}

void PlayIntroduceView::exit()
{
	//空实现
}