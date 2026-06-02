#pragma once
#include "Trap.h"
#include "global.h"
#include "utils.h"

// =================== BaseTrap ===================
BaseTrap::BaseTrap()
{

}

BaseTrap::BaseTrap(Rect rec, bool active = true)
{
    imgRect = rec;
    isactive = active;
}

// 设置激活状态s
void BaseTrap::setActive(bool active)
{
    isactive = active;
}



//绘制
//void BaseTrap::draw() {
//    if (!isactive) {
//        return;
//    }
//    putimage_new(imgRect.x, imgRect.y, &trapImg);
//}

void BaseTrap::loadImage(LPCTSTR str, int width, int height)
{
    loadimage(&trapImg, str, width, height);
}


// 是否为激活状态
bool BaseTrap::isActive() const
{
    return isactive;
}

// 检查与玩家碰撞
bool BaseTrap::checkCollision(const Rect& playerRect) const
{
    return false;
}

// 设置位置
void BaseTrap::setPosition(int x, int y)
{
    // TODO: 设置陷阱位置
}

// 获取位置
std::pair<int, int> BaseTrap::getPosition() const
{
    // TODO: 返回陷阱位置
    return { 0, 0 };
}

// 设置贴图
void BaseTrap::setImage(const IMAGE& img)
{
    // TODO: 设置 trapImg
    trapImg = img;
}


// 获取贴图区域
Rect& BaseTrap::getImgRect() {
    return imgRect;
}

// 设置贴图区域
void BaseTrap::setImgRect(const Rect& rect) {
    imgRect = rect;
}

// 获取初始贴图区域
Rect& BaseTrap::getInitialImgRect() {
    return initialImgRect;
}

// 设置初始贴图区域
void BaseTrap::setInitialImgRect(const Rect& rect) {
    initialImgRect = rect;
}

// 获取激活状态（返回引用，可直接修改）
bool& BaseTrap::getIsActive() {
    return isactive;
}

// 设置激活状态
void BaseTrap::setIsActive(bool active) {
    isactive = active;
}

// 获取贴图资源
IMAGE& BaseTrap::getTrapImg() {
    return trapImg;
}

// 设置贴图资源
void BaseTrap::setTrapImg(const IMAGE& img) {
    trapImg = img;
}


// =================== RectangleTrap ===================

// 构造函数
RectangleTrap::RectangleTrap(Rect collision, Rect img)
    : collisionRect(collision), initialCollisionRect(collision)
{
    this->isactive = true;
}

// 检测与玩家碰撞
bool RectangleTrap::checkCollision(const Rect& playerRect) const
{
    if (!isactive) {
        return false;
    }
    return collisionRect.intersects(playerRect);
}

void RectangleTrap::draw()
{
    if (!isactive) {
        return;
    }
    putimage_new(imgRect.x, imgRect.y, &trapImg);
    collisionRect.draw();
}

// 设置位置
void RectangleTrap::setPosition(int x, int y)
{
    collisionRect.x = x;
    collisionRect.y = y;
    imgRect.x = x;
    imgRect.y = y;
}

// 获取位置
std::pair<int, int> RectangleTrap::getPosition() const
{
    return make_pair(collisionRect.x, collisionRect.y);
}

// 获取碰撞箱
Rect& RectangleTrap::getCollisionRect() {
    return collisionRect;
}

// 设置碰撞箱
void RectangleTrap::setCollisionRect(const Rect& rect) {
    collisionRect = rect;
}

// 获取初始碰撞箱
Rect& RectangleTrap::getInitialCollisionRect() {
    return initialCollisionRect;
}

// 设置初始碰撞箱
void RectangleTrap::setInitialCollisionRect(const Rect& rect) {
    initialCollisionRect = rect;
}


// =================== TriangleTrap ===================

// 便捷使用的构造函数
TriangleTrap::TriangleTrap(Rect img, int dir = 1) : TriangleTrap(Rect2Tri(img), img, dir) // UP
{

}



// 构造函数
TriangleTrap::TriangleTrap(Triangle collision, Rect img, int dir = 1)
    : collisionTriangle(collision), initialCollisionTriangle(collision), direction(dir),
    BaseTrap(img, true)
{
    this->isactive = true;

}

