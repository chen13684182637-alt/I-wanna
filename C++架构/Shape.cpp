#include "Shape.h"



bool CollBoxDrawFlag = 0;

// Rect类构造函数：初始化矩形碰撞箱
// 参数1（x_）：矩形左上角X坐标
// 参数2（y_）：矩形左上角Y坐标
// 参数3（w_）：矩形宽度
// 参数4（h_）：矩形高度
Rect::Rect(int x_, int y_, int w_, int h_) : x(x_), y(y_), width(w_), height(h_) {}

// Rect::intersects：检测与另一个矩形是否重叠
// 参数1（other）：目标矩形
// 返回值：bool，true=重叠，false=不重叠
bool Rect::intersects(const Rect& other) const {
    return (x < other.x + other.width) && (x + width > other.x) &&
        (y < other.y + other.height) && (y + height > other.y);
}


//更新碰撞箱
void Rect::update(int newX, int newY)
{
    x = newX;
    y = newY;
}

//更新碰撞箱
void Rect::draw()
{
    if (CollBoxDrawFlag) rectangle(x, y, x + width, y + height);
}

// Triangle类构造函数：初始化三角形顶点
// 参数1（x1_）：顶点1X坐标
// 参数2（y1_）：顶点1Y坐标
// 参数3（x2_）：顶点2X坐标
// 参数4（y2_）：顶点2Y坐标
// 参数5（x3_）：顶点3X坐标
// 参数6（y3_）：顶点3Y坐标
Triangle::Triangle(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_)
    : x1(x1_), y1(y1_), x2(x2_), y2(y2_), x3(x3_), y3(y3_) {
}

// Triangle::intersects：检测与矩形是否重叠
// 参数1（rect）：目标矩形
// 返回值：bool，true=重叠，false=不重叠
bool Triangle::intersects(const Rect& rect) const {
    auto inRect = [&](int x, int y) {
        return x >= rect.x && x <= rect.x + rect.width &&
            y >= rect.y && y <= rect.y + rect.height;
        };
    if (inRect(x1, y1) || inRect(x2, y2) || inRect(x3, y3)) return true;

    auto inTriangle = [&](int x, int y) {
        int d1 = (x - x2) * (y1 - y2) - (x1 - x2) * (y - y2);
        int d2 = (x - x3) * (y2 - y3) - (x2 - x3) * (y - y3);
        int d3 = (x - x1) * (y3 - y1) - (x3 - x1) * (y - y1);
        bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
        return !(hasNeg && hasPos);
        };

    int rectPts[4][2] = {
        {rect.x, rect.y}, {rect.x + rect.width, rect.y},
        {rect.x + rect.width, rect.y + rect.height}, {rect.x, rect.y + rect.height}
    };
    for (auto& p : rectPts) if (inTriangle(p[0], p[1])) return true;

    return false;
}

//更新碰撞箱
void  Triangle::update(int newX1, int newY1, int newX2, int newY2, int newX3, int newY3 )
{
    x1 = newX1;
    y1 = newY1;
    x2 = newX2;
    y2 = newY2;
    x3 = newX3;
    y3 = newY3;
}

//绘制碰撞箱
void  Triangle::draw()
{
    POINT pentagonPoints[] =
    {
        {x1,y1},
        {x2,y2},
        {x3,y3}
    };
    if (CollBoxDrawFlag) polygon(pentagonPoints, 3);
}