#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <mmsystem.h>//������ý���豸�ӿ��ļ�
//#include "MoseCode.h"
//#include "Snake.h"

#pragma comment (lib, "WINMM.LIB")//���ؾ�̬��


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
#define BUTTON_HEIGHT 40//ͳһ���100���߶�40
#define CUSTOM_WIDTH 150
#define CUSTOM_HEIGHT 150
#define BUTTON_X1 375
#define BUTTON_X2 BUTTON_X1+BUTTON_WIDTH //x2-x2==��ť���
#define BUTTON_ONEY1 240
#define BUTTON_ONEY2 BUTTON_ONEY1+BUTTON_HEIGHT//Y2-Y1==������ť�ĸ߶�
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


//��ȡ�ؿ�
#define ROW 9 // ��������
#define COL 12 // ��������
#define LAY 2 // �������


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
	int C_BW;//����״̬common/black/white
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
//��ͼ���Ȳ��ŷ�����������壬�����ٷ���,��ô��Ҫobject�ĸ���λ�ö���






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

int custom;//�ؿ�������ʼ��Ϊ0
int condition = 0;//�ڰױ���
int secret = 0;//ͨ�����һ���Ƿ����Ħ˹����



//����ɺ���*****************************************************
void Gettext() {
	// �����ַ������������������û�����
	//settextstyle(16,0,("����") );//��������
	char s[35];
	InputBox(s, 35, "������Ħ˹����(�����ʽ����:.- ..):","������",NULL, 600, 400);
	Sleep(300);//�����˳���ͻ
	if (strcmp(s, "-.. .- ..- .-.. .. - -.--") == 0 && secret)
	{
		custom = CHOOSE;
		settextcolor(WHITE);
		outtextxy(50, 50, s);
		outtextxy(50, 80, "Daulity");//���������ʾ
		outtextxy(50, 110, "Play again");
	}//daulity
	
}//Ħ˹ת���ȶ���Ϣ�������ȶԺ��ܹ���ת��ѡ��䣬����ѡ���ų����յ�ͼƬ�Լ����Խ���
//void guanyu();//������ʾ��Ϣ������
//void tuichu();//�����˳�����ok�Ļ����ͳ��򣬷����������
/*void Snake();*///�������̰������Ϸ,̰������Ϸ��Ҫ�ı䣬��c�ı��ʵ��ͨ����ʵ��ƽ���ȡ��ȫ��Ħ˹�롣


//���彥�亯��,gcount Ϊ������ܴ�����sleeptime Ϊ��ʱʱ��
void gradient(int gcount, int sleeptime) {
	for (int i = 0; i < gcount; i += 5)
	{
		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
		cleardevice();//������ȡ���ڱ���ɫ��
		Sleep(sleeptime);//��ʱ20ms���γɽ���ɫ��Ч��
	}
	
}

void texttime() {
	MOUSEMSG m;//���ָ��
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;
		flushmessage();//��������Ϣ������
	}

}



//Showcustomչʾ�ؿ���Ϣ
//�涨�ؿ���λ�ú�������Ϣ
RECT guanyu = { 200, 80, 600, 600 };
int R[4] = { CUSTOM_X1,CUSTOM_Y1,CUSTOM_X2,CUSTOM_Y2 };//��ʽ������x1,y1,x2,y2
TCHAR s[7][145] = { "�����ͳ�ª��ͬһ��Ӳ�ҵ����棬���ͺ���ͬһ������������������ͺڰ���ͬһ����������ˡ��������ޡ��°���",
				"������һ�������ƽ�⣬��Ҫ�мᶨ�����ҲҪ�п��ŵ���̬����Ҫ������׷�����룬ҲҪ���ǻ۽�����ʵ������ʷ�ٷҡ���ά",
				"�Ҹ���ʹ�������������ζ�����Ȳ���ֻƷ��һ�֣�Ҳ������ȫ������һ�֡�ֻ���ھ�����ʹ��֮�󣬲��ܸ�����ϧ�͸м��Ҹ����������ס�����",
				"�����������ܲ���̽�������δ֪�����Ƿ����Լ�������İ����������һ���ܷ����Լ������������������ˣ���Զ����е��־������ ������ʢ�ͷ�",
				"������û�о��Ե������ֻ�в�ͬ�������͹۵㡣ÿ���˶����Լ���Ӣ�ۣ�Ҳ�Ǳ��˵Ķ�ħ���������Ρ�R��R����",
				"����û�жԴ�ֻ��ѡ��ͺ����ÿ���˶����Լ��ĵ��ݣ�Ҳ�Ǳ��˵Ĺ��ڡ�������˹����������",
				"��������ĵ�������������ҵ���"};