// 三角-矩形碰撞检测
bool TriangleTrap::checkCollision(const Rect& playerRect) const
{
    if (!isactive) {
        return false;
    }
    return collisionTriangle.intersects(playerRect);
}

void TriangleTrap::draw()
{
    if (!isactive) {
        return;
    }
    putimage_new(imgRect.x, imgRect.y, &trapImg);
    collisionTriangle.draw();
}

// 设置位置
void TriangleTrap::setPosition(int x, int y)
{
    int dx = x - collisionTriangle.x1;
    int dy = y - collisionTriangle.y1;
    collisionTriangle.x1 = x;
    collisionTriangle.y1 = y;
    collisionTriangle.x2 += dx;
    collisionTriangle.y2 += dy;
    collisionTriangle.x3 += dx;
    collisionTriangle.y3 += dy;
    imgRect.x += dx;
    imgRect.y += dy;
}

// 获取位置
std::pair<int, int> TriangleTrap::getPosition() const
{
    return make_pair(collisionTriangle.x1, collisionTriangle.y1);;
}

// 获取三角形碰撞箱
Triangle& TriangleTrap::getCollisionTriangle() {
    return collisionTriangle;
}

// 设置三角形碰撞箱
void TriangleTrap::setCollisionTriangle(const Triangle& triangle) {
    collisionTriangle = triangle;
}

// 获取初始三角形碰撞箱
Triangle& TriangleTrap::getInitialCollisionTriangle() {
    return initialCollisionTriangle;
}

// 设置初始三角形碰撞箱
void TriangleTrap::setInitialCollisionTriangle(const Triangle& triangle) {
    initialCollisionTriangle = triangle;
}

// 获取方向（返回引用，可直接修改）
int& TriangleTrap::getDirection() {
    return direction;
}

// 设置方向
void TriangleTrap::setDirection(const int direct) {
    direction = direct;
}


// =================== TriggerableTriangleTrap ===================

// 构造函数
TriggerableTriangleTrap::TriggerableTriangleTrap(Triangle collision, Rect img, Rect trigger, int moveSpeedX, int moveSpeedY, int dir)
    : TriangleTrap(collision, img, dir), triggerArea(trigger), isTriggered(false),
    moveSpeedX(moveSpeedX), moveSpeedY(moveSpeedY), moveStep(0), isTriggerable(true), triggeredState(TriggeredState::NONE)
{
}

// 构造函数
TriggerableTriangleTrap::TriggerableTriangleTrap(Triangle collision, Rect img, Rect trigger)
    : TriangleTrap(collision, img, 1), triggerArea(trigger), isTriggered(false),
    moveSpeedX(0), moveSpeedY(0), moveStep(0), isTriggerable(true), triggeredState(TriggeredState::NONE)
{
}

// 检查玩家是否触发陷阱
bool TriggerableTriangleTrap::checkTrigger(const Rect& playerRect)
{
    if (isTriggered) {
        return true;
    }
    if (triggerArea.intersects(playerRect)) {
        isTriggered = true;
        return true;
    }
    return false;
}

// 重置陷阱状态
void TriggerableTriangleTrap::reset()
{
    isTriggered = false;
    moveStep = 0;
    setPosition(initialCollisionTriangle.x1, initialCollisionTriangle.y1);
    isactive = true;
}

// 更新陷阱位置
void TriggerableTriangleTrap::update()
{
    if (!isActive()) {
        return;
    }
    if (triggeredState == TriggeredState::MOVE) {
        setPosition(collisionTriangle.x1 + moveSpeedX, collisionTriangle.y1 + moveSpeedY);
    }
}

// 陷阱是否超出窗口
bool TriggerableTriangleTrap::isOutOfWindow() const
{
    return collisionTriangle.x1 > WINDOW_WIDTH || collisionTriangle.y1 > WINDOW_HEIGHT;
}

// 获取触发区域
const Rect& TriggerableTriangleTrap::getTriggerArea() const
{
    return triggerArea;
}

