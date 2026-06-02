#pragma once
#include"Map.h"
#include"Shape.h"
#include<vector>
#include<graphics.h>
//玩家
//关于玩家相关的类和函数声明写这里，包括跳跃和行走

extern vector<IMAGE> imgLeftStandSpirit; //静止时角色朝左的显示动画
extern vector<IMAGE> imgLeftMoveSpirit; //移动时角色朝左的显示动画
extern vector<IMAGE> imgRightStandSpirit; //静止时角色朝左的显示动画
extern vector<IMAGE> imgRightMoveSpirit; //移动时角色朝左的显示动画
extern vector<IMAGE> imgJumpSpirit; //跳跃时角色的显示动画（仅限上升）
extern vector<IMAGE> imgFallSpirit; //下落时角色的显示动画 

extern const int PlayerSpeedX; //角色水平固定移动速度
extern const int PlayerJumpSpeedY; //角色跳跃时初始速度，负数
extern const int PlayerFalldSpeedY_NoSpace; //角色未按住"Space"下落速度增长量
extern const int PlayerFalldSpeedY_Space; //角色按住"Space"下落速度增长量
extern const int PlayerFallMaxSpeedY; //角色下落最大速度
extern const int PlayerErrorPixelPointtoGround;  //人物和地面的误差容许范围

class Player
{
private:
	Rect playerBox;
	int Birthx, Birthy;  //角色的死亡后复活点
	int x, y;         //角色贴图所在的位置
	int Xsize, Ysize;  //角色的尺寸大小，用于碰撞箱设定
	int vel_X, vel_Y;  //角色的速度,注意easyX的Y是向下增大
	int FaceToWhere;  //角色的朝向，-1为左，1为右边
	bool AliveFlag;   //判断角色是否存活
	bool DoubleJumpFlag;    //判断角色是否可以进行二段跳
	bool JumpFlag;    ///判断角色是否可以进行跳跃
	bool ContiJump;

	//Boundary用来处理地图边界和阻拦方块检测
	int RightBoundary;  //kid向右走时的阻挡边界
	int LeftBoundary;    //kid向左走时的阻挡边界
	int UpBoundary;     //kid向上跳的时的阻挡边界
	int DownBoundary;	 //kid向下跳的时的阻挡边界


	bool isGround;  //是否在地面上
public:
	Player() = default;
	Player(Map& currentmap);

	/*
	   功能：判断角色是否在处于下落状态（!isGround&&vel_Y>0）
	   参数：
		   无

	   返回值：1在下落，0不在下落
	*/
	bool isFalling()const;


	/*
	   功能：更新角色的运动状态并绘制
	   具体实现：依据输入更新角色的x,y位置
	   写入Gameview.InputHandle中
	*/
	void PlayerMove(ExMessage& msg);


	/*
	   功能：绘制角色
	   特别注意FaceToWhere为-1时反向绘制人物
	   写入Gameview.Draw
	*/
	void PlayerDraw();

	//更改存活状态的函数
	void Death();
	void Revive();


	//返回角色的碰撞箱
	Rect getPlayerRectBox();

	//重置角色X和Y的速度
	void PlayerChangeVelX(int vel);
	void PlayerChangeVelY(int vel);

	//改变角色的朝向
	void FacetoRight();
	void FacetoLeft();

	/*
	* 功能：重置角色重生点
	* 使用：激活存档的时候
	*/
	void updateSpawn(int newx, int newy);

	//获得角色x坐标
	int GetKidX();

	//获得角色y坐标
	int GetKidY();

	//改变角色x坐标
	void ChangeKidX(int newx);

	//改变角色的y坐标
	void ChangeKidY(int newy);

	//获得局的的x方向速度
	int GetKidVelX();

	//获得角色的y方向速度
	int GetKidVelY();

	//获得角色的x宽度
	int GetXsize();

	//获得角色的y宽度
	int GetYsize();

	//获得角色的存活状态
	bool isAlive();

	//获得角色的朝向
	int getFace();

	//重新初始化边界
	void ReInitRightBoundary();
	void ReInitLeftBoundary();
	void ReInitUpBoundary();
	void ReInitDownBoundary();

	//重新更改角色的移动边界
	void ChangeRightBoundary(int Boun);
	void ChangeLeftBoundary(int Boun);
	void ChangeUpBoundary(int Boun);
	void ChangeDownBoundary(int Boun);

	int& getBirthX();

	int& getBirthY();


	//更新是否在地面的状态
	void isGroundUpdate(bool i);

	//返回是否在地面的状态
	bool getIsGround();
};

#define LEFT 0
#define RIGHT 1
//用于控制静止动画的播放速度
#define AnimaStandTime 15

#define IMG_LEFT_STAND_KID_PATH1 "Assert/images/iwanna1a-removebg-preview.png"
#define IMG_LEFT_STAND_KID_PATH2 "Assert/images/iwanna2a-removebg-preview.png"
#define IMG_RIGHT_STAND_KID_PATH1 "Assert/images/iwanna1-removebg-preview.png"
#define IMG_RIGHT_STAND_KID_PATH2 "Assert/images/iwanna2-removebg-preview.png"
#define IMG_LEFT_JUMP_KID_PATH "Assert/images/iwanna3a-removebg-preview.png"
#define IMG_RIGHT_JUMP_KID_PATH "Assert/images/iwanna3-removebg-preview.png"
#define IMG_LEFT_FALL_KID_PATH "Assert/images/iwanna4a-removebg-preview.png"
#define IMG_RIGHT_FALL_KID_PATH "Assert/images/iwanna4a__2_-removebg-preview.png"
#define IMG_LEFT_MOVE_KID_PATH1 "Assert/images/iwanna5a-removebg-preview.png"
#define IMG_LEFT_MOVE_KID_PATH2 "Assert/images/iwanna6a-removebg-preview.png"
#define IMG_RIGHT_MOVE_KID_PATH1 "Assert/images/iwanna5-removebg-preview.png"
#define IMG_RIGHT_MOVE_KID_PATH2 "Assert/images/iwanna6-removebg-preview.png"
#define KID_SIZE_X 31
#define KID_SIZE_Y 31
#define KID_BOX_WIDTH 14 // 12
#define KID_BOX_HEIGHT 26 // 24
#define KID_BOX_dX 10 // 12
#define KID_BOX_dY 6