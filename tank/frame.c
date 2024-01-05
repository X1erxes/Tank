#include <windows.h>
#include "header.h"

void Frame ()     //打印游戏主体框架
{                 //SetConsoleTextAttribute为设置文本颜色和文本背景颜色函数
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
	printf("  ▂▂▂▂▂▂▂▂▂▂▂▂▂ \n");

	for(int i=0;i<14;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	    printf("▕                                                                              ▏");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
		printf(" |                          |\n");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("▕                                                                              ▏");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
	printf(" |═════════════|\n");


	for(int i=0;i<24;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	    printf("▕                                                                              ▏");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
		printf(" |                          |\n");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_BLUE); 
	printf(" ﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊\n");
	SideScreen ();  //打印副屏幕
}

void SideScreen ()  //副屏幕 行(84起,110末,若双字符宽则在108打印最后一个字）列(11上屏末,13下屏初,39下屏末。为美观最好打在38)
{                   // |         第  d  关         |   " |                          |\n"
	GoToxy(93,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	printf("第     关");
	GoToxy(92,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	printf("分  数：");
	GoToxy(92,7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printf("生  命：");
	GoToxy(86,9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	printf("剩余敌方坦克：");
	GoToxy(86,11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
	printf("当前游戏速度：  %d",21-speed);
	GoToxy(86,13);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("当前游戏状态：");
	GoToxy(94,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	GoToxy(94,24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	printf("帮  助");
	GoToxy(86,27);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printf("方向键  ←↑→↓  移动");
	GoToxy(93,29);
	printf("x 键 射击");
	GoToxy(89,31);
	printf("+ - 调整游戏速度");
	GoToxy(90,33);
	printf("游戏速度范围1~20");
	GoToxy(90,35);
	printf("回车键 暂停游戏");
	GoToxy(90,37);
	printf("Esc键  退出游戏");
/*	printf("帮  助");     //这是第二种详细说明的样式
	GoToxy(86,21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printf("方向键  ←↑→↓  移动");
	GoToxy(93,23);
	printf("x 键 射击");
	GoToxy(89,25);
	printf("+ - 调整游戏速度");
	GoToxy(90,27);
	printf("游戏速度范围1~20");
	GoToxy(90,29);
	printf("回车键 暂停游戏");
	GoToxy(90,31);
	printf("Esc键  退出游戏");
	GoToxy(86,33);
	printf("敌方坦克全部消灭则过关");
	GoToxy(87,34);
	printf("己方坦克生命值为0 或");
	GoToxy(86,35);
	printf("正下方的老家被毁则失败");
	GoToxy(86,36);
	printf("己坦克与敌坦克子弹碰撞");
	GoToxy(87,37);
	printf("则抵消，敌坦克间子弹碰");
	GoToxy(86,38);
	printf("撞不抵消且可穿过敌坦克");*/
}

void ColorChoose(int color)   //颜色选择函数
{
	switch(color)
	{
	   	case 1:               //天蓝色(我的坦克颜色)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			break;
		case 2:               //绿色
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);	
			break;
		case 3:               //黄色
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
			break;
		case 4:               //红色
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			break;
		case 5:               //紫色
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
			break;
		case 6:               //白色
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
			break;
		case 7:               //深蓝色(∵颜色深难与黑色背景辨识度不高 ∴坦克颜色不选用此颜色),只用在字体颜色闪烁中
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			break;
	}
}

void ClearMainScreen()  //主屏幕清屏函数，因使用system("cls");再打印框架有一定几率造成框架上移一行的错误，所以单独编写清屏函数
{
	for(int i=1;i<40;i++)
	{
		GoToxy(2,i);
		printf("                                                                              ");
	}
}

void HideCursor()  //隐藏光标
{                  //CONSOLE_CURSOR_INFO结构体包含控制台光标的信息,DWORD dwSize光标百分比厚度（1~100）和BOOL bVisible光标是否可见
	CONSOLE_CURSOR_INFO cursor_info= {1,0} ;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE) , &cursor_info ); //SetConsoleCursorInfo用来设置指定的控制台光标的大小和可见性。
}

void GoToxy(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
	COORD  coord;         //使用头文件自带的坐标结构
	coord.X=x;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
	coord.Y=y;
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
	SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}