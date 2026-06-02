
#include <Windows.h>
#include <graphics.h>
#include <string>
#include <iostream>
#include "global.h"
#include "utils.h"
using namespace std;

// 视图相关头文件
#include "view.h"
#include "viewManager.h"
#include "MenuView.h"


string myvolumn = "50";
string sound = "50";
string mymusictype;

int volume_int;
int sound_int;
vector<string> BGM = { "Normal1.MP3" , "Normal2.mp3", "Normal3.mp3" };
vector<string> BGMname = { "Normal1", "Normal2", "Normal3" };
int BGM_ptr = 0;

// 全局对象实例
ViewManager view_manager;

vector<EndPoint> ep1;
// 2. 存档点（SavePoint）：2个存档点，分别在中途和终点前
vector<SavePoint> sp1;
// 3. 普通地面（NormalGround）：多个平台和地面
vector<NormalGround> ng1;
// 4. 可消失地面（DisappearingGround）：延迟30帧（0.5秒）消失
vector<DisappearingGround> dg1;
// 5. 隐藏地面（HiddenGround）：接触后显示
vector<HiddenGround> hg1;
// 6. 矩形静态陷阱（RectangleTrap）：固定位置的陷阱
vector<RectangleTrap> rt1;
// 7. 三角形静态陷阱（TriangleTrap）：斜坡或角落的陷阱
vector<TriangleTrap> tt1;
// 8. 矩形可触发陷阱（TriggerableRectangleTrap）：进入触发区域后移动
vector<TriggerableRectangleTrap> trt1;
// 9. 三角形可触发陷阱（TriggerableTriangleTrap）：进入触发区域后移动
vector<TriggerableTriangleTrap> ttt1;

// 补充
vector<SpeedUpGround> sg1 = {};

/*测试用例*/
int ChosenCurrentMap = 1;       // 默认第一关
/*测试用例*/
//Map CurrentMap(IMAGE(), BG1_PATH, false, 100, 600); // 初始地图（出生点x=100,y=600）
IMAGE bgImage;
IMAGE game_title;

string bgPath;

Map CurrentMap;

Player kid;                 // 玩家对象（具体初始化根据Player类定义）




void MapLoder()
{
    loadimage(&bgImage, _T(BG1_PATH), WINDOW_WIDTH, WINDOW_HEIGHT);
    bgPath = BG1_PATH;

    // initLevel1();

    //CurrentMap = Map(bgImage, bgPath, false, 0, 0);

    CurrentMap = Map(bgImage, bgPath, false, 0, 0
        );

    kid = Player(CurrentMap);
    
}
void musicLoader()
{
    // 初始化音量
    volume_int = INIT_VOLUME;
    sound_int = INIT_SOUND;

    myvolumn = to_string(volume_int);
    sound = to_string(sound_int);
    mymusictype = BGMname[0];
    string musicName = BGM[0];

    // BGM
    char mp3Path[100];
    sprintf_s(mp3Path, sizeof(mp3Path), "Assert/musics/%s", musicName.c_str());        // c_str 把 string 转为 char*, 可以被格式化字符串识别

    char cmd[200];
    sprintf_s(cmd, "open \"%s\" alias music", mp3Path);
    mciSendString(cmd, 0, 0, 0);

    // 其他音效导入
    mciSendString("open \"Assert/musics/Death.mp3\" alias deathMusic", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndBreak.MP3\" alias blockBreakSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndTriggerTrap.MP3\" alias trapTriggeredSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndJump.MP3\" alias jumpSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndDoubleJump.MP3\" alias doubleJumpSound", 0, 0, 0);
    mciSendString("open \"Assert/musics/sndBlockAppear.MP3\" alias blockAppearSound", 0, 0, 0);
    

    // 初始化音量
    char s[100];
    sprintf_s(s, "setaudio music volume to %d", volume_int * 10);
    mciSendString(s, 0, 0, 0);
    sprintf_s(s, "setaudio deathMusic volume to %d", (volume_int-5) * 10);
    mciSendString(s, 0, 0, 0);

    mciSendString("play music repeat", 0, 0, 0);    // 播放音乐


    

}

int main() {
    // 初始化图形界面
    initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
    musicLoader();
    MapLoder();
    // 加载所有资源
    loadAllResources();

    // 设置中文字体
    settextstyle(20, 0, _T("微软雅黑"));

    // 直接通过ViewManager切换到菜单视图

    /*测试用例*/
    view_manager.switch_to(ViewManager::ViewType::Menu);
   
    /*测试用例*/

    // 游戏主循环
    ExMessage msg;

   


    //打开碰撞箱绘制
    /*测试用例*/
    BOX_DRAW_OFF;  
    /*测试用例*/

    //============================
    // 鼠标按键逻辑修改 : 
    // 负责人 Mer
    bool mouse_click = true;
    //============================

    

    while (true) {
        
        BeginBatchDraw();
        DWORD start_time = GetTickCount64();

        // 接受并处理消息
        while (peekmessage(&msg)) {
            peekmessage(&msg);

        }
        // 更新游戏状态

        //=====================================================================
        // 若玩家没有松开鼠标, 则不处理该左键信号, 避免多个按钮重叠时界面切换过快
        // 负责人 : Mer
        
        if (mouse_click || msg.message != WM_LBUTTONDOWN)
        {
            view_manager.handleInput(msg);
        }
        if (msg.message == WM_LBUTTONDOWN) { mouse_click = false; }
        else { mouse_click = true; }
        //=====================================================================

        view_manager.update();

        // 绘制游戏
        //cleardevice();    //清屏→空白→绘制”的短暂间隙 会卡，所以直接draw绘制覆盖
        view_manager.draw();
        FlushBatchDraw();




        // 控制帧率
        DWORD end_time = GetTickCount64();
        DWORD delta_time = end_time - start_time;
        if (delta_time < 1000 / 30) {  // 60 FPS
            Sleep(1000 / 30 - delta_time);
        }
    }



    EndBatchDraw();
    closegraph();
    return 0;
}