#include "Player.h"
#include "Ground.h"
#include "Shape.h"




// GroundBase类构造函数：初始化地面基础属性
// 参数1（x）：地面X坐标
// 参数2（y）：地面Y坐标
// 参数3（width）：地面宽度
// 参数4（height）：地面高度
// 参数5（visible）：初始可见性（默认true）
GroundBase::GroundBase(int x, int y, int width, int height, bool visible)
    : collisionRect(x, y, width, height), isVisible(visible) {
}

// GroundBase析构函数：空实现
GroundBase::~GroundBase() {}

// GroundBase::update：地面更新（默认无逻辑）
void GroundBase::update() {}

// GroundBase::reset：重置地面
void GroundBase::reset() { isVisible = true; }

// GroundBase::getCollisionRect：获取地面碰撞箱
// 返回值：const Rect&，碰撞箱引用
const Rect& GroundBase::getCollisionRect() const { return collisionRect; }

// GroundBase::getIsVisible：获取地面可见性
// 返回值：bool，true=可见，false=不可见
bool GroundBase::getIsVisible() const { return isVisible; }

// GroundBase::setImage：设置地面贴图
// 参数1（img）：贴图资源
void GroundBase::setImage(const IMAGE& img) { imgGround = img; }

void GroundBase::loadImage(LPCTSTR str, int width, int height)
{
    loadimage(&imgGround, str, width, height);
}

bool GroundBase::getIsVisible() { return isVisible; }
void GroundBase::setIsVisible(bool visible) { isVisible = visible; }


// NormalGround::draw：绘制普通地面
void NormalGround::draw() {
    if (!isVisible) return;

    const int tileW = 32;
    const int tileH = 32;

    // 碰撞箱左上角
    int startX = collisionRect.x;
    int startY = collisionRect.y;

    // 循环填满整个碰撞矩形
    for (int y = 0; y < collisionRect.height; y += tileH) {
        for (int x = 0; x < collisionRect.width; x += tileW) {
            putimage(startX + x, startY + y, &imgGround);
        }
    }
    collisionRect.draw();
}


//NormalGround::类碰撞检测函数：检测ked是否与地面碰撞，并更改kid的移动边界
//参数1（kid）引用游戏主角小孩
bool NormalGround::checkPlayerInteraction(Player& kid)
{
    if (!collisionRect.intersects(kid.getPlayerRectBox())) {
        return false;
    }
    //下落
    if (kid.GetKidY() + kid.GetYsize() >= collisionRect.y
        && kid.GetKidY() + kid.GetYsize() <= collisionRect.y + GROUND_ERROR
        && kid.GetKidVelY() > 0)
    {
        kid.PlayerChangeVelY(0);
        //更改kid的下落边界
        kid.ChangeDownBoundary(collisionRect.y);
    }

    //从左往右撞
    if (kid.GetKidX() + kid.GetXsize() >= collisionRect.x
        && kid.GetKidY() + kid.GetYsize() >= collisionRect.y + GROUND_ERROR
        && kid.GetKidY() + kid.GetYsize() <= (collisionRect.y + collisionRect.height) - GROUND_ERROR
        && kid.getFace() * kid.GetKidVelX() > 0)
    {
        //更改kid的向右移动边界
        kid.ChangeRightBoundary(collisionRect.x);
        kid.PlayerChangeVelX(0);

    }
    //从右往左撞
    if (kid.GetKidX() - kid.GetXsize() <= (collisionRect.x + collisionRect.width)
        && kid.GetKidY() + kid.GetYsize() >= collisionRect.y + GROUND_ERROR
        && kid.GetKidY() + kid.GetYsize() <= (collisionRect.y + collisionRect.height) - GROUND_ERROR
        && kid.getFace() * kid.GetKidVelX() < 0)
    {
        //更改kid的向左移动边界
        kid.ChangeLeftBoundary(collisionRect.x + collisionRect.width);
        kid.PlayerChangeVelX(0);
    }

    //上跳
    if (kid.getPlayerRectBox().y <= (collisionRect.y + collisionRect.height)
        && kid.getPlayerRectBox().y >= collisionRect.y + GROUND_ERROR
        && kid.getPlayerRectBox().x + kid.getPlayerRectBox().width >= collisionRect.x + GROUND_ERROR
        && kid.getPlayerRectBox().x <= collisionRect.x + collisionRect.width - GROUND_ERROR
        && kid.GetKidVelY() < 0)
    {
        //更改kid的向上移动边界
        kid.ChangeUpBoundary(collisionRect.y + collisionRect.height);
        kid.PlayerChangeVelY(0);
    }


    return false;
}

