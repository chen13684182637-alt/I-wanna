//团队介绍
#include "TeamIntroduceView.h"
#include "utils.h"
#include "ViewManager.h"
#include <cstdlib>
#include <iostream>

//ImageButton back_button;

// 进入视图：加载背景资源
void TeamIntroduceView::enter() {
    //暂时没有找到合适的背景图
    loadimage(&team_bk_image, _T("Assert\\images\\bg1.png"), WINDOW_WIDTH, WINDOW_HEIGHT, true);
    string backbotton = "点我回到菜单";
    // Button(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    TextButton tempbotton((WINDOW_WIDTH-192)/2, 400, 192, 60, backbotton.c_str());

    backButton = tempbotton;
}

// 更新视图：团队介绍为静态页面，无动态逻辑，暂时为空
void TeamIntroduceView::update() {
    // 若后续需添加动态效果（如文字滚动），可在此实现
}


void TeamIntroduceView::draw() {
    // 1. 绘制背景图
    putimage_new(0, 0,&team_bk_image);

    // 2. 绘制团队信息文本
    settextstyle(40, 0, _T("微软雅黑"));

    settextcolor(RGB(0, 0, 0)); // 黑色文本

    // 团队名称
    int name_width = textwidth(_T("游戏开发团队：请输入文本"));
    outtextxy((WINDOW_WIDTH - name_width) / 2 + 11, 60, _T("游戏开发团队：请输入文本"));


    std::string team_members[10] = { "成员1：mer（组长）",
                                    "成员2：亿光（副组长）",
                                    "成员3：抹茶（技术官）" ,
                                    "成员4：残念筠（技术官）",
                                    "成员5：好吧（技术官）",
                                    "成员6：郭建业（产品经理）",
                                   "成员7：melen(产品经理)",
                                    "成员8：charice（信息官）",
                                    "成员9：刘谌（信息官）",
                                    "成员10：w（监督官）" };
    // 成员列表
    settextstyle(30, 0, _T("微软雅黑"));
    for (int i = 0; i < 10; ++i) {
        //wstring t = StringToWString(team_members[i]);
        string t = team_members[i];
        int member_width = textwidth(t.c_str());
        outtextxy(300, 132 + i * 24, t.c_str());

    }

    // 3. 绘制返回菜单按钮
    backButton.drawButton();
}

// 处理输入：仅响应返回按钮点击（切换回菜单视图）
void TeamIntroduceView::handleInput(ExMessage& msg) {
    // 检测鼠标左键点击
    if (msg.message == WM_LBUTTONDOWN) {
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

// 退出视图：释放资源（IMAGE自动释放，无额外动态资源需手动释放）
void TeamIntroduceView::exit() {
    // 若后续加载了音效、动态内存等资源，可在此处释放
    std::cout << "退出团队介绍视图" << std::endl;
}