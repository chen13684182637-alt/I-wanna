#pragma once
#include "View.h"
#include "button.h"
#include "global.h"
#include<graphics.h>
#define IMAGE_PAUSE_WIDTH 328
#define IMAGE_PAUSE_HEIGHT 246
#define IMAGE_PAUSE_BOTTON_WIDTH 209
#define IMAGE_PAUSE_BOTTON_HEIGHT 60
#define IMAGE_BOTTON_DIS 11
#define PAUSE_PATH "Assert/images/Pause.png"



class PauseView : public View {
public:
	// enter()、exit()、handleInput()、update()、draw()
	PauseView() = default;
	~PauseView() = default;

	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;

private:
	IMAGE PAUSE;
	// 返回主菜单按钮
	ImageButton menuButton;
	// 继续游戏按钮
	ImageButton continueButton;


};

