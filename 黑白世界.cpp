#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <mmsystem.h>//包含多媒体设备接口文件
//#include "MoseCode.h"
//#include "Snake.h"

#pragma comment (lib, "WINMM.LIB")//加载静态库


#define SCREEN_WIDTH 880//ori 800
#define SCREEN_HEIGHT 715 //ori 650
#define ROW 9
#define COL 12
#define BLOCK_SIZE 55
#define OBJECT_SIZE 40
#define CEN_DELTABO (BLOCK_SIZE-OBJECT_SIZE)/2
#define START_X 40
#define START_Y 40
#define CONDITIONS 2
#define CUSTOMS 4

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40//统一宽度100，高度40
#define CUSTOM_WIDTH 150
#define CUSTOM_HEIGHT 150
#define BUTTON_X1 375
#define BUTTON_X2 BUTTON_X1+BUTTON_WIDTH //x2-x2==按钮宽度
#define BUTTON_ONEY1 240
#define BUTTON_ONEY2 BUTTON_ONEY1+BUTTON_HEIGHT//Y2-Y1==各个按钮的高度
#define BUTTON_TWOY1 320
#define BUTTON_TWOY2 BUTTON_TWOY1+BUTTON_HEIGHT
#define BUTTON_THREEY1 400
#define BUTTON_THREEY2 BUTTON_THREEY1+BUTTON_HEIGHT
#define BUTTON_FOURY1 480
#define BUTTON_FOURY2 BUTTON_FOURY1+BUTTON_HEIGHT
#define CUSTOM_X1 350
#define CUSTOM_X2 CUSTOM_X1+CUSTOM_WIDTH
#define CUSTOM_Y1 240
#define CUSTOM_Y2 CUSTOM_Y1+CUSTOM_HEIGHT


#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_C 'c'
#define KEY_E 'e'
#define KEY_P 'p'
#define KEY_R 'r'


//读取关卡
#define ROW 9 // 定义行数
#define COL 12 // 定义列数
#define LAY 2 // 定义层数


enum _character{
	BLACKWALL,
	WHITEWALL,
	BLACKBOX,
	WHITEBOX,
	COMMONPLAYER,
	BLACKPLAYER,
	WHITEPLAYER,
	STARPLAYER,
	BLACKTARGET,
	WHITETARGET,
	ALL
};

enum _key {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CHANGE,
	LINK,
	PAUSE,
	ESC
};

enum _background {
	CUSTOM0,
	CUSTOM1,
	CUSTOM2,
	CUSTOM3,
	MENU,
	CHOOSE,
	DARK,
	LIGHT,
	ALLBACK
};



struct _pos{
	int x;
	int y;
}blackbox, whitebox,whitetarget,blacktarget, nextpos, nenepos;

struct Man {
	struct _pos manpos;
	int C_BW;//人物状态common/black/white
}man;

typedef struct Man Man;
typedef enum _charater charater;
typedef struct _pos Pos;
//enum _character {
//	BLACKWALL,//0
//	WHITEWALL,//1
//	BLACKBOX,//2
//	WHITEBOX,//3
//	COMMONPLAYER,//4
//	BLACKPLAYER,//5
//	WHITEPLAYER,//6
//	BLACKTARGET,//7    [7][2]
//	WHITETARGET,//8    [1][9]
//	ALL//9
//};
//地图中先不放方块和人物物体，后面再放入,那么需要object的各个位置定义






int map[CONDITIONS][ROW][COL] = {
	{{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,1} },
	{{1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,1}}
};

IMAGE images[ALL];
IMAGE background[ALLBACK];
IMAGE pauseimage;

int custom;//关卡变量初始都为0
int condition = 0;//黑白变量
int secret = 0;//通过最后一关是否给出摩斯密码



//待完成函数*****************************************************
void Gettext() {
	// 定义字符串缓冲区，并接收用户输入
	//settextstyle(16,0,("宋体") );//设置字体
	char s[35];
	InputBox(s, 35, "请输入摩斯符号(输入格式形如:.- ..):","密码栏",NULL, 600, 400);
	Sleep(300);//避免退出冲突
	if (strcmp(s, "-.. .- ..- .-.. .. - -.--") == 0 && secret)
	{
		custom = CHOOSE;
		settextcolor(WHITE);
		outtextxy(50, 50, s);
		outtextxy(50, 80, "Daulity");//输出游玩提示
		outtextxy(50, 110, "Play again");
	}//daulity
	
}//摩斯转换比对信息，经过比对后能够跳转至选择间，进行选择后放出最终的图片以及名言解释
//void guanyu();//给出提示信息，关于
//void tuichu();//给出退出弹框，ok的话解释程序，否则清楚弹框
/*void Snake();*///负责接入贪吃蛇游戏,贪吃蛇游戏需要改变，用c改变果实，通过果实的平衡获取完全的摩斯码。


