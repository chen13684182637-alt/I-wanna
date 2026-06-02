#pragma once
#include<easyx.h>
#include<graphics.h>
#include"view.h"
#include"button.h"


class VictoryView : public View
{
public:
    VictoryView() = default;
    ~VictoryView() = default;
     void enter() override;
     void update()override;
     void draw()override;
     void handleInput(ExMessage& msg)override;
     void exit()override;

private:
    TextButton backButton;
    IMAGE Winview;
};

#define VICTORY_WIDTH 700
#define VICTORY_HEIGHT 350