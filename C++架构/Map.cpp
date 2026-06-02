#pragma once
#include <graphics.h>
#include "Map.h"
#include "global.h"
#include "viewManager.h"
using namespace std;

IMAGE imgSpikeUp;
IMAGE imgSpikeLeft;
IMAGE imgSpikeDown;
IMAGE imgSpikeRight;

// 苹果
IMAGE imgApple;

// 地面图片
IMAGE imgGround;

// 终点
IMAGE imgEndPoint;

extern ViewManager view_manager;

stack<SavePoint>savePointStack;//存档点工具栈

bool PlayerSpawnInitFlag=0;

//1.构造函数
Map::Map(IMAGE _bgImage, string _bgPath, bool _isMapLoaded, int _birthX, int _birthY)
    :
    bgImage(_bgImage),
    bgPath(_bgPath),
    isMapLoaded(_isMapLoaded),
    birthX(_birthX),
    birthY(_birthY)
{
}

//1.构造函数
Map::Map(IMAGE bgImage, string bgPath, bool isMapLoaded, int birthX, int birthY,
    vector<EndPoint>& ep,
    vector<SavePoint>& sp,
    vector<NormalGround>& ng,
    vector<DisappearingGround>& dg,
    vector<HiddenGround>& hg,
    vector<SpeedUpGround>& sg,
    vector<RectangleTrap>& rt,
    vector<TriangleTrap>& tt,
    vector<TriggerableRectangleTrap>& trt,
    vector<TriggerableTriangleTrap>& ttt) :
    bgImage(bgImage), bgPath(bgPath), isMapLoaded(isMapLoaded), birthX(birthX), birthY(birthY),
    ep(ep), sp(sp), ng(ng), dg(dg), hg(hg), sg(sg), rt(rt), tt(tt), trt(trt) {
}



//2.析构函数：释放所有动态资源（调用资源释放函数）
Map::~Map() { releaseMapResources(); }