// ����һ����������
RECT textr = { 200, 350, 650, 550 };//��������ı��ľ��ο�
//// ����������ʽ
//settextstyle(20, 0, _T("����"));
//
//// �������ֱ���Ϊ͸��
//setbkmode(TRANSPARENT);
//
//// ����������ɫΪ��ɫ
//settextcolor(WHITE);
void Showcustom() {
	LOGFONT f;
	RECT RH = { R[0],R[1],R[2],R[3] };
	cleardevice();
	gettextstyle(&f);     //��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����")); //��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ����� 
	f.lfHeight = 40;//��������߶�
	f.lfWidth = 20;   // ����������
	settextstyle(&f);                     // ����������ʽ
	switch (custom) {
	case CUSTOM0:
		drawtext("��ʶ��", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[CUSTOM0], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM1:
		drawtext("�����", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[CUSTOM1], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM2:
		drawtext("������", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[CUSTOM2], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CUSTOM3:
		drawtext("�����", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(30, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[CUSTOM3], &textr, DT_WORDBREAK);
		texttime();
		break;
	case CHOOSE://���ⴥ��
		drawtext("�����", &RH, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(20, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[CHOOSE-1], &textr, DT_WORDBREAK);
		texttime();
		break;
	}
	//DARK��LIGHT�ֱ���ʾ
	

	settextstyle(0, 0, 0);//������������
	Sleep(2000);
}

//#define SCREEN_WIDTH 880//ori 800
//#define SCREEN_HEIGHT 715 //ori 650
int r[4][4] = { {BUTTON_X1,BUTTON_ONEY1,BUTTON_X2,BUTTON_ONEY2},
				{BUTTON_X1,BUTTON_TWOY1,BUTTON_X2,BUTTON_TWOY2},
				{BUTTON_X1,BUTTON_THREEY1,BUTTON_X2,BUTTON_THREEY2},
				{BUTTON_X1,BUTTON_FOURY1,BUTTON_X2,BUTTON_FOURY2} };//������ť�Ķ�ά����


int button_judge(int x, int y)//�������������ж�
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
	HWND abc = GetHWnd();   //��ȡ���ھ��
	MOUSEMSG m;//���ָ��
	//short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
	//win_width = 480; win_height = 360;
	//initgraph(win_width, win_height);//��ʼ�����ڣ�������
	mciSendString("open music/maincon.mp3 alias song", NULL, 0, NULL);//��������
	mciSendString("play song repeat", NULL, 0, NULL);//�ظ���������
	gradient(256, 17);
	settextstyle(20, 0, ("����"));   // ��������
	setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
	settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
	drawtext(s[MENU+1], &textr, DT_WORDBREAK);
	Sleep(1000);
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			break;
		Sleep(200);//0.2��
		flushmessage();//��������Ϣ������
	}
	putimage(0, 0, &background[MENU]);
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	LOGFONT f;
	gettextstyle(&f);     //��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����")); //��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
	drawtext("��ʼ��Ϸ", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("Ħ˹��ת��", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("����", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�˳�", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	//MOUSEMSG m;//���ָ��

	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ
		if (flag)
			goto back;
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge(m.x, m.y) != 0)//button_judge�����ж����λ�����ĸ���ť��
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			switch (button_judge(m.x,m.y)) {
				case 1:
					goto Game;//ֱ������������������Ϸ
				//case 2;//����Ħ˹ת���ĳ���
				case 2://Ħ˹��ת����ֱ�ӻ�ȡ�ı���Ϣ���бȶ�
					Gettext();
					break;
				case 3://����
					cleardevice();
					setbkcolor(WHITE);
					settextstyle(30, 0, ("����"));   // ��������
					if (secret)
						outtextxy(50,50, "Ħ˹����:-.. .- ..- .-.. .. - -.--");
					drawtext("����:С����\n������Ʒ\n���֡������ز���Դ:AI\nĦ˹������Ҫ�ҳ����ص�״̬,��ͣ��(P)���Կ���\nem...�´�����������", &guanyu, DT_WORDBREAK);//��ʾ�ı�
					texttime();
					flag = 1;
					break;
				case 4://�˳�
					exit(0);
					break;
			}
			flushmessage();//��������Ϣ������
		}
	}
	Game:
	mciSendString("close song", NULL, 0, NULL);//�ر�����;
	//system("pause");//��ͣ��Ϊ����ʾ
}


//���ø��ؿ��ı���ͼƬ
void Setbackground(int con) {
	cleardevice();//����
	putimage(0, 0, &background[custom]);
}

void Setbgm() {
	switch (custom) {
	case CUSTOM0:
	case CUSTOM1:
	case CUSTOM2:
	case CUSTOM3:
		mciSendString("open music/playmusic.mp3 alias song", NULL, 0, NULL);//��������
		mciSendString("play song repeat", NULL, 0, NULL);//�ظ���������
		break;
	case CHOOSE:
		mciSendString("open music/defeatsnake.mp3 alias song", NULL, 0, NULL);//��������
		mciSendString("play song repeat", NULL, 0, NULL);//�ظ���������
		break;
	case DARK:
		mciSendString("open music/lastdark.mp3 alias song", NULL, 0, NULL);//��������
		mciSendString("play song repeat", NULL, 0, NULL);//�ظ���������
		break;
	case LIGHT:
		mciSendString("open music/lastlight.mp3 alias song", NULL, 0, NULL);//��������
		mciSendString("play song repeat", NULL, 0, NULL);//�ظ���������
		break;
	}
}

void loadimg() {
	//����ͼƬ
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

	////͸����ͼƬ
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
	//���뱳��ͼƬ
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
	//custom ���ƹؿ�,����Ӧ�ؿ���ʼ���ǵ�ͼbase����Ϣ
	if (custom == 0) {
		//��ʼ����Ʒ��Ϣ
		man.manpos.x = man.manpos.y = 7;
		man.C_BW = COMMONPLAYER;
		condition = 0;//��ʾһ��״̬
		blackbox.x = blackbox.y = 2;
		whitebox.x = 4;
		whitebox.y = 5;
		//��ʼ���ڰ�Ŀ�ĵ���Ϣ
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
		//��ʼ���ڰ�Ŀ�ĵ���Ϣ
		blacktarget.x = 0;
		blacktarget.y = 0;
		whitetarget.x = 10;
		whitetarget.y = 7;
	}
	else if (custom == 2) {
		//��ʼ����Ʒ��Ϣ
		man.manpos.x = man.manpos.y = 7;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = blackbox.y = 2;
		whitebox.x = 4;
		whitebox.y = 5;
		//��ʼ���ڰ�Ŀ�ĵ���Ϣ
		blacktarget.x = 3;
		blacktarget.y = 3;
		whitetarget.x = 9;
		whitetarget.y = 3;
	}
	else if (custom == 3) {
		//��ʼ����Ʒ��Ϣ
		man.manpos.x = 11;
		man.manpos.y = 5;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = 10;
		blackbox.y = 5;
		whitebox.x = 0;
		whitebox.y = 3;
		//��ʼ���ڰ�Ŀ�ĵ���Ϣ
		blacktarget.x = 5;
		blacktarget.y = 8;
		whitetarget.x = 5;
		whitetarget.y = 6;
	}
	//"***************************"
	else if (custom == CHOOSE) {
		//��ʼ����Ʒ��Ϣ
		man.manpos.x = 6;
		man.manpos.y = 4;
		man.C_BW = COMMONPLAYER;
		condition = 0;
		blackbox.x = 9;
		blackbox.y = 5;
		whitebox.x = 2;
		whitebox.y = 5;
		//��ʼ���ڰ�Ŀ�ĵ���Ϣ
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
	//	mciSendString("close song", NULL, 0, NULL);//�ر�����
	//Sleep(300);
	Showcustom();//չʾ�ؿ���Ϣ
	Setbackground(custom);//���ñ���
	Setbgm();//����bgm
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[condition][i][j] == 2)
				continue;
			putimage(START_X + j * BLOCK_SIZE, START_Y+i*BLOCK_SIZE, &images[map[condition][i][j]]);//���õ�ͼ
		}
	}
	putimage(START_X + man.manpos.x * BLOCK_SIZE+ CEN_DELTABO, START_Y + man.manpos.y * BLOCK_SIZE+ CEN_DELTABO, &images[man.C_BW]);//��������
	if(!(blacktarget.x==blackbox.x&&blacktarget.y==blackbox.y)&& !(blacktarget.x == whitebox.x && blacktarget.y == whitebox.y))
		putimage(START_X + blacktarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blacktarget.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKTARGET]);
	if (!(whitetarget.x == whitebox.x && whitetarget.y == whitebox.y)&& !(whitetarget.x == blackbox.x && whitetarget.y == blackbox.y))
		putimage(START_X + whitetarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitetarget.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITETARGET]);
	//���úڰ׺кͺڰ�Ŀ�ĵ�
	putimage(START_X + blackbox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blackbox.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKBOX]);
	putimage(START_X + whitebox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitebox.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITEBOX]);
}


