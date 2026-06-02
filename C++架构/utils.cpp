#include "global.h"
#include "utils.h"


IMAGE menu_bk_image;
IMAGE team_bk_image;


void initLevel1() {
    ep1.clear();
    sp1.clear();
    ng1.clear();
    dg1.clear();
    hg1.clear();
    rt1.clear();
    tt1.clear();
    trt1.clear();
    ttt1.clear();
    // 1. 终点初始化：坐标(1100, 300)，尺寸60×80
    ep1 = {
        EndPoint(700,382,32,32)
    };

    // 2. 存档点初始化：2个存档点
    sp1 = {
        SavePoint(400, 382, 32, 32),   // 第一个存档点：坐标(300,500)，尺寸40×40
        //SavePoint(800, 400, 40, 40)    // 第二个存档点：坐标(800,400)，尺寸40×40
    };

    // 3. 普通地面初始化：底部地面+3个平台
    ng1 = {
        NormalGround(0, 350, 800, 32),  // 草皮
        NormalGround(150, 170, 192, 32), // 平台一
        NormalGround(270, 238, 192, 32),  // 平台二
        NormalGround(0, 382, 800, 218), // 地基
    };

    // 4. 可消失地面：延迟30帧消失
    dg1 = {
        //DisappearingGround(400, 600, 100, 30, 30), // 坐标(400,600)，延迟30帧
        //DisappearingGround(700, 500, 100, 30, 30)  // 坐标(700,500)，延迟30帧
    };

    // 5. 隐藏地面：初始不可见，接触后显示
    hg1 = {
        //HiddenGround(650, 600, 100, 30),  // 坐标(650,600)，隐藏平台
        //HiddenGround(900, 300, 100, 30)   // 坐标(900,300)，隐藏平台
    };

    // 6. 矩形静态陷阱：固定位置（如地面缝隙中的尖刺）
    rt1 = {
        // 碰撞箱(150,720,30,30)，贴图位置(150,720,30,30)
        /*RectangleTrap(Rect(150, 720, 30, 30), Rect(150, 720, 30, 30)),
        RectangleTrap(Rect(450, 720, 30, 30), Rect(450, 720, 30, 30))*/
    };

    // 7. 三角形静态陷阱：斜坡上的尖刺（顶点坐标定义三角形）
    tt1 = {
        // 三角形顶点(300,700), (330,700), (315,670)，贴图位置(300,670,30,30)
        TriangleTrap(Triangle(302,170, 334,170, 318,138), Rect(302,138,32,32), TRIANGLE_DIRECT_UP),
        TriangleTrap(Triangle(270,270, 302,270, 286,238), Rect(270,238,32,32), TRIANGLE_DIRECT_UP)
    };

    // 8. 矩形可触发陷阱：触发区域进入后向右移动
    trt1 = {
        // 碰撞箱(600, 650, 40, 40)，贴图位置(600,650,40,40)，触发区域(550,600,100,100)
       /* TriggerableRectangleTrap(
            Rect(600, 650, 40, 40),
            Rect(600, 650, 40, 40),
            Rect(550, 600, 100, 100)
        )*/
    };
    // 初始化矩形可触发陷阱的移动参数
    //TriggerableRectangleTrap& trt1_0 = trt1[0];
    //trt1_0.moveSpeedX = 3;    // 水平速度3像素/帧（向右）
    //trt1_0.moveSpeedY = 0;    // 垂直速度0
    //trt1_0.triggeredState = TriggeredState::MOVE; // 触发后移动

    // 9. 三角形可触发陷阱：触发区域进入后向下移动
    //std::vector<TriggerableTriangleTrap> ttt1 = {
    //    // 三角形碰撞箱(950,500), (980,500), (965,470)，贴图位置(950,470,30,30)，触发区域(900,450,100,100)
    //    TriggerableTriangleTrap(
    //        Triangle(950,500, 980,500, 965,470),
    //        Rect(950,470,30,30),
    //        Rect(900,450,100,100)
    //    )
    //};
    // 初始化三角形可触发陷阱的移动参数
    //TriggerableTriangleTrap& ttt1_0 = ttt1[0];
    //ttt1_0.moveSpeedX = 0;     // 水平速度0
    //ttt1_0.moveSpeedY = 2;     // 垂直速度2像素/帧（向下）
    //ttt1_0.triggeredState = TriggeredState::MOVE; // 触发后移动
}

void loadAllResources() { 
    // load_image
    //kid的各种状态图片的加载
    loadimage(&imgLeftStandSpirit[0], _T(IMG_LEFT_STAND_KID_PATH1), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgLeftStandSpirit[1], _T(IMG_LEFT_STAND_KID_PATH2), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgRightStandSpirit[0], _T(IMG_RIGHT_STAND_KID_PATH1), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgRightStandSpirit[1], _T(IMG_RIGHT_STAND_KID_PATH2), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgLeftMoveSpirit[0], _T(IMG_LEFT_MOVE_KID_PATH1), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgLeftMoveSpirit[1], _T(IMG_LEFT_MOVE_KID_PATH2), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgRightMoveSpirit[0], _T(IMG_RIGHT_MOVE_KID_PATH1), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgRightMoveSpirit[1], _T(IMG_RIGHT_MOVE_KID_PATH2), KID_SIZE_X, KID_SIZE_Y);

    loadimage(&imgJumpSpirit[LEFT], _T(IMG_LEFT_JUMP_KID_PATH), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgJumpSpirit[RIGHT], _T(IMG_RIGHT_JUMP_KID_PATH), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgFallSpirit[LEFT], _T(IMG_LEFT_FALL_KID_PATH), KID_SIZE_X, KID_SIZE_Y);
    loadimage(&imgFallSpirit[RIGHT], _T(IMG_RIGHT_FALL_KID_PATH), KID_SIZE_X, KID_SIZE_Y);
}

/* 图像绘制工具函数
*  功能：绘制带Alpha通道的图像（支持透明/半透明效果），解决EasyX默认putimage不支持透明度的问题
*  参数：
*    x, y - 目标绘制区域的左上角坐标
*    img - 指向IMAGE对象的指针，存储待绘制的图像（需包含Alpha通道，如PNG格式）
*/
void putimage_new(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}



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
bool inArea(int x, int y, int l, int t, int r, int b) {
    // 坐标需同时满足：在左边界右侧、右边界左侧、上边界下方、下边界上方（不含边界）
    return (x > l && x < r && y > t && y < b);
}

Triangle Rect2Tri(Rect rec)
{
    // 正三角
    int x1 = rec.x + rec.width / 2;
    int y1 = rec.y;
    int x2 = rec.x;
    int y2 = rec.y + rec.height;
    int x3 = rec.x + rec.width;
    int y3 = rec.y + rec.height;
    return Triangle(x1, y1, x2, y2, x3, y3);
}

void setAudio(int vol)
{
    // 设置音效大小

    /*mciSendString("open \"Assert/musics/Death.mp3\" alias deathMusic", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndBreak.MP3\" alias blockBreakSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndTriggerTrap.MP3\" alias trapTriggeredSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndJump.MP3\" alias jumpSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndDoubleJump.MP3\" alias doubleJumpSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndBlockAppear.MP3\" alias blockAppearSound", 0, 0, 0);*/

    vector<string> SoundList = { "blockBreakSound", "trapTriggeredSound", "jumpSound","doubleJumpSound", "blcokApeearSound" };
    char cmd[100];
    for (string snd : SoundList)
    {
        sprintf_s(cmd, sizeof(cmd), "setaudio %s volume to %d", snd.c_str(), vol * 10);
        mciSendString(cmd, 0, 0, 0);
    }

}

