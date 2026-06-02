#pragma once
#include "Ground.h"
#include "Trap.h"
#include "Point.h"
#include <graphics.h>
#include <vector>

class Map;
class Player;

// 音乐音效相关
#define INIT_VOLUME 15
#define INIT_SOUND 70

extern int volume_int;
extern int sound_int;
extern string mymusictype;

extern vector<string> BGMname;
extern vector<string> BGM;
extern int BGM_ptr;

using namespace std;

/*
* 用来放全局变量
*/

extern bool RFlag ; //防止按住R无限重生


extern int ChosenCurrentMap;  //当前的关卡

extern bool PlayerSpawnInitFlag;

// 纯色背景颜色宏定义
#define SKYBLUE RGB(135, 206, 235)

extern bool CollBoxDrawFlag;

#define BOX_DRAW_ON CollBoxDrawFlag= 1
#define BOX_DRAW_OFF CollBoxDrawFlag= 0

/*
//std::vector<IMAGE> nowAnimation = &kid.imgStandSpirit; //初始动画默认为静止
extern const int PlayerSpeedX; //角色水平固定移动速度
extern const int PlayerJumpSpeedY; //角色跳跃时初始速度，负数
extern const int PlayerFalldSpeedY_NoSpace; //角色下落速度增长量
extern const int PlayerFalldSpeedY; //角色未按住"Space"下落速度增长量
extern const int PlayerFallMaxSpeedY; //角色下落最大速度
extern const int AniPlayDelaySpeed;  //动画播放的延迟速度
extern const int PlayerErrorPixelPointtoGround;  //人物和地面的误差容许范围
*/

extern int CurrenLevel;
extern Map CurrentMap;

extern Player kid;  //主角对象


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
/*测试用例*/
extern NormalGround ground1;
extern NormalGround ground2;
extern NormalGround ground3;
/*测试用例*/
/*
#define imgStandKidPath "Assert/images/PartStandkid.png"
#define KID_SIZE_X 16
#define KID_SIZE_Y 32
#define KID_BOX_WIDTH 8
#define KID_BOX_HEIGHT 24
*/

// 标题图片
extern IMAGE game_title;

// 菜单背景图片
extern IMAGE menu_bk_image;
// 团队介绍背景图片
extern IMAGE team_bk_image;

// 主角图片
extern IMAGE imgKid;

// 尖刺 : 四个朝向的图片
extern IMAGE imgSpikeUp;
extern IMAGE imgSpikeLeft;
extern IMAGE imgSpikeDown;
extern IMAGE imgSpikeRight;

// 苹果
extern IMAGE imgApple;

// 地面图片
extern IMAGE imgGround;

// 存档点图片
extern IMAGE imgSavedPoint;
extern IMAGE imgUnsavedPoint;

// 终点
extern IMAGE imgEndPoint;

// 菜单界面的若干按钮图片
//...
// 图片路径（根据实际资源填写）

// 第一关元素全局变量
// 1. 终点（EndPoint）：坐标(x=1100, y=300)，尺寸(60×80)
extern vector<EndPoint> ep1;
// 2. 存档点（SavePoint）：2个存档点，分别在中途和终点前
extern vector<SavePoint> sp1;
// 3. 普通地面（NormalGround）：多个平台和地面
extern vector<NormalGround> ng1;
// 4. 可消失地面（DisappearingGround）：延迟30帧（0.5秒）消失
extern vector<DisappearingGround> dg1;
// 5. 隐藏地面（HiddenGround）：接触后显示
extern vector<HiddenGround> hg1;
// 6. 矩形静态陷阱（RectangleTrap）：固定位置的陷阱
extern vector<RectangleTrap> rt1;
// 7. 三角形静态陷阱（TriangleTrap）：斜坡或角落的陷阱
extern vector<TriangleTrap> tt1;
// 8. 矩形可触发陷阱（TriggerableRectangleTrap）：进入触发区域后移动
extern vector<TriggerableRectangleTrap> trt1;
// 9. 三角形可触发陷阱（TriggerableTriangleTrap）：进入触发区域后移动
extern vector<TriggerableTriangleTrap> ttt1;
 