//ˢ�£�������
void freshinterface(Pos* pos, IMAGE image) {
	putimage(START_X + pos->x * BLOCK_SIZE + CEN_DELTABO, START_Y + pos->y * BLOCK_SIZE + CEN_DELTABO, &image);//�����λ��
}
//�������ڵ�ͼ��
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

//boxcheck�����Ƿ������ӵ��ж�
int boxcheck() {
	//������ֹ���̬
	int check = 0;
	if ((abs(whitebox.x - man.manpos.x) + abs(whitebox.y - man.manpos.y)) <= 1 && map[condition][man.manpos.y][man.manpos.x] == map[condition][whitebox.y][whitebox.x])//��ͬһ������������
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
			Sleep(2000);//���˻����ʱ��
			cleardevice();
			putimage(0, 0, &background[LIGHT]);//������ʾ��,ֱ�ӷ�һ��ͼƬ
			for(int i = 0;i<length;i++)
			{
				settextcolor(BLACK);
				settextstyle(30, 0, ("����"));   // ��������
				outtextxy(100+ i * 10, 80, end[1][i]);
				Sleep(200);//0.2��
			}
			texttime();
			custom = LIGHT;
		}
		else if (blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)
		{
			Sleep(2000);//���˻����ʱ��
			cleardevice();
			putimage(0, 0, &background[DARK]);//������ʾ��,ֱ�ӷ�һ��ͼƬ
			for (int i = 0; i < length; i++)
			{
				settextcolor(WHITE);
				settextstyle(30, 0, ("����"));   // ��������
				outtextxy(100 + i * 10, 80, end[0][i]);
				Sleep(200);//0.2��
			}
			texttime();
			custom = DARK;
		}
		return;
	}
	if (whitetarget.x == whitebox.x && whitetarget.y == whitebox.y) {
		if (blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)
			custom++;//˵��ͨ��
	}
	//����ͨ��˵��
	if (custom == 4 && man.C_BW == STARPLAYER)
		secret = 1;
	//������һ��
	if (num != custom) {
		Sleep(1000);
		cleardevice();
		Initmap(custom);
	}
		
}
void convert_map();
//��ʼ����0Ϊǽ��change�����ص�ͼ��0��δǽ����ͼƬ�����෴
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
			if (common_canmove())//common״̬�޷����н���,ֻ�����ƶ��ж�
			{
				reappear(&man.manpos);
				man.manpos.y = nextpos.y;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//���仯״̬ʱ˵���Ա��з���
		if(man.C_BW == BLACKPLAYER){
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�,��ô����������
			if (black_canpush()&& nenepos.y<ROW&&nenepos.y>=0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if(!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//�������Ӳ������ӾͲ���
				break;
		}
		else if(man.C_BW==WHITEPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�����ô����������
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
			//ͬʱ�����˿����ƶ��������ӿ����ƶ��������ӿ����ƶ�����ô�������ӣ��ƺ�����
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
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1|| !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//����ȡ��
				break;
		}
		break;
	case DOWN:
		nextpos.y += 1;
		nenepos.y += 2;
		if (nextpos.y >= ROW || nextpos.y < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common״̬�޷����н���,ֻ�����ƶ��ж�
			{
				reappear(&man.manpos);
				man.manpos.y = nextpos.y;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//if(man.C_BW == BLACKPLAYER){}
		//else{}
		//���仯״̬ʱ˵���Ա��з���
		if (man.C_BW == BLACKPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�,��ô����������
			if (black_canpush()&&nenepos.y < ROW && nenepos.y >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.y = nextpos.y;
				blackbox.y = nenepos.y;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//�������Ӳ������ӾͲ���
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�����ô����������
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
			//ͬʱ�����˿����ƶ��������ӿ����ƶ��������ӿ����ƶ�����ô�������ӣ��ƺ�����
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
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//����ȡ��
				break;
		}
		break;
	case LEFT:
		nextpos.x -= 1;
		nenepos.x -= 2;
		if (nextpos.x >= COL || nextpos.x < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common״̬�޷����н���,ֻ�����ƶ��ж�
			{
				reappear(&man.manpos);
				man.manpos.x = nextpos.x;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//���仯״̬ʱ˵���Ա��з���
		if (man.C_BW == BLACKPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�,��ô����������
			if (black_canpush()&&nenepos.x < COL && nenepos.x >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//�������Ӳ������ӾͲ���
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�����ô����������
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
			//ͬʱ�����˿����ƶ��������ӿ����ƶ��������ӿ����ƶ�����ô�������ӣ��ƺ�����
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
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//����ȡ��
				break;
		}
		break;
	case RIGHT:
		nextpos.x += 1;
		nenepos.x += 2;
		if (nextpos.x >= COL || nextpos.x < 0)break;
		if (man.C_BW == COMMONPLAYER) {
			if (common_canmove())//common״̬�޷����н���,ֻ�����ƶ��ж�
			{
				reappear(&man.manpos);
				man.manpos.x = nextpos.x;
				freshinterface(&man.manpos, images[man.C_BW]);//man move//
			}
		}
		//���仯״̬ʱ˵���Ա��з���
		if (man.C_BW == BLACKPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�,��ô����������
			if (black_canpush() && nenepos.x < COL && nenepos.x >= 0) {
				reappear(&man.manpos);
				reappear(&nextpos);
				man.manpos.x = nextpos.x;
				blackbox.x = nenepos.x;
				freshinterface(&man.manpos, images[man.C_BW]);
				freshinterface(&blackbox, images[BLACKBOX]);
			}
			else if (!(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//�������Ӳ������ӾͲ���
				break;
		}
		else if (man.C_BW == WHITEPLAYER) {
			//�˿����ƶ������������ӣ�����Ҳ�����ƶ�����ô����������
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
			//ͬʱ�����˿����ƶ��������ӿ����ƶ��������ӿ����ƶ�����ô�������ӣ��ƺ�����
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
			else if (abs(nextpos.x - whitebox.x) == 1 && abs(nextpos.y - whitebox.y) == 1 || !(nextpos.y == blackbox.y && nextpos.x == blackbox.x))//����ȡ��
				break;
		}
		break;
	case PAUSE:
		putimage(0, 0, &pauseimage);//������ʾ��,ֱ�ӷ�һ��ͼƬ
		sn = _getch();
		cleardevice();//����Ļ�����»�ͼ
		Setbackground(custom);//���ñ���
		convert_map();
		break;
	}
	judgegame();
}

//�ı�player��̬
void bwexchange() {
	if (man.C_BW == BLACKPLAYER || man.C_BW == WHITEPLAYER|| man.C_BW==STARPLAYER)
	{
		man.C_BW = COMMONPLAYER;
	}
	else if (man.C_BW == COMMONPLAYER) {
		int checks;
		checks = boxcheck();
		if (checks == STARPLAYER && (abs(blackbox.y-whitebox.y)==2 || abs(blackbox.x - whitebox.x) == 2))//��⵽���������ڵ�ͬʱ��Ҫ����������ͬһ������
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

//��ȡ��ͼ��Ϣ
void readmaps() {
	FILE* fp = NULL; // ����һ���ļ�ָ��
	// map��������ļ�������
	int num = 0; // ����һ���������������ÿ������
	int layer = 0; // ����һ��������������¼��ǰ�Ĳ���
	char line[80];
	char ch;
	int i = 0;


	fp = fopen("�ؿ���ͼ.txt", "r"); // ��ֻ��ģʽ���ļ�
	if (fp == NULL) // �����ʧ�ܣ����������Ϣ���˳�
	{
		perror("Error opening file");
		exit(1);
	}
	//��λ����Ҫ�Ĺؿ�����
	for (int count = 0; count < custom * 20; count++)
	{
		fgets(line, sizeof(line), fp);
	}

	for (i = 0; i <= ROW * LAY; i++) // ѭ����ȡ�ļ���ÿһ��
	{
		fscanf(fp, "%c", &ch);
		if (ch == '0' || ch == '1' || ch=='2') // ����ɹ���ȡһ������
		{
			num = ch - '0';
			map[layer][i % ROW][0] = num; // ��������ŵ���ά�����ж�Ӧ��λ��
			for (int j = 1; j < COL; j++) // ѭ����ȡÿһ�е�ʣ����
			{
				if (fscanf(fp, ",%d", &num) == 1) // ����ɹ���ȡһ���������������ţ�
				{
					map[layer][i % ROW][j] = num; // ��������ŵ���ά�����ж�Ӧ��λ��
				}
				else // �����ȡʧ�ܻ����ļ�����
				{
					break; // ����ѭ��
				}
			}
			fscanf(fp, "%c", &ch);
		}
		else// �����ȡʧ�ܻ����ļ�����������������
		{
			layer++; // ������һ
			i -= 1;
			if (layer >= LAY) // �������������
			{
				break; // ����ѭ��
			}
		}
	}
	fclose(fp); // �ر��ļ�
}


void convert_map() {

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[condition][i][j] == 2)
				continue;
			putimage(START_X + j * BLOCK_SIZE, START_Y + i * BLOCK_SIZE, &images[map[condition][i][j]]);
		}
	}
	
	putimage(START_X + man.manpos.x * BLOCK_SIZE + CEN_DELTABO, START_Y + man.manpos.y * BLOCK_SIZE + CEN_DELTABO, &images[man.C_BW]);//��������
	//���úڰ׺кͺڰ�Ŀ�ĵ�
	putimage(START_X + blackbox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blackbox.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKBOX]);
	putimage(START_X + whitebox.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitebox.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITEBOX]);

	if (!(blacktarget.x == blackbox.x && blacktarget.y == blackbox.y)&& !(blacktarget.x == man.manpos.x && blacktarget.y == man.manpos.y)&&!(blacktarget.x==whitebox.x&&blacktarget.y==whitebox.y))
		putimage(START_X + blacktarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + blacktarget.y * BLOCK_SIZE + CEN_DELTABO, &images[BLACKTARGET]);
	if (!(whitetarget.x == whitebox.x && whitetarget.y == whitebox.y)&& !(whitetarget.x == man.manpos.x && whitetarget.y == man.manpos.y)&&!(whitetarget.x == blackbox.x && whitetarget.y == blackbox.y))
		putimage(START_X + whitetarget.x * BLOCK_SIZE + CEN_DELTABO, START_Y + whitetarget.y * BLOCK_SIZE + CEN_DELTABO, &images[WHITETARGET]);
	if(man.C_BW!=COMMONPLAYER)
		bwexchange();//�Զ���ǿ��״̬ת��Ϊ��ͨ״̬
}

void Gameover() {
	if (secret)//����������أ���ô����
	{
		mciSendString("close song", NULL, 0, NULL);//�ر�����
		gradient(256, 17);//����,��������
		settextstyle(30, 0, ("����"));   // ��������
		setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
		settextcolor(BLACK);    //BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext(s[6], &textr, DT_WORDBREAK);//��ʾ�ı�
		mciSendString("open music/MOSECODE.mp3 alias song", NULL, 0, NULL);//��������
		mciSendString("play song", NULL, 0, NULL);//�ظ���������
		Sleep(11000);//11��
	}//����Ħ˹����
	mciSendString("close song", NULL, 0, NULL);//�ر�����;
	//����ı���Ϣ��ʾ��ҽ�������Ħ˹�����������˵�����
}




int main() {
	IMAGE bg_img;
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	//�������˵�
flag:
	custom = 0;
	//mciSendString("close song", NULL, 0, NULL);//�ر�����
	loadimg();
	menu();//����˵�
	//������Ϸ����

	//���ñ���,�ؿ�
	//Setbackground(custom);
	//ָ�����Ͻ����꣬����
	Initobject();
	Initmap(custom);//�����custom���ڶ�ȡ�����ƻ���ĳһ�صĵ�ͼ
	//peekmessage(&m_key, EM_KEY);//��ȡ������Ϣ
	//�������

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
				conexchange();//�ı�map,���ǲ���ؿ�,condition
				convert_map();//��ؿ��Ļ��ı�custom
				break;
			case KEY_E:
				bwexchange();//E��man.C_BW���иı�
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
		Sleep(100);//100����
	} while (custom!=4&&!(custom == DARK || custom == LIGHT));
	/*system("pause");*/
	//ͨ��
	
	//secret�ڱ��δ�����һֱ��Ϊ1������Ħ˹��ת���еĲ��Ű�ť�ĳ���
	cleardevice();
	/*if(!secret)*/
	if(!(custom==DARK||custom==LIGHT))
		Gameover();//��Ϸ����,����˵��
	mciSendString("close song", NULL, 0, NULL);//�ر�����
	goto flag;
	return 0;
}