// 获取/修改速度
int& TriggerableTriangleTrap::getSpeedX()
{
    return moveSpeedX;
}

int& TriggerableTriangleTrap::getSpeedY()
{
    return moveSpeedY;
}



// 获取触发状态（返回引用）
bool& TriggerableTriangleTrap::getIsTriggered() {
    return isTriggered;
}

// 设置触发状态
void TriggerableTriangleTrap::setIsTriggered(bool triggered) {
    isTriggered = triggered;
}

// 获取触发后状态（返回引用）
TriggeredState& TriggerableTriangleTrap::getTriggeredState() {
    return triggeredState;
}

// 设置触发后状态
void TriggerableTriangleTrap::setTriggeredState(TriggeredState state) {
    triggeredState = state;
}

// 获取是否可触发（返回引用）
bool& TriggerableTriangleTrap::getIsTriggerable() {
    return isTriggerable;
}

// 设置是否可触发
void TriggerableTriangleTrap::setIsTriggerable(bool triggerable) {
    isTriggerable = triggerable;
}






// =================== TriggerableRectangleTrap ===================

// 构造函数
TriggerableRectangleTrap::TriggerableRectangleTrap(Rect collision, Rect img, Rect trigger, int moveSpeedX = 0, int moveSpeedY = 0)
    : RectangleTrap(collision, img), triggerArea(trigger), isTriggered(false),
    moveSpeedX(moveSpeedX), moveSpeedY(moveSpeedY), moveStep(0), isTriggerable(true), triggeredState(TriggeredState::NONE)
{
    // TODO: 初始化触发状态
}

// 检查玩家是否触发陷阱
bool TriggerableRectangleTrap::checkTrigger(const Rect& playerRect)
{
    if (isTriggered) {
        return true;
    }
    if (triggerArea.intersects(playerRect)) {
        isTriggered = true;
        return true;
    }
    return false;
}

// 重置陷阱状态
void TriggerableRectangleTrap::reset()
{
    isTriggered = false;
    moveStep = 0;
    setPosition(initialCollisionRect.x, initialCollisionRect.y);
    isactive = true;
}

// 更新陷阱位置
void TriggerableRectangleTrap::update()
{
    if (!isActive()) {
        return;
    }
    if (triggeredState == TriggeredState::MOVE) {
        setPosition(collisionRect.x + moveSpeedX, collisionRect.y + moveSpeedY);
    }
}

// 陷阱是否超出窗口
bool TriggerableRectangleTrap::isOutOfWindow() const
{
    // TODO: 判断是否超出窗口
    return collisionRect.x > WINDOW_WIDTH || collisionRect.y > WINDOW_HEIGHT;;
}

// 获取触发区域
const Rect& TriggerableRectangleTrap::getTriggerArea() const
{
    return triggerArea;
}

// 获取/修改速度
int& TriggerableRectangleTrap::getSpeedX()
{
    return moveSpeedX;
}

int& TriggerableRectangleTrap::getSpeedY()
{
    return moveSpeedY;
}


void TriggerableRectangleTrap::draw() {
    if (!isactive) {
        return;
    }
    putimage_new(imgRect.x, imgRect.y, &trapImg);
}

void TriggerableTriangleTrap::draw() {
    if (!isactive) {
        return;
    }
    putimage_new(imgRect.x, imgRect.y, &trapImg);
}

// 获取触发状态（返回引用）
bool& TriggerableRectangleTrap::getIsTriggered() {
    return isTriggered;
}

// 设置触发状态
void TriggerableRectangleTrap::setIsTriggered(bool triggered) {
    isTriggered = triggered;
}

// 获取触发后状态（返回引用）
TriggeredState& TriggerableRectangleTrap::getTriggeredState() {
    return triggeredState;
}

// 设置触发后状态
void TriggerableRectangleTrap::setTriggeredState(TriggeredState state) {
    triggeredState = state;
}

// 获取是否可触发（返回引用）
bool& TriggerableRectangleTrap::getIsTriggerable() {
    return isTriggerable;
}

// 设置是否可触发
void TriggerableRectangleTrap::setIsTriggerable(bool triggerable) {
    isTriggerable = triggerable;
}