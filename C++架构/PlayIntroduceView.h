#pragma once
#include "PlayIntroduceView.h"
#include "button.h"
#include "view.h"
#include<easyx.h>
#include<graphics.h>

class PlayIntroduceView :public View
{
public:
    PlayIntroduceView() = default;
    ~PlayIntroduceView() = default;


    void enter() override;
    void update() override;
    void draw() override;
    void handleInput(ExMessage& msg) override;
    void exit() override;

private:
    TextButton CntinueButton;
    IMAGE EndPic;

    IMAGE intrbkpic;
};
