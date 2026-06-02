//功能函数，加载资源，绘制，判定等等

#pragma once
#include <graphics.h>
#include <windows.h> 
#include "global.h"
#include"Player.h"



#pragma comment(lib, "Msimg32.lib")



// 加载所有资源
void loadAllResources();




/* 图像绘制工具函数
*  功能：绘制带Alpha通道的图像（支持透明/半透明效果），解决EasyX默认putimage不支持透明度的问题
*  参数：
*    x, y - 目标绘制区域的左上角坐标
*    img - 指向IMAGE对象的指针，存储待绘制的图像（需包含Alpha通道，如PNG格式）
*/
void putimage_new(int x, int y, IMAGE* img);


/*
    功能: 判断目标坐标是否在指定矩形区域内（不包含区域边界）
    参数:
        x, y: 待判断的目标坐标
        l: 矩形区域的左边界坐标
        t: 矩形区域的上边界坐标
        r: 矩形区域的右边界坐标
        b: 矩形区域的下边界坐标
    返回值: 若坐标在区域内返回true，否则返回false
*/

bool inArea(int x, int y, int l, int t, int r, int b);


Triangle Rect2Tri(Rect);

void setAudio(int vol);