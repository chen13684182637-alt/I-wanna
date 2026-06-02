//界面管理器，可帮助不同界面之间的转换

#pragma once

#include "view.h"
#include "MenuView.h"
#include "TeamIntroduceView.h"
#include "GameView.h"
#include "DeathView.h"
#include "PauseView.h"
#include "SaveView.h"
#include "SettingView.h"
#include "VictoryView.h"
#include "PlayIntroduceView.h"

class ViewManager
{
public:
    // 视图类型枚举
    enum class ViewType {
        Menu,       // 游戏菜单
        TeamIntroduce,  // 团队介绍
        Pause,       //暂停界面
        Setting,    // 设置界面
        Save,       //存档界面
        Game,       // 游戏界面
        Death,      //死亡界面
        End,         // 结束（退出游戏）
        Victory,
        PlayIntroduce
    };

public:

    ViewManager() = default;
    ~ViewManager() {
        // 释放所有视图资源
        if (current_view) {
            delete current_view;
        }
    }
    //设置当前状态
    void set_current_view(View* view) {
        current_view = view;
        current_view->enter();
    }



    // 切换视图：根据类型创建对应视图
    void switch_to(ViewType type) {
        // 释放旧视图
        if (current_view) {
            current_view->exit();
            delete current_view;
            current_view = nullptr;
        }

        switch (type) {
        case ViewType::Menu:
            current_view = new MenuView();
            break;
        case ViewType::TeamIntroduce:
            current_view = new TeamIntroduceView();
            break;
        case ViewType::Game:
            current_view = new GameView();
            break;
        case ViewType::Pause:
            current_view = new PauseView();
            break;
        case ViewType::Death:
            current_view = new DeathView();
            break;
        case ViewType::Setting:
            current_view = new SettingView();
            break;
        case ViewType::Save:
            current_view = new SaveView();
            break;
        case ViewType::End:
            exit(0);
            break;
        case ViewType::Victory:
            current_view = new VictoryView();
            break;
        case ViewType::PlayIntroduce:
            current_view = new PlayIntroduceView();
            break;
        default:
            break;
        }

        // 进入新视图
        if (current_view) {
            current_view->enter();
        }
        
    }


    // 委托给当前视图的方法
    void update() {
        if (current_view) current_view->update();
    }
    void draw() {
        if (current_view) current_view->draw();
    }
    void handleInput(ExMessage& msg) {
        if (current_view) current_view->handleInput(msg);
    }



private:
    View* current_view = nullptr; // 当前活动视图
};

// 全局视图管理器
extern ViewManager view_manager;

