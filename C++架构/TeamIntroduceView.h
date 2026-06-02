#pragma once

#include "View.h"
#include "button.h"
#include "global.h"

// 团队介绍视图：展示团队信息，支持返回菜单
class TeamIntroduceView : public View {
public:
    TeamIntroduceView() = default;
    ~TeamIntroduceView() = default;

    // 视图生命周期函数（重写父类纯虚函数）
    void enter() override;     // 进入视图：初始化资源
    void update() override;    // 更新视图逻辑
    void draw() override;      // 绘制视图内容
    void handleInput(ExMessage& msg) override;  // 处理输入
    void exit() override;      // 退出视图：释放资源

private:
    // 返回菜单按钮（文本按钮，仿照退出按钮样式）
    TextButton backButton;

};
