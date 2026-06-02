#pragma once
#include "Shape.h"

class BaseTrap {
protected:
    IMAGE trapImg;           // 陷阱贴图资源
    bool isactive;           // 激活状态（是否参与碰撞击杀）
    Rect imgRect;
    Rect initialImgRect;            // 贴图初始位置（重置用）

public:
    // 构造
    ~BaseTrap() = default;
    // 析构
    BaseTrap();

    BaseTrap(Rect rec, bool isactive);

    // 是否为激活状态
    bool isActive() const;

    // 检查与玩家碰撞 (虚函数)
    virtual bool checkCollision(const Rect& playerRect) const;

    // 设置陷阱位置 (虚函数)
    virtual void setPosition(int x, int y);

    // 获取陷阱位置 (虚函数)
    virtual pair<int, int> getPosition() const;

    void loadImage(LPCTSTR str, int width, int height);

    // 设置陷阱贴图
    void setImage(const IMAGE& img);

    // 设置激活状态
    void setActive(bool active);

    //void draw();



    // 获取/设置贴图区域
    Rect& getImgRect();
    void setImgRect(const Rect& rect);

    // 获取/设置初始贴图区域
    Rect& getInitialImgRect();
    void setInitialImgRect(const Rect& rect);

    // 获取/设置激活状态
    bool& getIsActive();
    void setIsActive(bool active);

    // 获取/设置贴图资源
    IMAGE& getTrapImg();
    void setTrapImg(const IMAGE& img);

};


class RectangleTrap : public BaseTrap {
protected:
    Rect collisionRect;      // 矩形碰撞箱
    Rect initialCollisionRect; // 矩形碰撞箱初始状态（重置用）

public:
    // 构造函数 : 设置 碰撞箱 与 贴图区域
    RectangleTrap(Rect collision, Rect img);

    // 检测与玩家碰撞
    bool checkCollision(const Rect& playerRect) const;

    // 带碰撞箱的绘制
    void draw();

    // 设置位置 : 陷阱的 贴图 位置
    void setPosition(int x, int y);

    // 获取位置 : 陷阱贴图的左上角坐标
    pair<int, int> getPosition() const;

    // 接口设计
    // 获取碰撞箱（返回引用，可直接修改）
    Rect& getCollisionRect();
    void setCollisionRect(const Rect& rect);

    // 获取初始碰撞箱（返回引用，可直接修改）
    Rect& getInitialCollisionRect();
    void setInitialCollisionRect(const Rect& rect);
};


#define TRIANGLE_DIRECT_UP 1
#define TRIANGLE_DIRECT_LEFT 2
#define TRIANGLE_DIRECT_DOWN 3
#define TRIANGLE_DIRECT_RIGHT 4

class TriangleTrap : public BaseTrap {
protected:
    Triangle collisionTriangle;     // 三角形碰撞箱
    Triangle initialCollisionTriangle; // 三角形碰撞箱初始状态（重置用））
    int direction;
public:

    TriangleTrap(Rect img, int dir);

    // 构造函数 : 设置 碰撞箱 与 贴图区域
    TriangleTrap(Triangle collision, Rect img, int dir);

    // 三角-矩形碰撞箱检测 (主要是检测与玩家的重叠情况)
    bool checkCollision(const Rect& playerRect) const;

    void draw();

    // 设置位置 : 设置 imgRect 左上角坐标
    void setPosition(int x, int y);

    // 获取位置 : 获取 imgRect 左上角坐标
    pair<int, int> getPosition() const;


    // 获取三角形碰撞箱（返回引用，可直接修改）
    Triangle& getCollisionTriangle();
    void setCollisionTriangle(const Triangle& triangle);

    // 获取初始三角形碰撞箱（返回引用，可直接修改）
    Triangle& getInitialCollisionTriangle();
    void setInitialCollisionTriangle(const Triangle& triangle);

    int& getDirection();
    void setDirection(const int direct);
};


// 可触发的三角形陷阱
class TriggerableTriangleTrap : public TriangleTrap {
public:
    Rect triggerArea;           // 触发区域（玩家进入后激活陷阱）
    bool isTriggered;           // 触发状态（是否已被玩家触发）
    TriggeredState triggeredState; // 触发后状态（移动/静止）
    int moveSpeedX;             // 水平移动速度（像素/帧） : 
    int moveSpeedY;             // 垂直移动速度（像素/帧）
    int moveStep;               // 当前移动步数（控制移动进度）
    bool isTriggerable;         // 玩家进入 triggerArea 时是否可以触发陷阱移动.

    // 初始化 : 碰撞箱, 贴图位置, 触发区域
    TriggerableTriangleTrap(Triangle collision, Rect img, Rect trigger, int moveSpeedX, int moveSpeedY, int dir);
    TriggerableTriangleTrap(Triangle collision, Rect img, Rect trigger);

    // 检查玩家是否触发陷阱
    bool checkTrigger(const Rect& playerRect);

    // 重置陷阱状态
    void reset();

    // 更新陷阱位置
    void update();

    // 陷阱是否超出窗口
    bool isOutOfWindow() const;

    // 获取触发区域 Rect
    const Rect& getTriggerArea() const;

    // 获取/修改速度(引用)
    int& getSpeedX();
    int& getSpeedY();


    //重构图像绘制
    void draw();

    // 获取/设置触发状态 isTriggered
    bool& getIsTriggered();
    void setIsTriggered(bool triggered);

    // 获取/设置触发后状态 TriggeredState
    TriggeredState& getTriggeredState();
    void setTriggeredState(TriggeredState state);

    // 获取/设置是否可触发 IsTriggerable
    bool& getIsTriggerable();
    void setIsTriggerable(bool triggerable);
};


// 可触发的矩形陷阱
class TriggerableRectangleTrap : public RectangleTrap {
public:
    Rect triggerArea;           // 触发区域（玩家进入后激活陷阱）
    bool isTriggered;           // 触发状态（是否已被玩家触发）
    TriggeredState triggeredState; // 触发后状态（移动/静止）
    int moveSpeedX;             // 水平移动速度（像素/帧）
    int moveSpeedY;             // 垂直移动速度（像素/帧）
    int moveStep;               // 当前移动步数（控制移动进度）
    bool isTriggerable;         // 玩家进入 triggerArea 时是否可以触发陷阱移动.

    // 三角陷阱
    TriggerableRectangleTrap(Rect collision, Rect img, Rect trigger, int moveSpeedX, int moveSpeedY);

    // 检查玩家是否触发陷阱
    bool checkTrigger(const Rect& playerRect);

    // 重置陷阱状态
    void reset();

    // 更新陷阱位置
    void update();

    // 陷阱是否超出窗口
    bool isOutOfWindow() const;

    // 获取触发区域 Rect
    const Rect& getTriggerArea() const;

    // 获取/修改速度(引用)
    int& getSpeedX();
    int& getSpeedY();



    //重构图像绘制
    void draw();

    // 接口补充
    // 
    // 获取/设置触发状态 isTriggered
    bool& getIsTriggered();
    void setIsTriggered(bool triggered);

    // 获取/设置触发后状态 TriggeredState
    TriggeredState& getTriggeredState();
    void setTriggeredState(TriggeredState state);

    // 获取/设置是否可触发 IsTriggerable
    bool& getIsTriggerable();
    void setIsTriggerable(bool triggerable);
};
