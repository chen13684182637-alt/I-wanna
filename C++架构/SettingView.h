//设置界面
#pragma once
#include "View.h"
#include "button.h"
#include "global.h"
#include"utils.h"
#include <chrono>
#include <tchar.h>
#include <conio.h>

//mciSendString();



//=========================================================================================================
/*   存放settingview中需要使用的宏定义和：长条的长410宽30、每列间距30、每行间距80、文字区长60宽46、
	 悬钮长10宽52、功能按键1长120宽48、界面中心位置750，500、三角形按钮长45宽46、矩形长100宽46、
	 功能按键2长240宽96   */


#define BAR_LENGTH         210     // 长条的长度
#define BAR_WIDTH          20      // 长条的宽度
#define COLUMN_SPACING     30      // 每列之间的间距
#define ROW_SPACING        80      // 每行之间的间距
#define TEXT_AREA_LENGTH   30      // 文字区长度
#define TEXT_AREA_WIDTH    24      // 文字区宽度
#define HOVER_BUTTON_LENGTH 10     // 悬钮长度
#define HOVER_BUTTON_WIDTH  40     // 悬钮宽度
#define FUNC_BUTTON1_LENGTH 120    // 功能按键1长度
#define FUNC_BUTTON1_WIDTH  60     // 功能按键1宽度
#define SCREEN_CENTER_X    WINDOW_WIDTH/2   // 界面中心X坐标
#define SCREEN_CENTER_Y    WINDOW_HEIGHT/2    // 界面中心Y坐标
#define TRIANGLE_BUTTON_LENGTH 36  // 三角形按钮长度
#define TRIANGLE_BUTTON_WIDTH  34  // 三角形按钮宽度
#define RECTANGLE_LENGTH   50     // 矩形长度
#define RECTANGLE_WIDTH    34      // 矩形宽度
#define FUNC_BUTTON2_LENGTH 180    // 功能按键2长度
#define FUNC_BUTTON2_WIDTH  56     // 功能按键2宽度




class SettingView : public View {
public:
	// enter()、exit()、handleInput()、update()、draw()
	SettingView() = default;
	~SettingView() = default;

	void enter() override;
	void update() override;
	void draw()override;
	void handleInput(ExMessage& msg) override;
	void exit() override;


	//=====================封装一个一站式画图函数和绘制文字函数===================

	void PICTURE(IMAGE* pimg, int x, int y) {

		putimage_new(x, y, pimg);

	}


	void drawText(int rect_x, int rect_y, int rect_length, int rect_width,
		const std::string& text, COLORREF text_color = BLACK, int font_size = 26)
	{
		int center_x = rect_x + rect_length / 2;
		int center_y = rect_y + rect_width / 2;

		settextcolor(text_color);
		settextstyle(font_size, 0, _T("宋体"));

		const char* c_str = text.c_str();
		const TCHAR* t_str = _T(c_str);

		int text_width = textwidth(t_str);
		int text_height = textheight(t_str);

		int text_x = center_x - text_width / 2;
		int text_y = center_y - text_height / 2;

		outtextxy(text_x, text_y, t_str);
	}

private:
	//调节音量图标
	IMAGE setvolumn;
	//调节音效图标
	IMAGE setsound;
	// 切换音乐图标
	IMAGE changemusic;
	//音量调节悬钮
	IMAGE  volumnLatch;
	// 音效调节悬钮
	IMAGE  soundLatch;
	//音效调节长条
	IMAGE volumnStrip;
	//音量调节长条
	IMAGE soundStrip;
	//========================
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

	//===============疑似用不上=====
	// 背景图
	IMAGE settingBg;



};


