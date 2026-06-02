#pragma once
//´æµµÒ³Ãæ

#include "View.h"
#include "button.h"
#include "global.h"
#include <chrono>



class SaveView : public View {
public:
	// enter()¡¢exit()¡¢handleInput()¡¢update()¡¢draw()
	SaveView() = default;
	~SaveView() = default;

	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;



private:
	ImageButton loadSaveButton; //¶ÁÈ¡´æµµ°´Å¥
	ImageButton quitButton; // ÍË³ö°´Å¥

	ImageButton saveButton1;
	ImageButton saveButton2;
	ImageButton saveButton3;

};


