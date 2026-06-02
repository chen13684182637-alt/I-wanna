#pragma once
#include <graphics.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <utility>



class Player;
using namespace std;
#define PI 3.14159265358979323846f

//enum class ColsliderType { RECTANGLE, TRIANGLE };
enum class TriggeredState { NONE, MOVE };

class Rect {
public:
    int x;          // 矩形左上角X坐标
    int y;          // 矩形左上角Y坐标
    int width;      // 矩形宽度
    int height;     // 矩形高度
    Rect(int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0);
    bool intersects(const Rect& other) const;
    void update(int newX, int newY);
    void draw();
};

class Triangle {
public:
    int x1;         // 三角形顶点1X坐标
    int y1;         // 三角形顶点1Y坐标
    int x2;         // 三角形顶点2X坐标
    int y2;         // 三角形顶点2Y坐标
    int x3;         // 三角形顶点3X坐标
    int y3;         // 三角形顶点3Y坐标
    Triangle(int x1_ = 0, int y1_ = 0, int x2_ = 0, int y2_ = 0, int x3_ = 0, int y3_ = 0);
    bool intersects(const Rect& rect) const;
    void update(int newX1, int newY1, int newX2, int newY2, int newX3, int newY3);
    void draw();
};

