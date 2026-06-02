#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "global.h"
#include "utils.h"
#include <graphics.h>
#include "Trap.h"         //调用陷阱类成员函数
#include "Ground.h"       //调用地面类成员函数
#include "Player.h"       //调取角色数据
#include "Shape.h"
#include "Point.h"
#include <stack>
#include <utility>
using namespace std;

//需要用到的全局变量
#define BG1_PATH "Assert/images/bg1.png"                        //第一关背景图 (还没改)
#define END_POINT_PATH "Assert/images/sprWarp.png"                  //终点贴图
#define SAVE_UNSAVED_PATH "Assert/images/Archive_SAVE_OFF.png"      //未存档贴图
#define SAVE_SAVED_PATH "Assert/images/Archive_SAVE_ON.png"          //已存档贴图
#define GROUND_NORMAL_PATH "Assert/images/Block.png"    //地面贴图
#define TRAP_RECT_STATIC_PATH "Assert/images/sprCherry.png"     //矩形陷阱（苹果）贴图
#define TRAP_TRI_UP_PATH "Assert/images/sprSpikeUp.png"               //上三角
#define TRAP_TRI_LEFT_PATH "Assert/images/sprSpikeLeft.png"             //左三角
#define TRAP_TRI_RIGHT_PATH "Assert/images/sprSpikeRight.png"            //右三角
#define TRAP_TRI_DOWN_PATH "Assert/images/sprSpike.png"             //下三角

extern stack<SavePoint>savePointStack;//存档点工具栈

/*
地图类声明：
0.本类的各种函数由gameview类调用，只负责接口，不负责任何动画部分！！！！！
1.调用陷阱，地面的绘制，动画函数。陷阱，地面的绘制均在本文件进行
2.调用碰撞检测函数，调取角色位置和碰撞箱数据，检测与陷阱地面的碰撞
3.角色的行为在这里依靠碰撞检测改变，能够调用设置角色的运动状态，改变速度的函数，能判定角色死亡
4.本文件能够存储各种实体类信息存到数组，map类对象分关卡创立，设在全局变量中
5.本类只提供判断角色是否在某存档点存档，是否到达终点的函数接口，存档，暂停，退出游戏，读档，界面转换均在界面转换文件实现，本类只提供判断函数
*/

/*
注意：
1.将本类对象创建为局部对象，局部调用，玩家死亡或退出游戏时释放所有资源，之后重新创建对象，调用构造函数
2.玩家选择重生后，清屏，重新创建对象，重新调用绘制函数，重新从全局变量的数组中调取信息，免去恢复函数！===================================================================
3.本类不支持任何文件存档功能，存档只在游戏进行过程中进行，玩家退出游戏界面则清空存档栈，删除存档信息！
*/



//地图类，管理游戏场景中所有元素（地面、陷阱、存档点等）的加载、更新和渲染
class Map
{
private:
    IMAGE bgImage;      //背景图像资源
    string bgPath;     //图片路径
    bool isMapLoaded;   //地图加载状态标记（true表示已加载）
    int birthX, birthY; //玩家的出生点(初始为初始出生点，后续根据存档改编为存档点)

    //功能地块
    vector<EndPoint> ep;                   //终点
    vector<SavePoint> sp;                  //存档点

    //地面信息
    vector<NormalGround> ng;               //普通地面
    vector<DisappearingGround> dg;         //可消失地面
    vector<HiddenGround> hg;               //隐藏地面
    vector<SpeedUpGround> sg;              //可加速地面

    //陷阱信息
    vector<RectangleTrap> rt;              //静态矩形陷阱
    vector<TriangleTrap> tt;               //静态三角形陷阱
    vector<TriggerableRectangleTrap> trt;  //可触发矩形陷阱
    vector<TriggerableTriangleTrap> ttt;   //可触发三角形陷阱

public:
    //开始时执行一次
          //1.构造函数
    Map() {}
    Map(IMAGE bgImage, string bgPath, bool isMapLoaded, int birthX, int birthY);

    Map(IMAGE bgImage, string bgPath, bool isMapLoaded, int birthX, int birthY,
        vector<EndPoint> &ep,
        vector<SavePoint> &sp,
        vector<NormalGround> &ng,
        vector<DisappearingGround> &dg,
        vector<HiddenGround> &hg,
        vector<SpeedUpGround> &sg,
        vector<RectangleTrap> &rt,
        vector<TriangleTrap> &tt,
        vector<TriggerableRectangleTrap> &trt,
        vector<TriggerableTriangleTrap> &ttt
    );
    //2.析构函数：释放地图所有资源（退出游戏时也需调用）
    ~Map();
    //3.加载地图资源（加载每个实体对象的图片）
    void loadMap();
    //4.绘制地图所有元素                 
    void drawMap();



    //while(true)每帧执行
          //5.更新地图状态（刷新所有元素状态，处理玩家交互）                        
    void updateMap(const Rect& playerRect, int& playerVelX, int& playerVelY);



    //结束时执行一次
          //6.释放地图所有动态资源（工具函数）                             
    void releaseMapResources();



    //工具函数
          //7.获取地图加载状态（本类工具函数）                                             
    bool getIsMapLoaded() const;

    //8.判断出界（本类工具函数）
    bool checkPlayerIsOut(Player kid);

    //9.获取已激活的存档点（本类工具函数）                         
    pair<int, int> getActiveSavePoints() const;

    //10.设置玩家出生点坐标 （进入游戏和重生时调用）                                             
    void getBirthPoint(Player kid);

    //11.清空存档栈（玩家退出游戏时调用）
    void clearSavePoint();

    vector<NormalGround>& getNg();
    vector<HiddenGround>& getHg();


    void initLevel1();
    void initLevel2();
    void initLevel3();
    void initLevel4();
    void GlobalInitLevel();

    
};

wstring StringToWString(const std::string& str, UINT codePage = CP_ACP);
//6.重置地图状态（将所有元素恢复到初始状态)(准备弃置)============================================================================================================                      
