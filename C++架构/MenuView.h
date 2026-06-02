//游戏菜单
#pragma once

#include "View.h"
#include "button.h"
#include "global.h"
#include <chrono>


class MenuView : public View {
public:
	// enter()、exit()、handleInput()、update()、draw()
	MenuView() = default;
	~MenuView() = default;

	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;

private:

	// 开始游戏按钮
	ImageButton startButton;
	// 退出游戏按钮
	ImageButton exitButton;
	// 团队介绍按钮
	ImageButton teamButton;
	// 绘制“制作人员”按钮
	ImageButton settingButton;
	// 绘制玩法介绍按钮
	ImageButton playintroduce;

	//IMAGE bkpic;



};


