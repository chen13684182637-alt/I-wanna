#include "Player.h"
#include "utils.h"

/*用来控制动画播放*/
int imgMoveFlag = 0;
int imgStandFlag = 0;
int imgMoveCount = 0;
int imgStandCount = 0;
int isStandFlag = 0;

//控制连续跳跃
int SpaceFlag = 1;

//人物移动相关参数
const int PlayerSpeedX = 7; //角色水平固定移动速度
const int PlayerJumpSpeedY = -20; //角色跳跃时初始速度，负数
const int PlayerFalldSpeedY_Space = 2; //角色按住“Space”下落速度增长量
const int PlayerFalldSpeedY_NoSpace = 5; //角色未按住“Space”下落速度增长量		
const int PlayerFallMaxSpeedY = 9; //角色下落最大速度 



vector<IMAGE> imgLeftStandSpirit(2); //静止时角色朝左的显示动画
vector<IMAGE> imgLeftMoveSpirit(2); //移动时角色朝左的显示动画
vector<IMAGE> imgRightStandSpirit(2); //静止时角色朝右的显示动画
vector<IMAGE> imgRightMoveSpirit(2); //移动时角色朝右的显示动画
vector<IMAGE> imgJumpSpirit(2); //跳跃时角色的显示动画（仅限上升）
vector<IMAGE> imgFallSpirit(2); //下落时角色的显示动画 


Player::Player(Map& currentmap)
{

	CurrentMap.getBirthPoint(kid);
	Xsize = KID_SIZE_X;
	Ysize = KID_SIZE_Y;

	//人物碰撞箱设置大一点可以解决地面碰撞问题
	playerBox = Rect(x + KID_BOX_dX, y + KID_BOX_dY, KID_BOX_WIDTH, KID_BOX_HEIGHT);
	vel_X = 0;
	vel_Y = 0;
	x = Birthx;
	y = Birthy;
	FaceToWhere = 1;  //初始向右
	AliveFlag = 1;
	DoubleJumpFlag = 1;
	JumpFlag = 1;
	isGround = 0;
	RightBoundary = WINDOW_WIDTH;
	LeftBoundary = 0;
	UpBoundary = 0;
	DownBoundary = WINDOW_HEIGHT;

}

/*
   负责：残念筠
   功能：判断角色是否在处于下落状态（!isGround&&vel_Y>0）
   参数：无
   返回值：1在下落，0不在下落
*/
bool Player::isFalling() const
{
	return (vel_Y > 0);
}