//定义渐变函数,gcount 为渐变的总次数；sleeptime 为延时时间
void gradient(int gcount, int sleeptime) {
	for (int i = 0; i < gcount; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(sleeptime);//延时20ms，形成渐变色的效果
	}
	
}

void texttime() {
	MOUSEMSG m;//鼠标指针
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;
		flushmessage();//清空鼠标消息缓存区
	}

}



//Showcustom展示关卡信息
//规定关卡框位置和字体信息
RECT guanyu = { 200, 80, 600, 600 };
int R[4] = { CUSTOM_X1,CUSTOM_Y1,CUSTOM_X2,CUSTOM_Y2 };//格式，矩阵x1,y1,x2,y2
TCHAR s[7][145] = { "美丽和丑陋是同一个硬币的两面，爱和恨是同一个心灵的两极，光明和黑暗是同一个世界的两端。——保罗·柯艾略",
				"生命是一种奇妙的平衡，既要有坚定的信念，也要有开放的心态，既要有勇气追求梦想，也要有智慧接受现实。——史蒂芬·柯维",
				"幸福和痛苦是生活的两种味道，既不能只品尝一种，也不能完全避免另一种。只有在经历了痛苦之后，才能更加珍惜和感激幸福。——海伦·凯勒",
				"人生最大的秘密不是探索宇宙和未知，而是发现自己内心深处的奥妙和力量。一个能发现自己内心深处奥妙和力量的人，永远不会感到恐惧和软弱 ——稻盛和夫",
				"世界上没有绝对的善与恶，只有不同的立场和观点。每个人都是自己的英雄，也是别人的恶魔。——乔治·R·R·马丁",
				"人生没有对错，只有选择和后果。每个人都是自己的导演，也是别人的观众。——奥斯卡·王尔德",
				"请辨认内心的声音，起点能找到答案"};
