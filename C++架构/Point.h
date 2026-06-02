#pragma once

#include "Shape.h"


class SavePoint {
private:
    /*/ ===========================================     旧版
    Rect collisionRect;     // 存档点碰撞箱
    IMAGE imgUnsaved;       // 未存档状态贴图
    IMAGE imgSaved;         // 已存档状态贴图
    bool isSaved;           // 存档状态（是否已存档）
    bool isTriggered;       // 触发状态（是否已被玩家触发）       
    /======================================== */ 


    Rect collisionRect;	// 矩形碰撞箱
    IMAGE imgUnsaved; 	// 存档未触发图片
    IMAGE imgSaved;		// 存档已触发图片
    bool isSaved;	    	// 玩家当前是否记录在这个存档?

public:
    // 构造函数
    SavePoint(int x=0, int y=0, int width=0, int height=0);

    // 析构
    ~SavePoint();

    // 设置图片 (从 global.h 中引用)
    void setImages(const IMAGE& unsavedImg, const IMAGE& savedImg);

    void loadUnsavedImage(LPCTSTR str, int width, int height);
    void loadSavedImage(LPCTSTR str, int width, int height);
    
    

    // 绘制存档点 (根据 collisionRect 中的坐标)
    void draw(bool isUnsaved);

    // 检测是否与玩家碰撞
        //bool checkPlayerCollision(const Rect& playerRect) const;
    bool checkPlayerCollision()const;

    // 地图重置
    void reset();

    // 获取isSaved值
    bool& getisSaved();

    void setIsSaved(bool);

    // 获取碰撞箱 (可修改)
    Rect& getCollisionRect();
};



class EndPoint {
private:
    Rect collisionRect;     // 终点碰撞箱
    IMAGE imgEnd;           // 终点贴图
    bool isReached;         // 到达状态（玩家是否已到达）

public:
    EndPoint(int x, int y, int width, int height);
    ~EndPoint();

    
    // 设置图片状态
    void setImage(const IMAGE& img);

    void loadImage(LPCTSTR str, int width, int height);


    // 绘制终点 (用传送点表示)
    void draw();

    // 检查是否与玩家碰撞
    bool checkPlayerReach();

    // 检查当前地图是不是最后一关
    bool isEndReached() const;

    bool getIsReached();

    void setIsReached(bool setReached);
    
    // 重置
    void reset();

    // 获取地图碰撞箱
    const Rect& getCollisionRect();
};