/*
   负责：残念筠
   具体实现：依据输入更新角色的x,y位置
*/
void Player::PlayerMove(ExMessage& msg)
{
	
	if (!isGround)
	{
		if (vel_Y < PlayerFallMaxSpeedY)  //未到达下落的最大速度时，保持Y轴速度增大
		{
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && vel_Y < 0) vel_Y += PlayerFalldSpeedY_Space;  //处于跳跃状态按住space可以跳得更高
			else vel_Y += PlayerFalldSpeedY_NoSpace;
		}
		JumpFlag = 0;
	}
	else
	{
		if (isFalling())vel_Y = 0; //强调在下落时回到地面重置竖直方向速度为0，是为了防止刚刚跳起时候误判在地面上而重置y轴速度
		JumpFlag = 1;
		DoubleJumpFlag = 1;
	}

	/*移动检测*/
	if (GetAsyncKeyState('A') & 0x8000) { // 长按 A：向左
		FacetoLeft();
		vel_X = PlayerSpeedX;
		//向左移动重置左边界和下界面
		ReInitLeftBoundary();
		ReInitDownBoundary();

	}
	if (GetAsyncKeyState('D') & 0x8000) { // 长按 D：向右
		FacetoRight();
		vel_X = PlayerSpeedX;
		//向右移动重置右边界和下界面
		ReInitRightBoundary();
		ReInitDownBoundary();
	}
	if (!(GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000))vel_X = 0;

	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && SpaceFlag)
	{
		SpaceFlag = 0;
		// 1. 地面一段跳
		if (isGround && JumpFlag)
		{
			mciSendString("seek jumpSound to start", 0, 0, 0);
			mciSendString("play jumpSound",0,0,0);

			vel_Y = PlayerJumpSpeedY;  // 赋予向上跳跃速度
			//成功跳跃后重置下落边界和上界面
			ReInitDownBoundary();
			ReInitUpBoundary();
		}

		// 2. 空中二段跳
		else if (!isGround && DoubleJumpFlag)
		{
			mciSendString("seek doubleJumpSound to start", 0, 0, 0);
			mciSendString("play doubleJumpSound", 0, 0, 0);

			vel_Y = PlayerJumpSpeedY;  // 再次赋予向上速度
			DoubleJumpFlag = false;
			//成功跳跃后重置下落边界和上界面
			ReInitUpBoundary();
			ReInitDownBoundary();
		}


	}
	if ((GetAsyncKeyState('R') & 0x8000) && RFlag)
	{
		RFlag = 0;
		CurrentMap.GlobalInitLevel();
		CurrentMap.loadMap();
		kid.Revive();
	}
	if (msg.message == WM_KEYUP)
	{
		if (msg.vkcode == VK_SPACE) {
			SpaceFlag = 1;
			if (JumpFlag && !isGround)
			{
				JumpFlag = false;
				DoubleJumpFlag = true;
			}
		}
		if( msg.vkcode == 'R') RFlag = 1;
	}

	//当以地图为单位时，checkPlayerInteraction(kid)和isGround的状态更新写进Map.update()里面

	/*测试用例*/
	//isGround = ground1.isPlayerOnGround(kid) || ground2.isPlayerOnGround(kid) || ground3.isPlayerOnGround(kid);
	/*测试用例*/

	/*测试用例*/
	
	/*测试用例*/

	//位置坐标更新
	x += FaceToWhere * vel_X;
	y += vel_Y;

	playerBox.update(x + KID_BOX_dX, y + KID_BOX_dY);

	/*测试用例*/
	//checkPlayerInteraction可以更新阻拦kid的边界
	/*ground1.checkPlayerInteraction(kid);
	ground2.checkPlayerInteraction(kid);
	ground3.checkPlayerInteraction(kid);
	cout << isGround << endl;*/

	vector<NormalGround> normalg = CurrentMap.getNg();
	vector<HiddenGround> hiddeng = CurrentMap.getHg();
	for (auto& ng : normalg)
	{
		ng.checkPlayerInteraction(kid);
	}
	for (auto& hg : hiddeng)
	{
		hg.checkPlayerInteraction(kid);
	}
	/*测试用例*/



	//边界限制，当没有经过checkPlayerInteraction更新时，kid的边界默认是地图边界
	if (x + KID_BOX_WIDTH + KID_BOX_dX >= RightBoundary) x = RightBoundary - KID_BOX_WIDTH - KID_BOX_dX;
	if (x <= LeftBoundary)x = LeftBoundary - KID_BOX_dX / 2;
	if (y + KID_SIZE_Y >= DownBoundary) y = DownBoundary - KID_SIZE_Y;
	if (y <= UpBoundary)y = UpBoundary;

}