// 定义一个矩形区域
RECT textr = { 200, 350, 650, 550 };//定义输出文本的矩形框
//// 设置文字样式
//settextstyle(20, 0, _T("宋体"));
//
//// 设置文字背景为透明
//setbkmode(TRANSPARENT);
//
//// 设置文字颜色为白色
//settextcolor(WHITE);
void Showcustom() {
	LOGFONT f;
	RECT RH = { R[0],R[1],R[2],R[3] };
	cleardevice();
	gettextstyle(&f);     //获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体")); //设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿 
	f.lfHeight = 40;//设置字体高度
	f.lfWidth = 20;   // 设置字体宽度
	settextstyle(&f);                     // 设置字体样式
	switch (custom) {
	case CUSTOM0:
		drawtext("初识间", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[CUSTOM0], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM1:
		drawtext("理想间", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[CUSTOM1], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM2:
		drawtext("欲望间", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[CUSTOM2], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM3:
		drawtext("共存间", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[CUSTOM3], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CHOOSE://特殊触发
		drawtext("真理间", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(20, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[CHOOSE-1], &textr, DT_WORDBREAK);
		texttime();
		break;
	}
	//DARK和LIGHT分别显示
	

	settextstyle(0, 0, 0);//重置字体设置
	Sleep(2000);
}

//#define SCREEN_WIDTH 880//ori 800
//#define SCREEN_HEIGHT 715 //ori 650
int r[4][4] = { {BUTTON_X1,BUTTON_ONEY1,BUTTON_X2,BUTTON_ONEY2},
				{BUTTON_X1,BUTTON_TWOY1,BUTTON_X2,BUTTON_TWOY2},
				{BUTTON_X1,BUTTON_THREEY1,BUTTON_X2,BUTTON_THREEY2},
				{BUTTON_X1,BUTTON_FOURY1,BUTTON_X2,BUTTON_FOURY2} };//三个按钮的二维数组


int button_judge(int x, int y)//用于鼠标操作的判断
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	if (x > r[3][0] && x<r[3][2] && y>r[3][1] && y < r[3][3])return 4;
	return 0;
}
void menu()
{
	back:
	int i, event = 0;
	int flag = 0;
	HWND abc = GetHWnd();   //获取窗口句柄
	MOUSEMSG m;//鼠标指针
	//short win_width, win_height;//定义窗口的宽度和高度
	//win_width = 480; win_height = 360;
	//initgraph(win_width, win_height);//初始化窗口（黑屏）
	mciSendString("open music/maincon.mp3 alias song", NULL, 0, NULL);//载入音乐
	mciSendString("play song repeat", NULL, 0, NULL);//重复播放音乐
	gradient(256, 17);
	settextstyle(20, 0, ("宋体"));   // 设置字体
	setbkmode(TRANSPARENT);// 设置文字背景为透明
	settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	drawtext(s[MENU+1], &textr, DT_WORDBREAK);
	Sleep(1000);
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;
		Sleep(200);//0.2秒
		flushmessage();//清空鼠标消息缓存区
	}
	putimage(0, 0, &background[MENU]);
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	LOGFONT f;
	gettextstyle(&f);     //获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体")); //设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	drawtext("开始游戏", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("摩斯码转换", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext("关于", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("退出", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	//MOUSEMSG m;//鼠标指针

	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		if (flag)
			goto back;
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)//button_judge用于判断鼠标位置在哪个按钮上
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			switch (button_judge(m.x,m.y)) {
				case 1:
					goto Game;//直接跳出接下来进行游戏
				//case 2;//接入摩斯转换的程序
				case 2://摩斯码转化，直接获取文本信息进行比对
					Gettext();
					break;
				case 3://关于
					cleardevice();
					setbkcolor(WHITE);
					settextstyle(30, 0, ("宋体"));   // 设置字体
					if (secret)
						outtextxy(50,50, "摩斯密码:-.. .- ..- .-.. .. - -.--");
					drawtext("作者:小鸡崽\n垃圾作品\n音乐、美术素材来源:AI\n摩斯密码需要找出隐藏的状态,暂停键(P)可以看到\nem...下次再来看看吧", &guanyu, DT_WORDBREAK);//提示文本
					texttime();
					flag = 1;
					break;
				case 4://退出
					exit(0);
					break;
			}
			flushmessage();//清空鼠标消息缓存区
		}
	}
	Game:
	mciSendString("close song", NULL, 0, NULL);//关闭音乐;
	//system("pause");//暂停，为了显示
}


//放置各关卡的背景图片
void Setbackground(int con) {
	cleardevice();//清屏
	putimage(0, 0, &background[custom]);
}

void Setbgm() {
	switch (custom) {
	case CUSTOM0:
	case CUSTOM1:
	case CUSTOM2:
	case CUSTOM3:
		mciSendString("open music/playmusic.mp3 alias song", NULL, 0, NULL);//载入音乐
		mciSendString("play song repeat", NULL, 0, NULL);//重复播放音乐
		break;
	case CHOOSE:
		mciSendString("open music/defeatsnake.mp3 alias song", NULL, 0, NULL);//载入音乐
		mciSendString("play song repeat", NULL, 0, NULL);//重复播放音乐
		break;
	case DARK:
		mciSendString("open music/lastdark.mp3 alias song", NULL, 0, NULL);//载入音乐
		mciSendString("play song repeat", NULL, 0, NULL);//重复播放音乐
		break;
	case LIGHT:
		mciSendString("open music/lastlight.mp3 alias song", NULL, 0, NULL);//载入音乐
		mciSendString("play song repeat", NULL, 0, NULL);//重复播放音乐
		break;
	}
}

