//游戏菜单的函数定义
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MenuView.h"
#include "utils.h"
#include "viewManager.h"
#include <cstdlib>
#include "global.h"
#include <sstream>

#include <iostream>
#include "saveView.h"

// 进入菜单视图，初始化按钮位置等
void MenuView::enter() {//1. 初始化“开始游戏”按钮 


    ////设置位置
    //startButton.setPos(200, 300);
    //// 设置大小
    //startButton.setSize(150, 60);
    //// 绑定按钮图片（假设global.h中定义了start_btn_img这个图片资源）
    //startButton.setImage(&start_btn_img);


    ////  2. 初始化“退出游戏”按钮
    //exitButton.setPos(200, 400);  // 位置在开始按钮下方
    //exitButton.setSize(150, 60);
    //exitButton.setImage(&exit_btn_img);  // 绑定退出按钮的图片


    //// 3. 初始化“团队介绍”按钮 
    //teamButton.setPos(200, 500);  // 位置在退出按钮下方
    //teamButton.setSize(150, 60);
    //teamButton.setImage(&team_btn_img);  // 绑定团队介绍按钮的图片


    //// 4. 初始化“设置”按钮
    //historyButton.setPos(200, 600);  // 位置在团队介绍按钮下方
    //historyButton.setSize(150, 60);
    //historyButton.setImage(&history_btn_img);  // 绑定历史记录按钮的图片

    startButton = ImageButton(293, 84+80, 213, 72, "./Assert/Button/startButton.png");

    teamButton = ImageButton(293, 252 + 80, 213, 72, "./Assert/Button/TeamIntroductionButton.png");

    settingButton = ImageButton(293, 336 + 80, 213, 72, "./Assert/Button/settingButton.png");

    exitButton = ImageButton(293, 420 + 80, 213, 72, "./Assert/Button/exitButton.png");

    playintroduce = ImageButton(293, 168 + 80, 213, 72, "./Assert/Button/PlayIntroduce.png");

    loadimage(&menu_bk_image, _T("Assert\\images\\bg1.png"), WINDOW_WIDTH, WINDOW_HEIGHT,true);
    loadimage(&game_title, _T("Assert/images/title.png"), 600, 120);
}

// 更新菜单视图逻辑，无需更新
void MenuView::update() {

}

// 绘制菜单视图，放置菜单图像和新游戏，制作人员，退出，设置，历史记录按钮。
void MenuView::draw() {
    /*测试用例*/
    fillrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    /*测试用例*/

    ////////////////// 暂时使用纯色背景代替
    setbkcolor(RGB(135, 206, 235));  // 设置背景色
    cleardevice();                   // 用背景色刷新整个画面

    // 绘制背景图片
    putimage_new(0, 0, &menu_bk_image);

    putimage_new((WINDOW_WIDTH - 600) / 2, 40, &game_title);
    

    // 绘制“游戏”按钮（需要头文件中有newGameButton）
    startButton.drawButton();
    // 绘制“退出游戏”按钮
    exitButton.drawButton();
    // 绘制“制作人员”按钮
    settingButton.drawButton();
    // 8. 绘制“团队介绍”按钮
    teamButton.drawButton();

    playintroduce.drawButton();
}

// 处理菜单视图输入，主要处理按钮点击事件，以及ws光标移动和回车确认事件
void MenuView::handleInput(ExMessage& msg) {
    if (msg.message == WM_LBUTTONDOWN) {
        // 开始按钮点击判断：左=x，上=y，右=x+w，下=y+h
        if (startButton.ButtonClicked(msg)) {

            view_manager.switch_to(ViewManager::ViewType::Save);
            return;
        }
        // 团队按钮点击判断
        if (teamButton.ButtonClicked(msg)) {

            // 切换到团队介绍视图
            view_manager.switch_to(ViewManager::ViewType::TeamIntroduce);
            return;
        }
        if (exitButton.ButtonClicked(msg)) {

            ::exit(0);
        }
        if (settingButton.ButtonClicked(msg))
        {
            // 设置按钮被点击的逻辑处理
            view_manager.switch_to(ViewManager::ViewType::Setting);
            return;
        }
        if (playintroduce.ButtonClicked(msg))
        {
            view_manager.switch_to(ViewManager::ViewType::PlayIntroduce);
            return;
        }
    }

}

// 退出菜单视图，释放资源
void MenuView::exit() {
    setbkcolor(SKYBLUE);
    cleardevice();
}