//3.加载地图资源（加载每个实体对象的图片）
void Map::loadMap()
{
    //1. 释放已有资源（防止重复加载导致内存泄漏）
    releaseMapResources();

    //2. 加载背景图
    //wstring tempp = StringToWString(bgPath);
    string tempp = bgPath;
    loadimage(&bgImage, tempp.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, true);

    //3.加载终点
    if (!ep.empty())
    {
        for (auto& endPoint : ep)
        {
            int w = endPoint.getCollisionRect().width;
            int h = endPoint.getCollisionRect().height;
            // endPoint.setImage(imgEndPoint);
            endPoint.loadImage(_T(END_POINT_PATH), 32, 32);
        }
    }

    // 4. 加载存档点图片（未激活/已激活）
    if (!sp.empty())
    {
        for (auto& savePoint : sp)
        {
            int w = savePoint.getCollisionRect().width;
            int h = savePoint.getCollisionRect().height;
            savePoint.loadUnsavedImage(_T(SAVE_UNSAVED_PATH), 32, 32);
            savePoint.loadSavedImage(_T(SAVE_SAVED_PATH), 32, 32);
            // savePoint.setImages(imgUnsavedPoint, imgSavedPoint);
        }
    }

    // 5. 加载普通地面图片
    if (!ng.empty())
    {
        for (auto& normalGround : ng)
        {
            int w = normalGround.getCollisionRect().width;
            int h = normalGround.getCollisionRect().height;
            // normalGround.setImage(imgGround);
            normalGround.loadImage(_T(GROUND_NORMAL_PATH), 32, 32);
        }
    }

    // 6. 加载可消失地面图片
    if (!dg.empty())
    {
        for (auto& disappearingGround : dg)
        {
            int w = disappearingGround.getCollisionRect().width;
            int h = disappearingGround.getCollisionRect().height;
            //disappearingGround.setImage(imgGround);
            disappearingGround.loadImage(_T(GROUND_NORMAL_PATH), 32, 32);
        }
    }

    // 7. 加载隐藏地面图片
    if (!hg.empty())
    {
        for (auto& hiddenGround : hg)
        {
            int w = hiddenGround.getCollisionRect().width;
            int h = hiddenGround.getCollisionRect().height;
            //hiddenGround.setImage(imgGround);
            hiddenGround.loadImage(_T(GROUND_NORMAL_PATH), 32, 32);
        }
    }

    //加载加速地面图片
    if (!sg.empty())
    {
        for (auto& speedUpGround : sg)
        {
            int w = speedUpGround.getCollisionRect().width;
            int h = speedUpGround.getCollisionRect().height;
            //speedUpGround.setImage(imgGround);
            speedUpGround.loadImage(_T(GROUND_NORMAL_PATH), 32, 32);
        }
    }

    // 8. 加载矩形静态陷阱图片
    if (!rt.empty())
    {
        for (auto& rectangleTrap : rt)
        {
            int w = rectangleTrap.getImgRect().width;  // 陷阱宽度（从位置/尺寸获取）
            int h = rectangleTrap.getImgRect().height; // 陷阱高度
            //rectangleTrap.setImage(imgApple);
            rectangleTrap.loadImage(_T(TRAP_RECT_STATIC_PATH), 32, 32);
        }
    }

    if (!tt.empty())
    {
        for (auto& triangleTrap : tt)
        {
            int w = triangleTrap.getImgRect().width;
            int h = triangleTrap.getImgRect().height;
            int direction = triangleTrap.getDirection();
            switch (direction)
            {
            case TRIANGLE_DIRECT_UP:
                triangleTrap.setImage(imgSpikeUp);
                triangleTrap.loadImage(_T(TRAP_TRI_UP_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_LEFT:
                triangleTrap.setImage(imgSpikeLeft);
                triangleTrap.loadImage(_T(TRAP_TRI_LEFT_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_DOWN:
                triangleTrap.setImage(imgSpikeDown);
                triangleTrap.loadImage(_T(TRAP_TRI_DOWN_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_RIGHT:
                triangleTrap.setImage(imgSpikeRight);
                triangleTrap.loadImage(_T(TRAP_TRI_RIGHT_PATH), w, h);
                break;
            }
        }
    }

    // 10. 加载矩形可触发陷阱图片
    if (!trt.empty())
    {
        for (auto& triggerableRectangleTrap : trt)
        {
            int w = triggerableRectangleTrap.getImgRect().width;  // 陷阱宽度（从位置/尺寸获取）
            int h = triggerableRectangleTrap.getImgRect().height; // 陷阱高度
            triggerableRectangleTrap.setImage(imgApple);
            triggerableRectangleTrap.loadImage(_T(TRAP_RECT_STATIC_PATH), w, h);
        }
    }

    // 11. 加载三角形可触发陷阱图片
    if (!ttt.empty())
    {
        for (auto& triggerableTriangleTrap : ttt)
        {
            int w = triggerableTriangleTrap.getImgRect().width;
            int h = triggerableTriangleTrap.getImgRect().height;
            int direction = triggerableTriangleTrap.getDirection();
            switch (direction)
            {
            case TRIANGLE_DIRECT_UP:
                triggerableTriangleTrap.setImage(imgSpikeUp);
                triggerableTriangleTrap.loadImage(_T(TRAP_TRI_UP_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_LEFT:
                triggerableTriangleTrap.setImage(imgSpikeLeft);
                triggerableTriangleTrap.loadImage(_T(TRAP_TRI_LEFT_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_DOWN:
                triggerableTriangleTrap.setImage(imgSpikeDown);
                triggerableTriangleTrap.loadImage(_T(TRAP_TRI_DOWN_PATH), w, h);
                break;
            case TRIANGLE_DIRECT_RIGHT:
                triggerableTriangleTrap.setImage(imgSpikeRight);
                triggerableTriangleTrap.loadImage(_T(TRAP_TRI_RIGHT_PATH), w, h);
                break;
            }
        }
    }

    //12. 标记地图加载完成
    isMapLoaded = true;
}



//4.绘制地图所有元素  
void Map::drawMap()
{
    if (!isMapLoaded) return; // 地图未加载则直接返回


    // 1. 绘制背景图（最底层,最低优先级）
    putimage(0, 0, &bgImage);


    // 2. 绘制交互点（倒数第二优先级）
    for (auto& savePoint : sp)
    {
        //存档
        if (savePoint.checkPlayerCollision())
        {
            savePoint.draw(false);
        }
        else
            savePoint.draw(true);
        // savePoint.draw(savePoint.getisSaved()); // 内部会根据状态选择图片
    }
    for (auto& endPoint : ep)
    {
        //终点
        endPoint.draw();
    }


    // 3. 绘制陷阱（陷阱在地面之下）
        //静态矩形
    for (auto& rectangleTrap : rt)
    {
        rectangleTrap.draw();
    }
    //静态三角形
    for (auto& triangleTrap : tt)
    {
        triangleTrap.draw();
    }
    //可触发陷阱
    for (auto& triggerableRectangleTrap : trt)
    {
        triggerableRectangleTrap.draw();
    }
    for (auto& triggerableTriangleTrap : ttt)
    {
        triggerableTriangleTrap.draw();
    }


    // 4. 绘制地面（最高优先级）
        //普通地面
    for (auto& normalGround : ng)
    {
        normalGround.draw();
    }

    for (auto& hiddenGround : hg)
    {
        hiddenGround.draw();
    }


    //可消失地面
    for (auto& disappearingGround : dg)
    {

        if (disappearingGround.getIsVisible())
        {
            disappearingGround.draw();
        }
    }
    //加速地面
    for (auto& speedUpGround : sg)
    {
        speedUpGround.draw();
    }
}



//5.更新地图状态（处理元素交互和状态变化）
void Map::updateMap(const Rect& playerRect, int& playerVelX, int& playerVelY)
{
    if (!isMapLoaded) return;

    //1.终点交互
    for (auto& endPoint : ep)
    {
        if (endPoint.checkPlayerReach())
        {
            endPoint.setIsReached(endPoint.checkPlayerReach());
            if (endPoint.getIsReached())
            {
                ChosenCurrentMap++;
                PlayerSpawnInitFlag = 0;
                CurrentMap.GlobalInitLevel();
                CurrentMap.loadMap();
                if(ChosenCurrentMap>3) view_manager.switch_to(ViewManager::ViewType::Victory);
                
                kid.ReInitDownBoundary();
                kid.ReInitUpBoundary();
                kid.ReInitLeftBoundary();
                kid.ReInitRightBoundary();
                //过关操作====================================================================================（view负责）==================================================================================================================
            }
        }
    }

    //2.存档点交互
    for (auto& savePoint : sp)
    {
        if (savePoint.checkPlayerCollision())
        {
            savePoint.setIsSaved(true);
            kid.updateSpawn(savePoint.getCollisionRect().x, savePoint.getCollisionRect().y - 10);

        }
    }



    //3.普通地面碰撞交互
    bool flag = 0;
    for (auto& normalGround : ng)
    {
        flag = flag || normalGround.isPlayerOnGround(kid);
    }

    for (auto& normalGround : ng)
    {
        normalGround.checkPlayerInteraction(kid);
    }

    //4.隐藏地面交互
    for (auto& hiddenGround : hg)
    {
        flag = flag || hiddenGround.isPlayerOnGround(kid);
        if (hiddenGround.getCollisionRect().intersects(kid.getPlayerRectBox()))
            hiddenGround.setIsRevealed(true);
    }
    kid.isGroundUpdate(flag);
    for (auto& hiddenGround : hg)
    {
        hiddenGround.NormalGround::checkPlayerInteraction(kid);
    }


    //5.可消失地面交互
    for (auto& disappearingGround : dg)
    {

        if (disappearingGround.getIsVisible())
        {
            //碰到就消失
            if (disappearingGround.getCollisionRect().intersects(kid.getPlayerRectBox()))
                disappearingGround.setIsVisible(false);
        }
    }




    //6.加速地面交互
    for (auto& speedUpGround : sg)
    {
        speedUpGround.checkPlayerInteraction(kid);
    }

    //7.矩形静态陷阱交互
    for (auto& rectangleTrap : rt)
    {
        //检测碰撞
        if (rectangleTrap.checkCollision(kid.getPlayerRectBox()))
        {
            //判死
            kid.Death();
        }
    }

    //8.三角形静态陷阱交互
    for (auto& triangleTrap : tt)
    {
        //检测碰撞
        if (triangleTrap.checkCollision(kid.getPlayerRectBox()))
        {
            //判死
            kid.Death();
        }
    }

    //9.矩形可触发陷阱交互
    for (auto& triggerableRectangleTrap : trt)
    {
        //检测是否已触发
        if (triggerableRectangleTrap.getIsTriggered())
        {
            //若已触发，检测是否移动到位置
            if (triggerableRectangleTrap.getTriggeredState() == TriggeredState::MOVE && triggerableRectangleTrap.isOutOfWindow())//isOutOfWindow()暂时代替=============================================================================
            {
                triggerableRectangleTrap.setTriggeredState(TriggeredState::NONE);
            }
            else
            {
                triggerableRectangleTrap.update();//更新陷阱位置
            }
            //检测碰撞
            if (triggerableRectangleTrap.checkCollision(kid.getPlayerRectBox()))
            {
                //判死
                kid.Death();
            }
            continue;//碰撞检测完成，遍历下一个陷阱
        }
        //若未触发，检测是否到达触发区域
        if (triggerableRectangleTrap.checkTrigger(kid.getPlayerRectBox()))
        {
            triggerableRectangleTrap.setIsTriggered(triggerableRectangleTrap.checkTrigger(kid.getPlayerRectBox()));//设置该陷阱为已触发
            triggerableRectangleTrap.setTriggeredState(TriggeredState::MOVE);//设置触发状态为：移动
            triggerableRectangleTrap.update();//可以触发，更新陷阱位置
            //检测碰撞
            if (triggerableRectangleTrap.checkCollision(kid.getPlayerRectBox()))
            {
                //判死
                kid.Death();
            }
        }
        //没触发也没到达触发地点，遍历下一个陷阱
    }

    //10.三角形可触发陷阱交互
    for (auto& triggerableTriangleTrap : ttt)
    {
        //检测是否已触发
        if (triggerableTriangleTrap.getIsTriggered())
        {
            //若已触发，检测是否移动到位置
            if (triggerableTriangleTrap.getTriggeredState() == TriggeredState::MOVE && triggerableTriangleTrap.isOutOfWindow())//isOutOfWindow()暂时代替=====================================================================================
            {
                triggerableTriangleTrap.setTriggeredState(TriggeredState::NONE);
            }
            else
            {
                triggerableTriangleTrap.update();//更新陷阱位置
            }
            //检测碰撞
            if (triggerableTriangleTrap.checkCollision(kid.getPlayerRectBox()))
            {
                //判死
                kid.Death();
            }
            continue;//碰撞检测完成，遍历下一个陷阱
        }
        //若未触发，检测是否到达触发区域
        if (triggerableTriangleTrap.checkTrigger(kid.getPlayerRectBox()))
        {
            triggerableTriangleTrap.setIsTriggered(triggerableTriangleTrap.checkTrigger(kid.getPlayerRectBox()));//设置该陷阱为已触发
            triggerableTriangleTrap.setTriggeredState(TriggeredState::MOVE);//设置触发状态为：移动
            triggerableTriangleTrap.update();//可以触发，更新陷阱位置
            //检测碰撞
            if (triggerableTriangleTrap.checkCollision(kid.getPlayerRectBox()))
            {
                //判死
                kid.Death();
            }
        }
    }

    //11.边界交互
    if (checkPlayerIsOut(kid))
    {
        kid.Death();//===================================================================（暂时用判死代替）===============================================================================
    }
}



//6.释放地图所有动态资源=========================================================================（存疑）==================================================================================
void Map::releaseMapResources()
{
    //空实现，自动释放
}




//7.获取地图加载状态
bool Map::getIsMapLoaded() const
{
    return isMapLoaded;
}




//8.判断角色出界
bool Map::checkPlayerIsOut(Player kid)
{
    if (kid.getPlayerRectBox().x <= 3 || kid.getPlayerRectBox().y <= 3 ||
        kid.getPlayerRectBox().x + kid.getPlayerRectBox().width >= WINDOW_WIDTH ||
        kid.getPlayerRectBox().y + kid.getPlayerRectBox().height >= WINDOW_HEIGHT+5)
    {
        return true;
    }
    else return false;
}



//9.获取已激活的存档点（工具函数）
pair<int, int> Map::getActiveSavePoints() const
{
    SavePoint currentSavePoint = savePointStack.top();
    Rect cur = currentSavePoint.getCollisionRect();
    int x = cur.x, y = cur.y;
    return make_pair(x, y);
}



//10.设置玩家初始出生点坐标
void Map::getBirthPoint(Player kid)
{
    //if (savePointStack.empty())
    //{
        kid.updateSpawn(birthX, birthY);
    //}
    //else
    //{
    //    int x = getActiveSavePoints().first;
    //    int y = getActiveSavePoints().second;
    //    kid.updateSpawn(x, y);
    //}
}

//11.清空存档栈
void Map::clearSavePoint()
{
    while (!savePointStack.empty())
    {
        savePointStack.pop();
    }
}

vector<NormalGround>& Map::getNg()
{
    return ng;
}
vector<HiddenGround>& Map::getHg()
{
    return hg;
}



void Map::GlobalInitLevel()
{
    switch (ChosenCurrentMap)
    {
    case 1:
        initLevel1();
        break;

    case 2:
        initLevel2();
        break;

    case 3:
        initLevel3();
        break;

    default:
        break;
    }
}



void Map::initLevel1()
{
    birthX = 50;
    birthY = 270;
    //如果人物的重生点已经初始化过，就不用再初始化了，用于地图间的切换
    if (!PlayerSpawnInitFlag)
    {
        PlayerSpawnInitFlag = 1;
        kid.updateSpawn(birthX, birthY);
        kid.Revive();
    }
    ep.clear();
    sp.clear();
    ng.clear();
    dg.clear();
    hg.clear();
    rt.clear();
    tt.clear();
    trt.clear();
    ttt.clear();
    // 1. 终点初始化：坐标(1100, 300)，尺寸60×80
    ep = {
        EndPoint(700,382,32,32)
    };
    ep.clear();
    ep.emplace_back(700, 350 - 32, 32, 32);

    // 2. 存档点初始化：2个存档点
    sp = {
        SavePoint(400, 382, 32, 32),   // 第一个存档点：坐标(300,500)，尺寸40×40
        //SavePoint(800, 400, 40, 40)    // 第二个存档点：坐标(800,400)，尺寸40×40
    };


    sp.clear();
    sp.emplace_back(100, 350 - 32, 32, 32);


    // 3. 普通地面初始化：底部地面+3个平台
    ng = {
        //NormalGround(0, 350, 800, 32),  // 草皮
        //NormalGround(150, 170, 192, 32), // 平台一
        //NormalGround(270, 238, 192, 32),  // 平台二
        //NormalGround(0, 382, 800, 218), // 地基
    };

    ng.clear();
    ng.reserve(10);
    ng.emplace_back(0, 350, 800, 32);   // 草皮
    ng.emplace_back(150, 170, 192, 32);   // 平台一
    ng.emplace_back(270, 238, 192, 32);   // 平台二
    ng.emplace_back(0, 382, 800, 218);  // 地基
    ng.emplace_back(200, 350 - 32, 32 * 3, 32 * 1);
    // 4. 可消失地面：延迟30帧消失
    dg = {
        //DisappearingGround(400, 600, 100, 30, 30), // 坐标(400,600)，延迟30帧
        //DisappearingGround(700, 500, 100, 30, 30)  // 坐标(700,500)，延迟30帧
    };
    dg.clear();
    //dg.emplace_back(200, 350 - 32 - 32, 32, 32, 1);

    // 5. 隐藏地面：初始不可见，接触后显示
    hg = {
        //HiddenGround(650, 600, 100, 30),  // 坐标(650,600)，隐藏平台
        //HiddenGround(900, 300, 100, 30)   // 坐标(900,300)，隐藏平台
    };

    hg.clear();
    hg.emplace_back(200, 350 - 32 - 32, 32 * 3, 32 * 3);

    // 6. 矩形静态陷阱：固定位置（如地面缝隙中的尖刺）
    rt = {
        // 碰撞箱(150,720,30,30)，贴图位置(150,720,30,30)
        /*RectangleTrap(Rect(150, 720, 30, 30), Rect(150, 720, 30, 30)),
        RectangleTrap(Rect(450, 720, 30, 30), Rect(450, 720, 30, 30))*/
    };

    // 7. 三角形静态陷阱：斜坡上的尖刺（顶点坐标定义三角形）
    tt = {
        // 三角形顶点(300,700), (330,700), (315,670)，贴图位置(300,670,30,30)
        TriangleTrap(Triangle(302,170, 334,170, 318,138), Rect(302,138,32,32), TRIANGLE_DIRECT_UP),
        TriangleTrap(Triangle(270,270, 302,270, 286,238), Rect(270,238,32,32), TRIANGLE_DIRECT_UP)
    };

    tt.clear();
    tt.emplace_back(
        Triangle(302, 170, 334, 170, 318, 138),
        Rect(302, 138, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(
        Triangle(265, 265, 297, 265, 281, 233),
        Rect(265, 233, 32, 32),
        TRIANGLE_DIRECT_UP);

    trt = {};
}

void Map::initLevel2()
{
    birthX = 100;
    birthY = 440;
    if (!PlayerSpawnInitFlag)
    {
        PlayerSpawnInitFlag = 1;
        kid.updateSpawn(birthX, birthY);
        kid.Revive();
    }

    ep.clear();
    sp.clear();
    ng.clear();
    dg.clear();
    hg.clear();
    rt.clear();
    tt.clear();
    trt.clear();
    ttt.clear();

    /*
    声明：1.界面总大小为800*600
            800=32*25      600=32*18+24
          2.所有方块贴图默认为32*32
    */

    // 1. 终点初始化：坐标(1100, 300)，尺寸60×80
    ep.reserve(1);
    ep.emplace_back(23 * 32, 2 * 32, 32, 32);

    // 2. 存档点初始化：2个存档点
    sp.reserve(50);
    sp.emplace_back(3 * 32, 13 * 32, 32, 32);//出生点存档
    sp.emplace_back(13 * 32, 16 * 32, 32, 32);//中下存档
    sp.emplace_back(12 * 32, 8 * 32, 32, 32);//中上存档


    // 3. 普通地面初始化：底部地面+3个平台
    ng.reserve(50);
    /*
    ng.emplace_back(0, 350, 800, 32);   // 草皮
    ng.emplace_back(150, 170, 192, 32);   // 平台一
    ng.emplace_back(270, 238, 192, 32);   // 平台二
    ng.emplace_back(0, 382, 800, 218);  // 地基
    ng.emplace_back(200, 350 - 32 , 32 * 3, 32 * 1);
    ng.emplace_back(90, 90, 32, 32);
    */
    ng.emplace_back(0, 0, 25 * 32, 32);//天花板
    ng.emplace_back(3 * 32, 16 * 32, 5 * 32, 32);//出生点垂直下方平台
    ng.emplace_back(11 * 32, 15 * 32, 32 * 4, 32);//中下跳台
    ng.emplace_back(16 * 32, 0, 32, 16 * 32);//右侧长竖挡
    ng.emplace_back(13 * 32, 17 * 32, 32 * 8, 32);//右下平台
    ng.emplace_back(23 * 32, 11 * 32, 32, 32);//右右中跳台
    ng.emplace_back(17 * 32, 7 * 32, 32, 32);//右左中跳台
    ng.emplace_back(20 * 32, 3 * 32, 32 * 4, 32);//右上平台
    ng.emplace_back(24 * 32, 0, 32, 32 * 20);//右墙

    // 4. 可消失地面：延迟30帧消失
    dg.reserve(50);

    // 5. 隐藏地面：初始不可见，接触后显示
    hg.reserve(50);
    hg.emplace_back(6 * 32, 7 * 32, 32, 32);//出生点右侧竖挡左侧跳台
    hg.emplace_back(7 * 32, 4 * 32, 32, 32 * 13);//出生点右侧竖挡上方竖挡
    hg.emplace_back(12 * 32, 9 * 32, 32 * 4, 32);//中上跳台
    hg.emplace_back(0, 3 * 32, 32, 32 * 9);//出生点左侧竖挡
    hg.emplace_back(32, 11 * 32, 32, 32);//出生点左侧跳台

    // 6. 矩形静态陷阱：固定位置（如地面缝隙中的尖刺）
    rt.reserve(50);

    // 7. 三角形静态陷阱：斜坡上的尖刺（顶点坐标定义三角形）
    tt.reserve(50);
    tt.emplace_back(//中下跳台右刺
        Triangle(14 * 32, 15 * 32, 15 * 32, 15 * 32, 14 * 32 + 16, 14 * 32),
        Rect(14 * 32, 14 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(//中下跳台左刺
        Triangle(13 * 32, 15 * 32, 14 * 32, 15 * 32, 13 * 32 + 16, 14 * 32),
        Rect(13 * 32, 14 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(//中上跳台的右刺
        Triangle(11 * 32, 10 * 32, 12 * 32, 10 * 32, 11 * 32 + 16, 9 * 32),
        Rect(11 * 32, 9 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(//中上跳台的左刺
        Triangle(10 * 32, 10 * 32, 11 * 32, 10 * 32, 10 * 32 + 16, 9 * 32),
        Rect(10 * 32, 9 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(//最上方左尖刺
        Triangle(8 * 32, 5 * 32, 9 * 32, 5 * 32, 8 * 32 + 16, 4 * 32),
        Rect(8 * 32, 4 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    tt.emplace_back(//最上方右尖刺
        Triangle(9 * 32, 5 * 32, 10 * 32, 5 * 32, 9 * 32 + 16, 4 * 32),
        Rect(9 * 32, 4 * 32, 32, 32),
        TRIANGLE_DIRECT_UP
    );

    // 8. 矩形可触发陷阱：触发区域进入后向右移动
    trt.reserve(50);

    // 9. 三角形可触发陷阱：触发区域进入后向下移动
    ttt.reserve(50);
}
void Map::initLevel3()
{
    birthX = 0;
    birthY = 50;
    //如果人物的重生点已经初始化过，就不用再初始化了，用于地图间的切换
    if (!PlayerSpawnInitFlag)
    {
        PlayerSpawnInitFlag = 1;
        kid.updateSpawn(birthX, birthY);
        kid.Revive();
    }
    ep.clear();
    sp.clear();
    ng.clear();
    dg.clear();
    hg.clear();
    rt.clear();
    tt.clear();
    trt.clear();
    ttt.clear();

#define x 32
    //终点
    ep.reserve(1);
    ep.emplace_back(21 * x, 14 * x, x, x);

    //存档点
    sp.reserve(10);
    sp.emplace_back(20 * x, 7 * x, x, x);
    sp.emplace_back(12 * x, 11 * x, x, x);

    //ground
    ng.reserve(20);
    ng.emplace_back(0, 0, 800, 60);
    ng.emplace_back(23 * x, 2 * x, 2 * x, 17 * x);
    ng.emplace_back(0, 11 * x, 5 * x, 7 * x);
    ng.emplace_back(10 * x, 5 * x, 8 * x, x);
    ng.emplace_back(13 * x, 8 * x, 10 * x, x);
    ng.emplace_back(4 * x, 9 * x, 6 * x, x);
    ng.emplace_back(12 * x, 12 * x, 7 * x, x);
    ng.emplace_back(10 * x, 6 * x, x, 6 * x);
    ng.emplace_back(7 * x, 8 * x, 4 * x, x);
    ng.emplace_back(8 * x, 7 * x, 2 * x, x);
    ng.emplace_back(9 * x, 6 * x, x, x);
    ng.emplace_back(10 * x, 5 * x, x, x);
    ng.emplace_back(2 * x, 4 * x, 3 * x, x);
    ng.emplace_back(2 * x, 7 * x, 3 * x, x);
    ng.emplace_back(4 * x, 4 * x, x, 9 * x);
    ng.emplace_back(5 * x, 2 * x, x, x);
    //三角形静态陷阱
    //第一波刺
    tt.reserve(30);
    tt.emplace_back(
        Triangle(6 * x, 8 * x + 15, 6 * x + 15, 8 * x, 6 * x + 15, 8 * x + 30),
        Rect(6 * x, 8 * x, x, x),
        TRIANGLE_DIRECT_LEFT
    );

    tt.emplace_back(
        Triangle(7 * x, 7 * x + 15, 7 * x + 15, 7 * x + 0, 7 * x + 15, 7 * x + 30),
        Rect(7 * x, 7 * x, x, x),
        TRIANGLE_DIRECT_LEFT
    );
    tt.emplace_back(
        Triangle(8 * x, 6 * x + 15, 8 * x + 15, 6 * x + 0, 8 * x + 15, 6 * x + 30),
        Rect(8 * x, 6 * x, x, x),
        TRIANGLE_DIRECT_LEFT
    );
    tt.emplace_back(
        Triangle(9 * x, 5 * x + 15, 9 * x + 15, 5 * x + 0, 9 * x + 15, 5 * x + 30),
        Rect(9 * x, 5 * x, x, x),
        TRIANGLE_DIRECT_LEFT
    );

    //第二波刺(死亡判定太灵敏了，删了两个)
    tt.emplace_back(
        Triangle(364, 129 + 40, 364 + 36, 129 + 40, 364 + 18, 129),
        Rect(364, 129, 36, 40),
        TRIANGLE_DIRECT_UP
    );

    /*tt.emplace_back(
        Triangle(424, 129 + 40, 424 + 36, 129 + 40, 424 + 18, 129),
        Rect(424, 129, 36, 40),
        TRIANGLE_DIRECT_UP
    );*/
    tt.emplace_back(
        Triangle(424, 60, 424 + 36, 60, 424 + 18, 60 + 40),
        Rect(424, 60, 36, 40),
        TRIANGLE_DIRECT_DOWN
    );

    tt.emplace_back(
        Triangle(484, 129 + 40, 484 + 36, 129 + 40, 484 + 18, 129),
        Rect(484, 129, 36, 40),
        TRIANGLE_DIRECT_UP
    );
    /*tt.emplace_back(
        Triangle(544, 129 + 40, 544 + 36, 129 + 40, 544 + 18, 129),
        Rect(544, 129, 36, 40),
        TRIANGLE_DIRECT_UP
    );*/
    //第三波刺
    tt.emplace_back(
        Triangle(19 * x, 8 * x + 10, 19 * x + 8, 8 * x + 10, 19 * x + 4, 8 * x),
        Rect(19 * x, 8 * x - 5, 8, 10),
        TRIANGLE_DIRECT_UP
    );
    //第四波刺
    tt.emplace_back(
        Triangle(16 * x, 8 * x + 15, 16 * x + 34, 8 * x + 15, 16 * x + 17, 8 * x),
        Rect(16 * x, 8 * x - 1, x, x),
        TRIANGLE_DIRECT_UP
    );
    tt.emplace_back(
        Triangle(14 * x, 8 * x + 15, 14 * x + 34, 8 * x + 15, 14 * x + 17, 8 * x),
        Rect(14 * x, 8 * x - 1, x, x),
        TRIANGLE_DIRECT_UP
    );
    //第五波刺
    
    tt.emplace_back(
        Triangle(14 * x, 12 * x + 15, 14 * x + 30, 12 * x + 15, 14 * x + 15, 12 * x),
        Rect(14 * x, 12 * x - 1, x, x),
        TRIANGLE_DIRECT_UP
    );
    tt.emplace_back(
        Triangle(15 * x, 12 * x + 15, 15 * x + 30, 12 * x + 15, 15 * x + 15, 12 * x),
        Rect(15 * x, 12 * x - 1, x, x),
        TRIANGLE_DIRECT_UP
    );
    //触发类陷阱
    //可触发三角形陷阱
    ttt.emplace_back(
        Triangle(22 * x, 6 * x, 22 * x + 30, 6 * x, 22 * x + 30, 6 * x),
        Rect(22 * x, 6 * x, x, x),
        Rect(16 * x, 6 * x, 2 * x, x),-30,0, TRIANGLE_DIRECT_LEFT
    );
    ttt.emplace_back(
        Triangle(18 * x, 9 * x, 18 * x + 30, 9 * x, 18 * x + 15, 9 * x + 2 * x - 5),
        Rect(18 * x, 9 * x, x, 2 * x),
        Rect(18*x-3,11*x+3,x,x),0,3,
        TRIANGLE_DIRECT_DOWN
    );
}
void Map::initLevel4()
{
    birthX = 0;
    birthY = 50;
    //如果人物的重生点已经初始化过，就不用再初始化了，用于地图间的切换
    if (!PlayerSpawnInitFlag)
    {
        PlayerSpawnInitFlag = 1;
        kid.updateSpawn(birthX, birthY);
        kid.Revive();
    }
    ep.clear();
    sp.clear();
    ng.clear();
    dg.clear();
    hg.clear();
    rt.clear();
    tt.clear();
    trt.clear();
    ttt.clear();

}


//=======================================================================================================（准备弃置）=============================================================
////6.重置地图状态（恢复所有元素初始状态）
//void Map::resetMap(vector<DisappearingGround>& dg, vector<HiddenGround>& hg,
//    vector<TriggerableRectangleTrap>& trt, vector<TriggerableTriangleTrap>& ttt)
//{
//    if (!isMapLoaded) return;
//
//    //6. 重置可消失地面
//    for (auto& disappearingGround : dg)
//    {
//        //重置函数
//    }
//
//    //7.重置隐藏地面
//    for (auto& hiddenGround : hg)
//    {
//        //重置函数
//    }
//
//    //10.重置矩形可触发陷阱
//    for (auto& triggerableRectangleTrap : trt)
//    {
//        //重置函数
//    }
//
//    //11.重置三角形可触发陷阱
//    for (auto& triggerableTriangleTrap : ttt)
//    {
//        //重置函数
//    }
//}


// 转换函数：std::string → std::wstring（支持系统默认编码或UTF-8）
wstring StringToWString(const std::string& str, UINT codePage) {
    if (str.empty()) return L"";
    int wLen = MultiByteToWideChar(codePage, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(wLen, 0);
    MultiByteToWideChar(codePage, 0, str.c_str(), -1, &wstr[0], wLen);
    return wstr;
}
