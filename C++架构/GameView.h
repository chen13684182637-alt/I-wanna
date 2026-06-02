//”Œœ∑ΩÁ√Ê
#pragma once
#include "View.h"
#include "global.h"
#include "button.h"


class GameView : public View {
public:
	GameView() = default;
	~GameView() = default;

	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;

private:
	ImageButton newGameButton;
	ImageButton exitButton;
	ImageButton settingButton;
	ImageButton historyButton;
	ImageButton teamButton;
};