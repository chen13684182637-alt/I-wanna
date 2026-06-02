#pragma once
#include"Shape.h"
class Player;
class GroundBase {
protected:
    IMAGE imgGround;        // 地面贴图资源
    Rect collisionRect;     // 地面碰撞箱
    bool isVisible;         // 可见状态（是否参与绘制和碰撞）

public:
    // 构造函数
    GroundBase(int x=0, int y = 0, int width = 0, int height=0, bool visible = true);


    // 析构函数
    virtual ~GroundBase();

    // 绘制地面图片
    virtual void draw() = 0;

    // 检测玩家是否与地面接触，以此更改玩家的移动边界
    virtual bool checkPlayerInteraction(Player& kid) = 0;

    //判断玩家是否在地面上
    virtual bool isPlayerOnGround(Player& kid)=0;

    // 更新陷阱位置
    virtual void update();

    // 重置地面的位置和状态
    virtual void reset();

    // 获取地面的碰撞箱
    const Rect& getCollisionRect() const;

    // 获取地面的isVisible是否可见/参与碰撞
    bool getIsVisible() const;

    // 从文件加载图片的接口
    void loadImage(LPCTSTR str, int width, int height);

    // 设置陷阱图片变量 imgGround
    void setImage(const IMAGE& img);

    bool getIsVisible();

    void setIsVisible(bool visible);
};

class NormalGround : public GroundBase {
public:
    // 自动继承基类构造函数
    using GroundBase::GroundBase;

    // 绘制地面 (覆写)
    void draw() override;

    // 检测玩家是否与地面接触，以此更改玩家的移动边界
    bool checkPlayerInteraction(Player& kid) override;

    // 判断玩家是否站在地面上
    bool isPlayerOnGround(Player& kid);
};

class DisappearingGround : public NormalGround {
private:
    bool isTriggered;       // 触发状态（是否已被玩家踩中）
    int disappearDelay;     // 延迟消失帧数（触发后多久消失）
    int currentDelay;       // 当前延迟计数（已过去的帧数）

public:
    // 构造函数
    DisappearingGround(int x, int y, int width, int height, int delay = 30);

    // 检查玩家是否接触, 接触则消失
    bool checkPlayerInteraction(Player& kid) override;

    //判断玩家是否在地面上
    //bool isPlayerOnGround(Player& kid);

    // 更新陷阱状态
    void update() override;

    // 重置陷阱状态 (逻辑比较简单, 直接改属性就行)
    void reset() override;

    // 获取/设置触发状态
    bool& getIsTriggered();
    void setIsTriggered(bool triggered);

    // 获取/设置消失延迟
    int& getDisappearDelay();
    void setDisappearDelay(int delay);

    // 获取/设置当前延迟计数
    int& getCurrentDelay();
    void setCurrentDelay(int delay);
};

class HiddenGround : public NormalGround {
private:
    bool isRevealed;        // 显示状态（是否已被玩家碰撞显示）

public:

    // 构造函数
    HiddenGround(int x, int y, int width, int height);

    // 绘制隐藏地面 (接触后)
    void draw() override;

    // 检查玩家是否接触, 接触产生阻挡效果
    bool checkPlayerInteraction(Player& kid) override;

    //判断玩家是否在地面上
    //bool isPlayerOnGround(Player& kid);

    // 重置陷阱状态. (isRevealed = false;)
    void reset() override;

    // 获取/设置显示状态
    bool& getIsRevealed();
    void setIsRevealed(bool revealed);
};

class SpeedUpGround : public NormalGround {
private:
    int speedBoost;         // 加速力度（玩家站在上面时的水平速度）

public:
    // 构造函数
    SpeedUpGround(int x, int y, int width, int height, int boost = 10);
    bool checkPlayerInteraction(Player& kid) override;

    //判断玩家是否在地面上
    //bool isPlayerOnGround(Player& kid);
};


//地面误差范围，如果没有，在下落过程中容易直接穿过地面坠落虚空
#define GROUND_ERROR 15

//横向误差范围，如果没有，边角容易穿模 
#define LEN_ERROR 25