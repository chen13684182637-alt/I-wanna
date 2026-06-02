#include "Point.h"
#include "global.h"
#include "utils.h"

IMAGE imgSavedPoint;
IMAGE imgUnsavedPoint;

//=================================================================

// class SavePoint

//=================================================================

// 构造函数 : 初始化碰撞箱, 引用图片, 
// 参数:
	// x, y : 矩形碰撞箱左上角坐标
	// width, height : 矩形碰撞箱的 宽, 高
SavePoint::SavePoint(int x, int y, int width, int height)
{
	collisionRect = Rect(x, y, width, height);
	setImages(imgUnsavedPoint, imgSavedPoint);		// 全局变量
	isSaved = false;
}

// 析构函数 : 
SavePoint::~SavePoint() {}


// 设置图片 :		// ??? 是否会有性能问题
void SavePoint::setImages(const IMAGE& unsavedImg, const IMAGE& savedImg)
{
	imgUnsaved = unsavedImg;		//结构体赋值, 但是结构体里面的指针还是同一个
	imgSaved = savedImg;
}

void SavePoint::loadUnsavedImage(LPCTSTR str, int width, int height)
{
	loadimage(&imgUnsaved, str, width, height);
}

void SavePoint::loadSavedImage(LPCTSTR str, int width, int height)
{
	loadimage(&imgSaved, str, width, height);
}

// 绘制存档点
void SavePoint::draw(bool isUnsaved = 1)
{
	if (isUnsaved)
	putimage_new(collisionRect.x, collisionRect.y, &imgUnsaved);
	else
	putimage_new(collisionRect.x, collisionRect.y, &imgSaved);
	
	collisionRect.draw();
}

// 检测是否与玩家碰撞
bool SavePoint::checkPlayerCollision() const
{
	// 玩家
	return collisionRect.intersects(kid.getPlayerRectBox());
}


// 地图重置
void SavePoint::reset()
{

}

// 获取 isSaved 值 (可修改)
bool& SavePoint::getisSaved() { return isSaved; }

// 获取碰撞箱 (可修改)
Rect& SavePoint::getCollisionRect() { return collisionRect; }

void SavePoint::setIsSaved(bool set) { isSaved = set; }



//=================================================================

// class EndPoint

//=================================================================

// 构造函数 : 设置碰撞箱, 图片, 初始化到达状态
EndPoint::EndPoint(int x, int y, int width, int height)
{
	collisionRect = Rect(x, y, width, height);
	isReached = false;
}

// 析构函数
EndPoint::~EndPoint() {}

// 设置图片
void EndPoint::setImage(const IMAGE& img)
{
	imgEnd = img;	// 性能问题?
}

void EndPoint::loadImage(LPCTSTR str, int width, int height)
{
	loadimage(&imgEnd, str, width, height);
}

// 绘制终点 : 根据 collisionRect 绘制图片
void EndPoint::draw() {
	putimage_new(collisionRect.x, collisionRect.y, &imgEnd);
}

// 玩家是否到达当前终点对象处
bool EndPoint::checkPlayerReach()
{
	return collisionRect.intersects(kid.getPlayerRectBox());
}

// 返回当前是否为最后一关 (这个函数好像在 Map 地图中比较好控制, 待定)
bool EndPoint::isEndReached()const
{
	return 0;
}

// 重置关卡状态
void EndPoint::reset()
{

}

// 获取碰撞箱
const Rect& EndPoint::getCollisionRect()
{
	return collisionRect;
}

void EndPoint::setIsReached(bool setReached)
{
	isReached = setReached;
}

bool EndPoint::getIsReached() { return isReached; }