bool NormalGround::isPlayerOnGround(Player& kid)
{
    if (!collisionRect.intersects(kid.getPlayerRectBox())) {
        return false;
    }
    //判断是否在地面上
    if (kid.getPlayerRectBox().y + kid.getPlayerRectBox().height >= collisionRect.y
        && kid.getPlayerRectBox().y + kid.getPlayerRectBox().height <= collisionRect.y + GROUND_ERROR
        && kid.GetKidVelY() >= 0
        && kid.getPlayerRectBox().y <= collisionRect.y
        )
    {
        return true;
    }

    return false;
}

// DisappearingGround类构造函数：初始化可消失地面
// 参数1（x）：地面X坐标
// 参数2（y）：地面Y坐标
// 参数3（width）：地面宽度
// 参数4（height）：地面高度
// 参数5（delay）：延迟消失帧数（默认30）
DisappearingGround::DisappearingGround(int x, int y, int width, int height, int delay)
    : NormalGround(x, y, width, height),
    isTriggered(false),
    disappearDelay(delay),
    currentDelay(0) {
}

//DisappearingGround类消失的地面碰撞检测函数：查看kid是否与DisappearingGround发生碰撞，并处理消失逻辑
//参数1（kid）引用游戏主角小孩
bool DisappearingGround::checkPlayerInteraction(Player& kid) {
    if (!isVisible || isTriggered) return false;
    bool isBlocking = NormalGround::checkPlayerInteraction(kid);
    if (collisionRect.intersects(kid.getPlayerRectBox()) && (kid.GetKidVelY() >= 0)) {
        isTriggered = true; // 被触发了
    }
    return isTriggered;
}

// DisappearingGround::update：更新可消失地面（处理延迟消失）
void DisappearingGround::update() {
    if (isTriggered && isVisible) {
        currentDelay++;
        if (currentDelay >= disappearDelay) {
            isVisible = false;
        }
    }
}

// DisappearingGround::reset：重置可消失地面
void DisappearingGround::reset() {
    NormalGround::reset();
    isTriggered = false;
    currentDelay = 0;
}

// 获取触发状态
bool& DisappearingGround::getIsTriggered() {
    return isTriggered;
}

// 设置触发状态
void DisappearingGround::setIsTriggered(bool triggered) {
    isTriggered = triggered;
}

// 获取消失延迟
int& DisappearingGround::getDisappearDelay() {
    return disappearDelay;
}

// 设置消失延迟
void DisappearingGround::setDisappearDelay(int delay) {
    disappearDelay = delay;
}

// 获取当前延迟计数
int& DisappearingGround::getCurrentDelay() {
    return currentDelay;
}

// 设置当前延迟计数
void DisappearingGround::setCurrentDelay(int delay) {
    currentDelay++;
}






//=======================================================================

// HiddenGround类构造函数：初始化隐藏地面
// 参数1（x）：地面X坐标
// 参数2（y）：地面Y坐标
// 参数3（width）：地面宽度
// 参数4（height）：地面高度
HiddenGround::HiddenGround(int x, int y, int width, int height)
    : NormalGround(x, y, width, height, true), isRevealed(false) {
}

// HiddenGround::draw：绘制隐藏地面
void HiddenGround::draw() {
    if (isRevealed) {
        NormalGround::draw();
    }
}

// HiddenGround::checkPlayerInteraction：检测玩家与地面交互（显示+阻挡）
//参数1（kid）引用游戏主角小孩
bool HiddenGround::checkPlayerInteraction(Player& kid) {
    /*if (!isRevealed && collisionRect.intersects(kid.getPlayerRectBox())) {
        isRevealed = true;
        isVisible = true;
    }
    return isRevealed ? NormalGround::checkPlayerInteraction(kid) : false;*/
    return NormalGround::checkPlayerInteraction(kid);
    
}

// HiddenGround::reset：重置隐藏地面
void HiddenGround::reset() {
    NormalGround::reset();
    isRevealed = false;
    isVisible = false;
}

// 获取显示状态（返回引用，可直接修改）
bool& HiddenGround::getIsRevealed() {
    return isRevealed;
}

// 设置显示状态
void HiddenGround::setIsRevealed(bool revealed) {
    isRevealed = revealed;
}

// SpeedUpGround类构造函数：初始化加速地面
// 参数1（x）：地面X坐标
// 参数2（y）：地面Y坐标
// 参数3（width）：地面宽度
// 参数4（height）：地面高度
// 参数5（boost）：加速力度（默认10）
SpeedUpGround::SpeedUpGround(int x, int y, int width, int height, int boost)
    : NormalGround(x, y, width, height), speedBoost(boost) {
}

// SpeedUpGround::checkPlayerInteraction：检测玩家与地面交互（加速+阻挡）
//参数1（kid）引用游戏主角小孩
bool SpeedUpGround::checkPlayerInteraction(Player& kid) {
    if (!isVisible) return false;

    NormalGround::checkPlayerInteraction(kid);

    if (collisionRect.intersects(kid.getPlayerRectBox()) && kid.GetKidVelY() == 0) {
        kid.PlayerChangeVelX(speedBoost);
    }

    return false;
}


