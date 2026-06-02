//游戏设置
#pragma once
#include "SettingView.h"
#include "global.h"
#include "utils.h"
#include "viewManager.h"
#include "Windows.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
//=========================================================================================================
// 初始化暂停界面，设置按钮位置等
// 具体 : 
// 设置背景为 SKYBLUE 纯色
// 调用 draw() 方法绘制基本界面
//==========================================================================================================

//初始化settingview界面参数
void SettingView::enter() {
	//
	settingBg = (WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&settingBg, "./Assert/images/bg1.png", WINDOW_WIDTH, WINDOW_HEIGHT);
	//图标IMAGE 长宽 width、height
	setvolumn = (FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH); /*getwidth(), getheight()*/
	loadimage(&setvolumn, "./Assert/Button/setvolumn.png", FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH);
	//string setvolumnpath = ;
	setsound = IMAGE(FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH);
	loadimage(&setsound, "./Assert/Button/yinxiao.png", FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH);
	//string setsoundpath = ;
	changemusic = IMAGE(FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH);
	loadimage(&changemusic, "./Assert/Button/musicbutton.png", FUNC_BUTTON1_LENGTH, FUNC_BUTTON1_WIDTH);
	//string changemusicpath = ;
	volumnLatch = IMAGE(HOVER_BUTTON_LENGTH, HOVER_BUTTON_WIDTH);
	loadimage(&volumnLatch, "./Assert/Button/xuanniu.png", HOVER_BUTTON_LENGTH, HOVER_BUTTON_WIDTH);
	//string volumnLatchpath = ;
	soundLatch = IMAGE(HOVER_BUTTON_LENGTH, HOVER_BUTTON_WIDTH);
	loadimage(&soundLatch, "./Assert/Button/xuanniu.png", HOVER_BUTTON_LENGTH, HOVER_BUTTON_WIDTH);
	//	string soundLatchpath = ;
	volumnStrip = IMAGE(BAR_LENGTH, BAR_WIDTH);
	loadimage(&volumnStrip, "./Assert/Button/yinliangtiao.png", BAR_LENGTH, BAR_WIDTH);
	//string volumnStrippath = ;
	soundStrip = IMAGE(BAR_LENGTH, BAR_WIDTH);
	loadimage(&soundStrip, "./Assert/Button/yinliangtiao.png", BAR_LENGTH, BAR_WIDTH);
	//string soundStrippath = ;
	//按钮ImageButton x、y、w、h、路径，drawBtton、ButtonClicked
	/*
		BAR_LENGTH         410     // 长条的长度
#define BAR_WIDTH          30      // 长条的宽度
#define COLUMN_SPACING     30      // 每列之间的间距
#define ROW_SPACING        80      // 每行之间的间距
#define TEXT_AREA_LENGTH   60      // 文字区长度
#define TEXT_AREA_WIDTH    46      // 文字区宽度
#define HOVER_BUTTON_LENGTH 10     // 悬钮长度
#define HOVER_BUTTON_WIDTH  52     // 悬钮宽度
#define FUNC_BUTTON1_LENGTH 120    // 功能按键1长度
#define FUNC_BUTTON1_WIDTH  48     // 功能按键1宽度
#define SCREEN_CENTER_X    750     // 界面中心X坐标
#define SCREEN_CENTER_Y    500     // 界面中心Y坐标
#define TRIANGLE_BUTTON_LENGTH 45  // 三角形按钮长度
#define TRIANGLE_BUTTON_WIDTH  46  // 三角形按钮宽度
#define RECTANGLE_LENGTH   100     // 矩形长度
#define RECTANGLE_WIDTH    46      // 矩形宽度
#define FUNC_BUTTON2_LENGTH 240    // 功能按键2长度
#define FUNC_BUTTON2_WIDTH  96     // 功能按键2宽度
*/
	menuButton = ImageButton(SCREEN_CENTER_X - FUNC_BUTTON2_LENGTH / 2 - 4, SCREEN_CENTER_Y + ROW_SPACING * 2 - FUNC_BUTTON2_WIDTH / 2 + 30, FUNC_BUTTON2_LENGTH + 2, 10 + FUNC_BUTTON2_WIDTH, "./Assert/Button/ReturnButton.png");
	continueButton = ImageButton(SCREEN_CENTER_X - FUNC_BUTTON2_LENGTH / 2, SCREEN_CENTER_Y + ROW_SPACING - FUNC_BUTTON2_WIDTH / 2 + 20, FUNC_BUTTON2_LENGTH - 4, 6 + FUNC_BUTTON2_WIDTH, "./Assert/Button/returngame.png");
	//============
	volumeUpButton = ImageButton(SCREEN_CENTER_X + 150 - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 3 + RECTANGLE_LENGTH + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonright.png");//音量加
	volumeDownButton = ImageButton(SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING, SCREEN_CENTER_Y - ROW_SPACING - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonleft.png");//音量减
	//================
	soundUpButton = ImageButton(SCREEN_CENTER_X + 150 - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 3 + RECTANGLE_LENGTH + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING * 2 - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonright.png");//音效加
	soundDownButton = ImageButton(SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING, SCREEN_CENTER_Y - ROW_SPACING * 2 - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonleft.png");
	//===============
	Lturnmusic = ImageButton(SCREEN_CENTER_X - (FUNC_BUTTON1_LENGTH + TEXT_AREA_LENGTH + COLUMN_SPACING * 3 + TRIANGLE_BUTTON_LENGTH * 2) / 2 + COLUMN_SPACING + FUNC_BUTTON1_LENGTH, SCREEN_CENTER_Y - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonleft.png");
	Rturnmusic = ImageButton(SCREEN_CENTER_X - (FUNC_BUTTON1_LENGTH + TEXT_AREA_LENGTH + COLUMN_SPACING * 3 + TRIANGLE_BUTTON_LENGTH * 2) / 2 + FUNC_BUTTON1_LENGTH + TRIANGLE_BUTTON_LENGTH + COLUMN_SPACING * 4 - 10 + TEXT_AREA_LENGTH, SCREEN_CENTER_Y - TRIANGLE_BUTTON_WIDTH / 2, TRIANGLE_BUTTON_LENGTH, TRIANGLE_BUTTON_WIDTH, "./Assert/Button/mybuttonright.png");

	//// 返回主菜单按钮
//	menuButton = ImageButton;
//	// 继续游戏按钮
//	continueButton = ImageButton;
//	// 增大音量按钮
//	volumeUpButton = ImageButton;
//	// 减小音量按钮
//	volumeDownButton = ImageButton;
//	// 增大音效按钮
//	soundUpButton = ImageButton;
//	// 减小音效按钮
//	soundDownButton = ImageButton;
//	// 向左切换音乐按钮
//	Lturnmusic = ImageButton;
//	// 向右切换音乐按钮
//	Rturnmusic = ImageButton;


	// 播放音乐




}
//===========================================================================================================
// 更新界面 : 当音量的大小和音效值被 handleInput 改变时, 需要修改显示在界面上的音量音效值.
// 具体 : 这个函数应该被 handleInput 接受到玩家调整音量的信息, 改变了值大小后 再调用更新屏幕上显示的数值.
	// 请先确保在 main.cpp 或者 global.h 其中之一写上代表整个程序的 音量值和音效值大小变量 int volumn , sound; 的定义
	// update 的任务是将当前 volumn 和 sound 的值输出到 设置界面的屏幕上. 
		// 1. 先用easyx内置的矩形绘制函数, 颜色设置为与背景一致 (颜色参数可用 SKYBLUE), 涉及到覆盖旧的音量和音效大小数值.
		// 2. 再将当前的 volumn 和 sound 输出到被覆盖的位置上.
//===========================================================================================================





void SettingView::update() {

	// 这句代码意思是设置背景颜色为 SKYBLUE. SKYBLUE是定义在 global.h 中的一个宏. 


}




//===========================================================================================================
// 绘制设置界面，放置设置背景图和各个按钮，绘制当前音量和音效值的条形图，显示当前播放的音乐
// 具体 : 需要绘制的内容和按钮包括
	// 音乐大小显示, 音乐大小调节按钮
	// 音效大小显示, 音效大小调节按钮
	// "返回主菜单"按钮
	// 按钮下面文字显示:"按 ESC 返回主菜单"
// 要求 : 按钮居中, 大小适当. 可以用 豆包 AI 生成按钮图片资源+ ImageButton (建议), 或者直接 TextButton 都可
//===========================================================================================================



void SettingView::draw() {
	//===========图标和按钮
	putimage(0, 0, &settingBg);
	menuButton.drawButton();
	continueButton.drawButton();
	volumeUpButton.drawButton();
	volumeDownButton.drawButton();
	soundUpButton.drawButton();
	soundDownButton.drawButton();
	Lturnmusic.drawButton();
	Rturnmusic.drawButton();



	PICTURE(&setvolumn, SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2, SCREEN_CENTER_Y - ROW_SPACING - FUNC_BUTTON1_WIDTH / 2);
	PICTURE(&setsound, SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2, SCREEN_CENTER_Y - ROW_SPACING * 2 - FUNC_BUTTON1_WIDTH / 2);
	PICTURE(&changemusic, SCREEN_CENTER_X - (FUNC_BUTTON1_LENGTH + TEXT_AREA_LENGTH + COLUMN_SPACING * 3 + TRIANGLE_BUTTON_LENGTH * 2) / 2, SCREEN_CENTER_Y - FUNC_BUTTON1_WIDTH / 2);
	//===================
	PICTURE(&volumnStrip, SCREEN_CENTER_X - 10 - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 2 + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING - BAR_WIDTH / 2);
	PICTURE(&soundStrip, SCREEN_CENTER_X - 10 - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 2 + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING * 2 - BAR_WIDTH / 2);
	//==================
	PICTURE(&volumnLatch, SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 2 + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING - HOVER_BUTTON_WIDTH / 2);
	PICTURE(&soundLatch, SCREEN_CENTER_X - (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 + FUNC_BUTTON1_LENGTH + COLUMN_SPACING * 2 + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - ROW_SPACING * 2 - HOVER_BUTTON_WIDTH / 2);

	/*
		BAR_LENGTH         410     // 长条的长度
#define BAR_WIDTH          30      // 长条的宽度
#define COLUMN_SPACING     30      // 每列之间的间距
#define ROW_SPACING        80      // 每行之间的间距
#define TEXT_AREA_LENGTH   60      // 文字区长度
#define TEXT_AREA_WIDTH    46      // 文字区宽度
#define HOVER_BUTTON_LENGTH 10     // 悬钮长度
#define HOVER_BUTTON_WIDTH  52     // 悬钮宽度
#define FUNC_BUTTON1_LENGTH 120    // 功能按键1长度
#define FUNC_BUTTON1_WIDTH  48     // 功能按键1宽度
#define SCREEN_CENTER_X    750     // 界面中心X坐标
#define SCREEN_CENTER_Y    500     // 界面中心Y坐标
#define TRIANGLE_BUTTON_LENGTH 45  // 三角形按钮长度
#define TRIANGLE_BUTTON_WIDTH  46  // 三角形按钮宽度
#define RECTANGLE_LENGTH   100     // 矩形长度
#define RECTANGLE_WIDTH    46      // 矩形宽度
#define FUNC_BUTTON2_LENGTH 240    // 功能按键2长度
#define FUNC_BUTTON2_WIDTH  96     // 功能按键2宽度
*/
//文字绘制
//音量
	drawText(SCREEN_CENTER_X + (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 - TEXT_AREA_LENGTH - 60, SCREEN_CENTER_Y + 6 - ROW_SPACING - RECTANGLE_WIDTH / 2, TEXT_AREA_LENGTH, TEXT_AREA_WIDTH,
		to_string(volume_int));
	//音效
	drawText(SCREEN_CENTER_X + (TRIANGLE_BUTTON_LENGTH * 2 + COLUMN_SPACING * 4 + BAR_LENGTH + FUNC_BUTTON1_LENGTH + RECTANGLE_LENGTH) / 2 - TEXT_AREA_LENGTH - 60, SCREEN_CENTER_Y + 6 - ROW_SPACING * 2 - RECTANGLE_WIDTH / 2, TEXT_AREA_LENGTH, TEXT_AREA_WIDTH,
		to_string(sound_int));
	//音乐
	drawText(SCREEN_CENTER_X - (FUNC_BUTTON1_LENGTH + TEXT_AREA_LENGTH + COLUMN_SPACING * 3 + TRIANGLE_BUTTON_LENGTH * 2) / 2 + COLUMN_SPACING * 2 + FUNC_BUTTON1_LENGTH + TRIANGLE_BUTTON_LENGTH, SCREEN_CENTER_Y - TRIANGLE_BUTTON_WIDTH / 2, RECTANGLE_LENGTH, RECTANGLE_WIDTH,
		mymusictype);
	//播放音乐


}
//===========================================================================================================
// 处理设置界面输入，主要处理各个按钮的点击事件
// 具体 : 需要处理的事件包括以下几点
	// 1. 玩家点击按钮, 包括音乐/音效大小调整按钮 和返回主菜单按钮, 事件处理逻辑自行完成, 界面跳转的代码可以参考其他 view 类 cpp 文件.
	//		调整音量大小时需要更新 volumn, sound 变量, 然后调用 update() 方法重新绘制音量值
	// 2. 玩家点击键盘 ESC 键, 功能等同与点击返回主菜单按钮.
//===========================================================================================================




void SettingView::handleInput(ExMessage& msg) {
	//开始监测
	if (msg.vkcode == 'J')
	{
		mciSendString("play jumpSound repeat", 0, 0, 0);
	}
	if (msg.message == WM_LBUTTONDOWN) {
		//返回游戏(开始游戏，先从存档点进入）
		if (continueButton.ButtonClicked(msg)) {

			view_manager.switch_to(ViewManager::ViewType::Save);

			return;
		}
		//返回主菜单
		if (menuButton.ButtonClicked(msg)) {


			view_manager.switch_to(ViewManager::ViewType::Menu);
			return;
		}
		//================================================
		/*
	// 返回主菜单按钮
	ImageButton menuButton;
	// 继续游戏按钮
	ImageButton continueButton;
	// 增大音量按钮
	ImageButton volumeUpButton;
	// 减小音量按钮
	ImageButton volumeDownButton;
	// 增大音效按钮
	ImageButton soundUpButton;
	// 减小音效按钮
	ImageButton soundDownButton;
	// 向左切换音乐按钮
	ImageButton Lturnmusic;
	// 向右切换音乐按钮
	ImageButton Rturnmusic;
	*/
		if (volumeUpButton.ButtonClicked(msg)) {
			// 增大音乐音量

			if (volume_int >= 100) return;
			volume_int++;
			char s[100];
			sprintf_s(s, "setaudio music volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			sprintf_s(s, "setaudio deathMusic volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			return;
		}
		if (volumeDownButton.ButtonClicked(msg))
		{

			if (volume_int <= 0) return;
			volume_int--;
			char s[100];
			sprintf_s(s, "setaudio music volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			sprintf_s(s, "setaudio deathMusic volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			return;
		}

		if (soundUpButton.ButtonClicked(msg)) {

			if (sound_int >= 100) return;
			sound_int++;
			setAudio(sound_int);
			return;
		}
		if (soundDownButton.ButtonClicked(msg))
		{
			if (sound_int <= 0) return;
			sound_int--;
			setAudio(sound_int);
			return;
		}
		if (Lturnmusic.ButtonClicked(msg)) {

			BGM_ptr = (BGM_ptr - 1) % BGMname.size();
			mymusictype = BGMname[BGM_ptr];
			string musicName = BGM[BGM_ptr];

			// BGM
			char mp3Path[100];
			sprintf_s(mp3Path, sizeof(mp3Path), "Assert/musics/%s", musicName.c_str());        // c_str 把 string 转为 char*, 可以被格式化字符串识别

			char cmd[200];
			mciSendString("stop music",0,0,0);
			mciSendString("close music", 0, 0, 0);
			sprintf_s(cmd, "open \"%s\" alias music", mp3Path);
			mciSendString(cmd, 0, 0, 0);
			mciSendString("play music repeat", 0, 0, 0);
			char s[100];
			sprintf_s(s, "setaudio music volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			return;
		}
		if (Rturnmusic.ButtonClicked(msg))
		{
			BGM_ptr = (BGM_ptr+1) % BGMname.size();
			mymusictype = BGMname[BGM_ptr];
			string musicName = BGM[BGM_ptr];

			// BGM
			char mp3Path[100];
			sprintf_s(mp3Path, sizeof(mp3Path), "Assert/musics/%s", musicName.c_str());        // c_str 把 string 转为 char*, 可以被格式化字符串识别

			char cmd[200];
			mciSendString("stop music", 0, 0, 0);
			mciSendString("close music", 0, 0, 0);
			sprintf_s(cmd, "open \"%s\" alias music", mp3Path);
			mciSendString(cmd, 0, 0, 0);
			mciSendString("play music repeat", 0, 0, 0);
			char s[100];
			sprintf_s(s, "setaudio music volume to %d", volume_int * 10);
			mciSendString(s, 0, 0, 0);
			return;
		}

	}




}
//==================================================================
// 退出设置界面，释放资源
// 具体 : 调用 easyx 内置函数清空屏幕为 SKYBLUE 纯背景色.
void SettingView::exit() {
	setbkcolor(SKYBLUE);
	cleardevice();
}
//=====================================================================