/*
   负责：残念筠
   功能：依据不同人物状态绘制角色
   写入Gameview.Draw
*/
void Player::PlayerDraw()
{
	int dirFlag = FaceToWhere == -1 ? LEFT : RIGHT;
	if (vel_Y != 0)
	{
		if (isFalling())
		{
			putimage_new(x, y, &imgFallSpirit[dirFlag]);
		}
		else
		{
			putimage_new(x, y, &imgJumpSpirit[dirFlag]);
		}
	}
	else
	{
		if (dirFlag == LEFT)
		{
			if (!(GetAsyncKeyState('A') & 0x8000))
			{
				putimage_new(x, y, &imgLeftStandSpirit[imgStandFlag]);
				imgStandCount++;
				if (imgStandCount == AnimaStandTime)
				{
					imgStandFlag = imgStandFlag == 1 ? 0 : 1;
					imgStandCount = 0;
				}
			}
			else
			{
				putimage_new(x, y, &imgLeftMoveSpirit[imgMoveFlag]);
				imgMoveFlag = imgMoveFlag == 1 ? 0 : 1;
			}
		}
		else
		{
			if (!(GetAsyncKeyState('D') & 0x8000))
			{
				putimage_new(x, y, &imgRightStandSpirit[imgStandFlag]);
				imgStandCount++;
				if (imgStandCount == AnimaStandTime)
				{
					imgStandFlag = imgStandFlag == 1 ? 0 : 1;
					imgStandCount = 0;
				}
			}
			else
			{
				putimage_new(x, y, &imgRightMoveSpirit[imgMoveFlag]);
				imgMoveFlag = imgMoveFlag == 1 ? 0 : 1;

			}
		}
	}
	playerBox.draw();
}


/*
* 负责：残念筠
* 功能：判定角色死亡
*/
void Player::Death() {
	AliveFlag = 0;
}

/*
* 负责：残念筠
* 功能：判定角色重生
*/
void Player::Revive()
{
	AliveFlag = 1;
	x = Birthx;
	y = Birthy;
}


/*
* 负责：残念筠
* 功能：返回角色碰撞箱
*/
Rect Player::getPlayerRectBox() { return playerBox; }

/*
* 负责：残念筠
* 功能：重置角色X和Y的速度
*/
void Player::PlayerChangeVelX(int vel) { vel_X = vel; }
void Player::PlayerChangeVelY(int vel) { vel_Y = vel; }

/*
* 负责：残念筠
* 功能：更改角色的朝向
*/
void Player::FacetoRight() { FaceToWhere = 1; }
void Player::FacetoLeft() { FaceToWhere = -1; }

/*
	* 负责：残念筠
	* 功能：重置角色重生点
	* 使用：激活存档的时候
	*/
void Player::updateSpawn(int newx, int newy)
{
	Birthx = newx;
	Birthy = newy;
}


//获得角色x坐标
int Player::GetKidX()
{
	return x;
}

//获得角色y坐标
int Player::GetKidY()
{
	return y;
}

//改变角色x坐标
void Player::ChangeKidX(int newx)
{
	x = newx;
	return;
}

//改变角色y坐标
void Player::ChangeKidY(int newy)
{
	y = newy;
	return;
}

//获得局的的x方向速度
int Player::GetKidVelX()
{
	return vel_X;
}

//获得角色的y方向速度
int Player::GetKidVelY()
{
	return vel_Y;
}

//获得角色的x宽度
int Player::GetXsize()
{
	return Xsize;
}

//获得角色的y宽度
int Player::GetYsize()
{
	return Ysize;
}

//获得角色的存活状态
bool Player::isAlive()
{
	return AliveFlag;
}

int Player::getFace()
{
	return FaceToWhere;
}


void Player::ReInitRightBoundary()
{
	RightBoundary = WINDOW_WIDTH;
}
void Player::ReInitLeftBoundary()
{
	LeftBoundary = 0;
}
void Player::ReInitUpBoundary()
{
	UpBoundary = 0;
}
void Player::ReInitDownBoundary()
{
	DownBoundary = WINDOW_HEIGHT;
}
//重新更改角色的移动边界
void Player::ChangeRightBoundary(int Boun)
{
	RightBoundary = Boun;
}
void Player::ChangeLeftBoundary(int Boun)
{
	LeftBoundary = Boun;
}
void Player::ChangeUpBoundary(int Boun)
{
	UpBoundary = Boun;
}
void Player::ChangeDownBoundary(int Boun)
{
	DownBoundary = Boun;
}

int& Player::getBirthX() { return Birthx; }

int& Player::getBirthY() { return Birthy; }

//更新是否在地面的状态
void Player::isGroundUpdate(bool i)
{
	isGround = i;
}

//获取是否在地面的状态
bool Player::getIsGround()
{
	return isGround;
}
