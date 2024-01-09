#include <windows.h>

#include "whole.h"

void Frame (void)     //打印游戏主体框架
{                 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  ");//顶部
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
	printf("  ▂▂▂▂▂▂▂▂▂▂▂▂▂ \n");

	for(int i=0;i<14;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	    printf("▕                                                                              ▏");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
		printf(" |                          |\n");//中部
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("▕                                                                              ▏");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
	printf(" |═════════════|\n");//右框框


	for(int i=0;i<24;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	    printf("▕                                                                              ▏");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_BLUE); 
		printf(" |                          |\n");//中部
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY| FOREGROUND_BLUE); 
	printf(" ﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊\n");//底部
	SideScreen ();  //打印副屏幕
	return;
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
	printf("当前游戏难度：  %d",11-speed);
	GoToxy(86,13);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("当前游戏状态：");
	GoToxy(94,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	GoToxy(93,17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	printf("帮     助");
	GoToxy(93,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printf("WSAD  移动");
	GoToxy(93,21);
	printf("J 键 射击");
	GoToxy(90,23);
	printf("] [ 调整游戏难度");
	GoToxy(90,25);
	printf("游戏难度范围1~10");
	GoToxy(90,27);
	printf("回车键 暂停游戏");
	GoToxy(90,29);
	printf("Esc键  退出游戏");
	GoToxy(90,31);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
	printf("玩家名：%s",name);
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

void HideCursor(void)  //隐藏光标
{        
	CONSOLE_CURSOR_INFO cursor_info= {1,0} ;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE) , &cursor_info );
	return;
}

void displaymenu(){
	MenuFrame();//主菜单框架
	GoToxy(50,16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("经典坦克大战");
    GoToxy(45,17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    printf("  ==================  ");
    GoToxy(54,18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
	printf("%s",MenuText[0]);//开始
	GoToxy(54,19);
	printf("%s",MenuText[1]);//载入
	GoToxy(54,20);
	printf("%s",MenuText[2]);//设置
	GoToxy(54,21);
	printf("%s",MenuText[3]);//退出
	GoToxy(45,22);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    printf("  ==================  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	GoToxy(52,17+sel);
	printf("<<");
	GoToxy(58,17+sel);
	printf(">>");
	state = 0;//第一阶段
}

void MenuFrame(){
	GoToxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	printf("▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁");
	for(int i=0;i<39;i++)
	{
	    printf("|                                                                                                              |");
	}
	printf("▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔");
	return;
}

void GoToxy(int x,int y)  //光标移动函数，X表示横坐标，Y表示纵坐标。
{
	COORD  coord;         //使用头文件自带的坐标结构
	coord.X=x;            //这里将int类型值传给short,不过程序中涉及的坐标值均不会超过short范围
	coord.Y=y;
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄
	SetConsoleCursorPosition(a,coord);         //以标准输出的句柄为参数设置控制台光标坐标
}