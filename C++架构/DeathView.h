//死亡界面

#pragma once
#include "View.h"
#include "button.h"
#include "global.h"

class DeathView : public View {
public:
	// enter()、exit()、handleInput()、update()、draw()
	DeathView() = default;
	~DeathView() = default;
	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;

	void setDeathMessage(const std::string& message) {
		deathMessage = message;
	}

private:
	IMAGE m_gameOverBg;
	ImageButton restartButton; //重新开始按钮
	std::string deathMessage; //死亡提示信息
};


#define DEATH_WIDTH 800
#define DEATH_HEIGHT 320