void loadimg() {
	//加载图片
	loadimage(&images[COMMONPLAYER], _T("pictures/original.png"), OBJECT_SIZE, OBJECT_SIZE,true);
	loadimage(&images[BLACKPLAYER], _T("pictures/black.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[WHITEPLAYER], _T("pictures/white.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[STARPLAYER], _T("pictures/original2.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[WHITEWALL], _T("pictures/whitewall.png"), BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&images[BLACKWALL], _T("pictures/blackwall.png"), BLOCK_SIZE, BLOCK_SIZE, true);
	loadimage(&images[WHITEBOX], _T("pictures/whitebox.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[BLACKBOX], _T("pictures/blackbox.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[BLACKTARGET], _T("pictures/blacktarget.png"), OBJECT_SIZE, OBJECT_SIZE, true);
	loadimage(&images[WHITETARGET], _T("pictures/whitetarget.png"), OBJECT_SIZE, OBJECT_SIZE, true);

	////透明化图片
	//enum _background {
	//	MENU,
	//	CUSTOM0,
	//	CUSTOM1,
	//	CUSTOM3,
	//	CUSTOM4,
	//	DARK,
	//	LIGHT,
	//	ALLBACK
	//};	
	//载入背景图片
	loadimage(&background[MENU], ("pictures/menu.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[CUSTOM0], ("pictures/background.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[CUSTOM1], ("pictures/background1.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[CUSTOM2], ("pictures/background2.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[CUSTOM3], ("pictures/background3.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[CHOOSE], ("pictures/choose.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[DARK], ("pictures/darkend.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&background[LIGHT], ("pictures/lightend.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	loadimage(&pauseimage, ("pictures/pause.png"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
}

void Initobject() {
	//custom 控制关卡,给对应关卡初始化非地图base的信息
	if (custom == 0) {
		//初始化物品信息
		man.manpos.x = man.manpos.y = 7;
		man.C_BW = COMMONPLAYER;
		condition = 0;//表示一种状态
		blackbox.x = blackbox.y = 2;
		whitebox.x = 4;
		whitebox.y = 5;
		//初始化黑白目的地信息
		blacktarget.x = 3;
		blacktarget.y = 3;
		whitetarget.x = 9;
		whitetarget.y = 3;
	}
	else if (custom == 1) {
		man.manpos.x = 7;
		man.manpos.y = 5;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = 7;
		blackbox.y = 1;
		whitebox.x = 3;
		whitebox.y = 5;
		//初始化黑白目的地信息
		blacktarget.x = 0;
		blacktarget.y = 0;
		whitetarget.x = 10;
		whitetarget.y = 7;
	}
	else if (custom == 2) {
		//初始化物品信息
		man.manpos.x = man.manpos.y = 7;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = blackbox.y = 2;
		whitebox.x = 4;
		whitebox.y = 5;
		//初始化黑白目的地信息
		blacktarget.x = 3;
		blacktarget.y = 3;
		whitetarget.x = 9;
		whitetarget.y = 3;
	}
	else if (custom == 3) {
		//初始化物品信息
		man.manpos.x = 11;
		man.manpos.y = 5;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = 10;
		blackbox.y = 5;
		whitebox.x = 0;
		whitebox.y = 3;
		//初始化黑白目的地信息
		blacktarget.x = 5;
		blacktarget.y = 8;
		whitetarget.x = 5;
		whitetarget.y = 6;
	}
	//"***************************"
	else if (custom == CHOOSE) {
		//初始化物品信息
		man.manpos.x = 6;
		man.manpos.y = 4;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = 9;
		blackbox.y = 5;
		whitebox.x = 2;
		whitebox.y = 5;
		//初始化黑白目的地信息
		blacktarget.x = 9;
		blacktarget.y = 8;
		whitetarget.x = 2;
		whitetarget.y = 1;
	}//choose 
	
}
void readmaps();
void Initmap(int custom) {
	if (custom == 4)
		return;
	gradient(256, 17);
	Initobject();
	readmaps();
	//if(custom==CUSTOM3)
	//	mciSendString("close song", NULL, 0, NULL);//关闭音乐
	//Sleep(300);
	Showcustom();//展示关卡信息
	Setbackground(custom);//设置背景
	Setbgm();//设置bgm
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[condition][i][j] == 2)
				continue;
			putimage(START_X + j * BLOCK_SIZE, START_Y+i*BLOCK_SIZE, &images[map[condition][i][j]]);//放置地图
		}
	}
	putimage(START_X + man.manpos.x * BLOCK_SIZE+ CEN_DELTABO, START_Y + man.manpos.y * BLOCK_SIZE+ CEN_DELTABO, &images[man.C_BW]);//放置人物
	if(!(blacktarget.x==blackbox.x&&blacktarget.y==blackbox.y)&& !(blacktarget.x == whitebox.x && blacktarget.y == whitebox.y))
		putimage(START_X + blacktarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blacktarget.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKTARGET]);
	if (!(whitetarget.x == whitebox.x && whitetarget.y == whitebox.y)&& !(whitetarget.x == blackbox.x && whitetarget.y == blackbox.y))
		putimage(START_X + whitetarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitetarget.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITETARGET]);
	//放置黑白盒和黑白目的地
	putimage(START_X + blackbox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blackbox.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKBOX]);
	putimage(START_X + whitebox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitebox.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITEBOX]);
}


//刷新，用于物
void freshinterface(Pos* pos, IMAGE image) {
	putimage(START_X + pos->x * BLOCK_SIZE + CEN_DELTABO, START_Y + pos->y * BLOCK_SIZE + CEN_DELTABO, &image);//放入后位置
}
//复现用于地图物
void reappear(Pos* pos) {
	if (pos->x == whitetarget.x && pos->y == whitetarget.y) {
		putimage(START_X + pos->x * BLOCK_SIZE+ CEN_DELTABO, START_Y + pos->y * BLOCK_SIZE+ CEN_DELTABO, &images[WHITETARGET]);
		return;
	}
	else if (pos->x == blacktarget.x && pos->y == blacktarget.y) {
		putimage(START_X + pos->x * BLOCK_SIZE+ CEN_DELTABO, START_Y + pos->y * BLOCK_SIZE+ CEN_DELTABO, &images[BLACKTARGET]);
		return;
	}
	else {
		putimage(START_X + pos->x * BLOCK_SIZE, START_Y + pos->y * BLOCK_SIZE, &images[map[condition][pos->y][pos->x]]);
	}	
}


#define common_canmove() (map[condition][nextpos.y][nextpos.x] == map[condition][man.manpos.y][man.manpos.x]&& !(nextpos.y == whitebox.y && nextpos.x == whitebox.x)&& !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))
#define black_canpush() (map[condition][nextpos.y][nextpos.x] == map[condition][man.manpos.y][man.manpos.x]&& nextpos.x == blackbox.x && nextpos.y == blackbox.y&& map[condition][nenepos.y][nenepos.x] == map[condition][man.manpos.y][man.manpos.x])
#define white_canpull() (map[condition][nextpos.y][nextpos.x] == map[condition][man.manpos.y][man.manpos.x]&& (abs(nextpos.x-whitebox.x)==2||abs(nextpos.y-whitebox.y)==2) && map[condition][man.manpos.y][man.manpos.x] == map[condition][whitebox.y][whitebox.x])

//boxcheck用于是否有箱子的判断
int boxcheck() {
	//允许出现共存态
	int check = 0;
	if ((abs(whitebox.x - man.manpos.x) + abs(whitebox.y - man.manpos.y)) <= 1 && map[condition][man.manpos.y][man.manpos.x] == map[condition][whitebox.y][whitebox.x])//在同一个区域并且相邻
		check += WHITEBOX;
	if ((abs(blackbox.x - man.manpos.x) + abs(blackbox.y - man.manpos.y)) <= 1 && map[condition][man.manpos.y][man.manpos.x] == map[condition][blackbox.y][blackbox.x])
		check += BLACKBOX;
	if (check == BLACKBOX + WHITEBOX)
		return STARPLAYER;
	if (check == 0)
		return COMMONPLAYER;
	return check;
}

char end[2][63] = { "You followed your own choice and bowed to your desires! Ugh", "You overcame your own desires and brought forth the light! Ugh" };
int length = strlen(end[0]);

void judgegame() {
	int num = custom;
	if (custom == CHOOSE)
	{
		if (whitetarget.x == whitebox.x && whitetarget.y == whitebox.y)
		{
			Sleep(2000);//给人缓冲的时间
			cleardevice();
			putimage(0, 0, &background[LIGHT]);//弹出提示框,直接放一个图片
			for(int i = 0;i<length;i++)
			{
				settextcolor(BLACK);
				settextstyle(30, 0, ("宋体"));   // 设置字体
				outtextxy(100+ i * 10, 80, end[1][i]);
				Sleep(200);//0.2秒
			}
			texttime();
			custom = LIGHT;
		}
		else if (blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)
		{
			Sleep(2000);//给人缓冲的时间
			cleardevice();
			putimage(0, 0, &background[DARK]);//弹出提示框,直接放一个图片
			for (int i = 0; i < length; i++)
			{
				settextcolor(WHITE);
				settextstyle(30, 0, ("宋体"));   // 设置字体
				outtextxy(100 + i * 10, 80, end[0][i]);
				Sleep(200);//0.2秒
			}
			texttime();
			custom = DARK;
		}
		return;
	}
	if (whitetarget.x == whitebox.x && whitetarget.y == whitebox.y) {
		if (blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)
			custom++;//说明通关
	}
	//给出通关说明
	if (custom == 4 && man.C_BW == STARPLAYER)
		secret = 1;
	//进入下一关
	if (num != custom) {
		Sleep(1000);
		cleardevice();
		Initmap(custom);
	}
		
}
void convert_map();
//起始定义0为墙，change后重载地图，0仍未墙但是图片放置相反
void game(int dir) {
	char sn;
	nextpos.x = man.manpos.x;
	nextpos.y = man.manpos.y;
	nenepos.x = man.manpos.x;
	nenepos.y = man.manpos.y;
	switch (dir) {
	case UP:
		nextpos.y -= 1;
		nenepos.y -= 2;
		if (nextpos.y >= ROW || nextpos.y < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common状态无法进行交互,只进行移动判断
			{
				reappear(&man.manpos);
				man.manpos.y = nextpos.y;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//当变化状态时说明旁边有方块
		if(man.C_BW == BLACKPLAYER){
			//人可以移动，人在推箱子，箱子也可以移动,那么正在推箱子
			if (black_canpush()&& nenepos.y<ROW&&nenepos.y>=0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if(!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//由于链接不推箱子就不动
				break;
		}
		else if(man.C_BW==WHITEPLAYER) {
			//人可以移动，人在拉箱子，箱子也可以移动，那么正在拉箱子
			if (white_canpull()) {
				reappear(&man.manpos);
				reappear(&whitebox);
				whitebox.y = man.manpos.y;
				man.manpos.y = nextpos.y;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
			}
			else if (abs(nextpos.x-whitebox.x)==1&&abs(nextpos.y-whitebox.y)==1)
				break;
		}
		else if(man.C_BW==STARPLAYER){
			//同时满足人可以移动，白箱子可以移动，黑箱子可以移动，那么拉白箱子，推黑箱子
			if (white_canpull() && black_canpush() && nenepos.y < ROW && nenepos.y >= 0)
			{
				reappear(&whitebox);
				reappear(&man.manpos);
				reappear(&blackbox);
				whitebox.y = man.manpos.y;
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1|| !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//两者取货
				break;
		}
		break;
	case DOWN:
		nextpos.y += 1;
		nenepos.y += 2;
		if (nextpos.y >= ROW || nextpos.y < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common状态无法进行交互,只进行移动判断
			{
				reappear(&man.manpos);
				man.manpos.y = nextpos.y;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//if(man.C_BW == BLACKPLAYER){}
		//else{}
		//当变化状态时说明旁边有方块
		if (man.C_BW == BLACKPLAYER) {
			//人可以移动，人在推箱子，箱子也可以移动,那么正在推箱子
			if (black_canpush()&&nenepos.y < ROW && nenepos.y >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//由于链接不推箱子就不动
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//人可以移动，人在拉箱子，箱子也可以移动，那么正在拉箱子
			if (white_canpull()) {
				reappear(&man.manpos);
				reappear(&whitebox);
				whitebox.y = man.manpos.y;
				man.manpos.y = nextpos.y;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1)
				break;
		}
		else if (man.C_BW == STARPLAYER) {
			//同时满足人可以移动，白箱子可以移动，黑箱子可以移动，那么拉白箱子，推黑箱子
			if (white_canpull() && black_canpush() && nenepos.y < ROW && nenepos.y >= 0)
			{
				reappear(&whitebox);
				reappear(&man.manpos);
				reappear(&blackbox);
				whitebox.y = man.manpos.y;
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//两者取货
				break;
		}
		break;
	case LEFT:
		nextpos.x -= 1;
		nenepos.x -= 2;
		if (nextpos.x >= COL || nextpos.x < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common状态无法进行交互,只进行移动判断
			{
				reappear(&man.manpos);
				man.manpos.x = nextpos.x;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//当变化状态时说明旁边有方块
		if (man.C_BW == BLACKPLAYER) {
			//人可以移动，人在推箱子，箱子也可以移动,那么正在推箱子
			if (black_canpush()&&nenepos.x < COL && nenepos.x >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//由于链接不推箱子就不动
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//人可以移动，人在拉箱子，箱子也可以移动，那么正在拉箱子
			if (white_canpull()) {
				reappear(&man.manpos);
				reappear(&whitebox);
				whitebox.x = man.manpos.x;
				man.manpos.x = nextpos.x;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1)
				break;
		}
		else if (man.C_BW == STARPLAYER) {
			//同时满足人可以移动，白箱子可以移动，黑箱子可以移动，那么拉白箱子，推黑箱子
			if (white_canpull() && black_canpush() && nenepos.y < ROW && nenepos.y >= 0)
			{
				reappear(&whitebox);
				reappear(&man.manpos);
				reappear(&blackbox);
				whitebox.x = man.manpos.x;
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//两者取货
				break;
		}
		break;
	case RIGHT:
		nextpos.x += 1;
		nenepos.x += 2;
		if (nextpos.x >= COL || nextpos.x < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common状态无法进行交互,只进行移动判断
			{
				reappear(&man.manpos);
				man.manpos.x = nextpos.x;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//当变化状态时说明旁边有方块
		if (man.C_BW == BLACKPLAYER) {
			//人可以移动，人在推箱子，箱子也可以移动,那么正在推箱子
			if (black_canpush() && nenepos.x < COL && nenepos.x >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//由于链接不推箱子就不动
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//人可以移动，人在拉箱子，箱子也可以移动，那么正在拉箱子
			if (white_canpull()) {
				reappear(&man.manpos);
				reappear(&whitebox);
				whitebox.x = man.manpos.x;
				man.manpos.x = nextpos.x;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1)
				break;
		}
		else if (man.C_BW == STARPLAYER) {
			//同时满足人可以移动，白箱子可以移动，黑箱子可以移动，那么拉白箱子，推黑箱子
			if (white_canpull() && black_canpush() && nenepos.y < ROW && nenepos.y >= 0)
			{
				reappear(&whitebox);
				reappear(&man.manpos);
				reappear(&blackbox);
				whitebox.x = man.manpos.x;
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&whitebox, images[WHITEBOX]);
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//两者取货
				break;
		}
		break;
	case PAUSE:
		putimage(0, 0, &pauseimage);//弹出提示框,直接放一个图片
		sn = _getch();
		cleardevice();//清屏幕，重新绘图
		Setbackground(custom);//设置背景
		convert_map();
		break;
	}
	judgegame();
}

//改变player形态
void bwexchange() {
	if (man.C_BW == BLACKPLAYER || man.C_BW == WHITEPLAYER|| man.C_BW==STARPLAYER)
	{
		man.C_BW = COMMONPLAYER;
	}
	else if (man.C_BW == COMMONPLAYER) {
		int checks;
		checks = boxcheck();
		if (checks == STARPLAYER && (abs(blackbox.y-whitebox.y)==2 || abs(blackbox.x - whitebox.x) == 2))//检测到两个箱子在的同时需要两个箱子在同一轴线上
			man.C_BW = STARPLAYER;
		if (checks == BLACKBOX)
			man.C_BW = BLACKPLAYER;
		else if (checks == WHITEBOX)
			man.C_BW = WHITEPLAYER;
	}		
	putimage(START_X + man.manpos.x * BLOCK_SIZE + CEN_DELTABO, START_Y + man.manpos.y * BLOCK_SIZE + CEN_DELTABO, &images[man.C_BW]);
}

void conexchange() {
	if (condition == 0)
	{
		condition = 1;
		return;
	}
	condition = 0;

}

//读取地图信息
void readmaps() {
	FILE* fp = NULL; // 定义一个文件指针
	// map用来存放文件的内容
	int num = 0; // 定义一个变量，用来存放每个数字
	int layer = 0; // 定义一个变量，用来记录当前的层数
	char line[80];
	char ch;
	int i = 0;


	fp = fopen("关卡地图.txt", "r"); // 以只读模式打开文件
	if (fp == NULL) // 如果打开失败，输出错误信息并退出
	{
		perror("Error opening file");
		exit(1);
	}
	//定位到需要的关卡的行
	for (int count = 0; count < custom * 20; count++)
	{
		fgets(line, sizeof(line), fp);
	}

	for (i = 0; i <= ROW * LAY; i++) // 循环读取文件的每一行
	{
		fscanf(fp, "%c", &ch);
		if (ch == '0' || ch == '1' || ch=='2') // 如果成功读取一个整数
		{
			num = ch - '0';
			map[layer][i % ROW][0] = num; // 将整数存放到三维数组中对应的位置
			for (int j = 1; j < COL; j++) // 循环读取每一行的剩余列
			{
				if (fscanf(fp, ",%d", &num) == 1) // 如果成功读取一个整数（跳过逗号）
				{
					map[layer][i % ROW][j] = num; // 将整数存放到三维数组中对应的位置
				}
				else // 如果读取失败或者文件结束
				{
					break; // 跳出循环
				}
			}
			fscanf(fp, "%c", &ch);
		}
		else// 如果读取失败或者文件结束或者遇到空行
		{
			layer++; // 层数加一
			i -= 1;
			if (layer >= LAY) // 如果超过最大层数
			{
				break; // 跳出循环
			}
		}
	}
	fclose(fp); // 关闭文件
}


void convert_map() {

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[condition][i][j] == 2)
				continue;
			putimage(START_X + j * BLOCK_SIZE, START_Y + i * BLOCK_SIZE, &images[map[condition][i][j]]);
		}
	}
	
	putimage(START_X + man.manpos.x * BLOCK_SIZE + CEN_DELTABO, START_Y + man.manpos.y * BLOCK_SIZE + CEN_DELTABO, &images[man.C_BW]);//放置人物
	//放置黑白盒和黑白目的地
	putimage(START_X + blackbox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blackbox.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKBOX]);
	putimage(START_X + whitebox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitebox.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITEBOX]);

	if (!(blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)&& !(blacktarget.x == man.manpos.x && blacktarget.y == man.manpos.y)&&!(blacktarget.x==whitebox.x&&blacktarget.y==whitebox.y))
		putimage(START_X + blacktarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blacktarget.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKTARGET]);
	if (!(whitetarget.x == whitebox.x && whitetarget.y == whitebox.y)&& !(whitetarget.x == man.manpos.x && whitetarget.y == man.manpos.y)&&!(whitetarget.x == blackbox.x && whitetarget.y == blackbox.y))
		putimage(START_X + whitetarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitetarget.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITETARGET]);
	if(man.C_BW!=COMMONPLAYER)
		bwexchange();//自动由强力状态转换为普通状态
}

void Gameover() {
	if (secret)//如果解锁隐藏，那么开启
	{
		mciSendString("close song", NULL, 0, NULL);//关闭音乐
		gradient(256, 17);//渐变,给出词条
		settextstyle(30, 0, ("宋体"));   // 设置字体
		setbkmode(TRANSPARENT);// 设置文字背景为透明
		settextcolor(BLACK);    //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(s[6], &textr, DT_WORDBREAK);//提示文本
		mciSendString("open music/MOSECODE.mp3 alias song", NULL, 0, NULL);//载入音乐
		mciSendString("play song", NULL, 0, NULL);//重复播放音乐
		Sleep(11000);//11秒
	}//播放摩斯密码
	mciSendString("close song", NULL, 0, NULL);//关闭音乐;
	//输出文本信息提示玩家将听到的摩斯密码输入主菜单框中
}




int main() {
	IMAGE bg_img;
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	//设置主菜单
flag:
	custom = 0;
	//mciSendString("close song", NULL, 0, NULL);//关闭音乐
	loadimg();
	menu();//进入菜单
	//进入游戏程序

	//设置背景,关卡
	//Setbackground(custom);
	//指定左上角坐标，长宽
	Initobject();
	Initmap(custom);//传入的custom用于读取并绘制绘制某一关的地图
	//peekmessage(&m_key, EM_KEY);//获取键盘消息
	//按键检测

	do {
		if (_kbhit) {
			char ch = _getch();
			switch(ch) {
			case KEY_DOWN:
				game(DOWN);
				break;
			case KEY_UP:
				game(UP);
				break;
			case KEY_LEFT:
				game(LEFT);
				break;
			case KEY_RIGHT:
				game(RIGHT);
				break;
			case KEY_C:
				conexchange();//改变map,但是不变关卡,condition
				convert_map();//变关卡的话改变custom
				break;
			case KEY_E:
				bwexchange();//E对man.C_BW进行改变
				break;
			case KEY_P:
				game(PAUSE);
				break;
			case KEY_R:
				Initmap(custom);
				break;
			default:
				break;
			}
		}
		Sleep(100);//100毫秒
	} while (custom!=4&&!(custom == DARK || custom == LIGHT));
	/*system("pause");*/
	//通关
	
	//secret在本次窗口中一直置为1，便于摩斯码转换中的播放按钮的出现
	cleardevice();
	/*if(!secret)*/
	if(!(custom==DARK||custom==LIGHT))
		Gameover();//游戏结束,给出说明
	mciSendString("close song", NULL, 0, NULL);//关闭音乐
	goto flag;
	return 0;
}