#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "bullet.h"
#include "tank.h"
#include "define.h"
#include "header.h"
#include "struct.h"
#include "map.h"
#include "keyboard.h"

                           //里规格：长39*2=78 （真坐标）(假坐标宽为39)  高39
                           //外规格：长41*2=82 （真坐标）(假坐标宽为41)  高41


//程序中未写入函数参数表中且未说明的变量只有map二维数组,level_info数组和level   
 
/*
      此程序中涉及的x,y类的坐标值，分为以下两种：                                 
                                                                                                  
假坐标：这里的坐标指的是以一个■长度为单位的坐标，而不是真正的coord坐标 (用于map数组的坐标)                             
                                                                                                  
真坐标：头文件自带的坐标结构coord中的坐标（也可以说是控制台里的真正坐标值）                                 
                                                                                                  
  区别：纵坐标y两值一致，假横坐标x值与真正coord横坐标（真坐标）关系是 x * 2 = coord 横坐标    
                                                                                                            
		  coord横坐标既指GoTo函数中的x参数,因为本程序游戏界面以一个■长度为基本单位，                    
                                                                                                  
		  可以说涉及的coord横坐标全是偶数。既假坐标要变真坐标（变真坐标才能发挥真正作用），横坐标须乘以2                                    
                                                           
*/
 

//∵所有的函数都有可能对全局变量map进行读写(改变)，
//∴函数中不另说明是否会对全局变量map读写
//基本操作与游戏辅助函数
void GoToxy(int x,int y);    //光标移动
void HideCursor();           //隐藏光标
void keyboard ();            //接受键盘输入
void Initialize();           //初始化(含有对多个数据的读写)
void Stop();                 //暂停
void Frame ();               //打印游戏主体框架
void SideScreen ();          //副屏幕打印
void GameCheak();            //检测游戏输赢
void GameOver( int home );  //游戏结束
void ClearMainScreen();      //主屏幕清屏函数∵system("cls")后打印框架有一定几率造成框架上移一行的错误∴单独编写清屏函数
void ColorChoose(int color); //颜色选择函数
void NextLevel();            //下一关(含有对level全局变量的读写)
 
 
//DWORD WINAPI InputX(LPVOID lpParameter); //声明线程函数，用于检查X键输入并设置X键的输入冷却时间
 
 
//注意map数组应是纵坐标在前，横坐标在后，既map[y][x]，(∵数组行长度在前，列长度在后)
//map里的值: 个位数的值为地图方块部分，百位数的值为坦克,子弹在map上没有值(子弹仅仅是一个假坐标)
//map里的值: 0为可通过陆地，1为红砖，2黄砖，5为水，100~103为敌方坦克，200为我的坦克，
 
 
 
int main ()                               //主函数
{
	int i;
	unsigned int interval[12]={1,1,1,1,1,1,1,1,1,1,1,1} ;  //间隔计数器数组，用于控制速度

	srand(time(NULL)); //设置随机数种子(若不设置种子而调用rand会使每次运行的随机数序列一致)随机数序列指:如首次调用rand得到1,第二次得2,第三次3,则此次随机数序列为1,2,3
	HideCursor();                         //隐藏光标
	system("mode con cols=112 lines=42"); //控制窗口大小
	Frame ();                             //打印游戏主体框架
	Initialize();                         //初始化，全局变量level初值便是1 


//	HANDLE h1 , h2 ;
    //定义句柄变量
	for(;;)
	{
		if(interval[0]++%speed==0)        //速度调整用,假设interval[0]为a, 语句意为 a % 2==0,a=a+1; 
		{
			GameCheak();                  //游戏胜负检测
			BulletFly ( bullet );
			for(i=0 ; i<=3 ; i++)         //AI坦克移动循环
			{
				if(AI_tank[i].model==2 && interval[i+1]++%2==0) //四个坦克中的快速坦克单独使用计数器1,2,3,4
					MoveAITank( & AI_tank[i]);
				if(AI_tank[i].model!=2 && interval[i+5]++%3==0) //四个坦克中的慢速坦克单独使用计数器5,6,7,8
					MoveAITank( & AI_tank[i]);
			}
			for(i=0;i<=3;i++)                                   //建立AI坦克部分
	  		   	if(AI_tank[i].alive==0 && AI_tank[i].revive<4 && interval[9]++%90==0)  //一个敌方坦克每局只有4条命
				{                                               //如果坦克不存活。计时,每次建立有间隔  1750 ms
             	  	BuildAITank( &position, & AI_tank[i] );     //建立AI坦克（复活）
			  		break;                                      //每次循环只建立一个坦克
		  		}
			for(i=0;i<=3;i++)
				if(AI_tank[i].alive)
					BuildAIBullet(&AI_tank[i]);                 //AIshoot自带int自增计数CD,不使用main中的CD interval
			if(my_tank.alive && interval[10]++%2==0 )
         		keyboard ();
    		if(my_tank.alive==0 && interval[11]++%30==0 && my_tank.revive < MAX_LIFE)
     			BuildMyTank( &my_tank );
		}
		Sleep(5);
	}
	return 0;
}
 
 
/*//这里的多线程暂时不用                   //x键用于子弹发射，x键的冷却时间不能和上下左右一同设置，那样就太快了
DWORD WINAPI InputX(LPVOID lpParameter)    //如果不用多线程运行，那么在x键冷却时间内程序会因Sleep将会挂起，暂停运行
{                                          //因为只有一个变量改变，而且变量改变先后顺序是显而易见的，所以不必设置缓冲区
	for(;;)                              
	{                                    
		if(GetAsyncKeyState( 88 )& 0x8000) //88为x键键值,当摁下x并且x键处于可输入状态
		{
			key_x=1;                       // X键是否允许被“读入”的变量，也是子弹是否可以发射的变量
	    	Sleep(600);                    // 子线程Sleep中，x就不能被"读入"，主线程每操作完一次子弹发射，key_x会归零
		}
		Sleep(10);
	}
	return 0;
}*/
 

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
 
 
void Stop()    //暂停
{
	int color=1,timing=0;
	while(1)
	{
		if(timing++%30==0)
		{
			ColorChoose(color);   //颜色选择
			GoToxy(100,13);       //副屏幕打印
			printf("游戏暂停");
			GoToxy(88,17);
			printf("按回车键回到游戏");
			GoToxy(88,18);
			printf("或按 Esc键退出游戏");
			if(++color==8)
				color=1;
		}
		if (GetAsyncKeyState( 0xD )& 0x8000)      //回车键
		{
			GoToxy(100,13);       //副屏幕打印
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			printf("正在进行");   //覆盖掉原来的提示
			GoToxy(88,17);
			printf("                     ");
			GoToxy(88,18);
			printf("                     ");
			break;
		}
		else if(GetAsyncKeyState( 0x1B )& 0x8000) //Esc键退出	
			exit(0);
		Sleep(20);
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
 
 
void GameOver(int home)
{
	int timing=0,color=1;
	while(1)
	{
		if(timing++%30==0)         //游戏结束原因为生命值为0
		{
			ColorChoose(color);    //颜色选择
			if(home)               //游戏结束原因为老家被毁,则多打印一行字以提示玩家
			{
				GoToxy(37,19);     //主屏幕中心打印
				printf("老家被毁!");
			}
			GoToxy(37,20);         //主屏幕中心打印
			printf("游戏结束!");
			GoToxy(100,13);        //副屏幕打印
			printf("游戏结束");
			GoToxy(88,17);
			printf("请按回车键重新开始!");
			GoToxy(88,18);
			printf("或按 Esc键退出游戏!");
			if(++color==8)
				color=1;
		}
		if (GetAsyncKeyState( 0xD )& 0x8000)  //回车键
		{
//			system("cls");       //清屏,这里清屏后再次打印框架有一定几率造成框架上移一行的bug，因此选用自建清屏函数
//			Frame ();            //重新打印游戏框架
			score-=500;          //分数-500
			ClearMainScreen();   //主屏清屏函数，无需再次打印框架
			Initialize();        //从本关重新开始
			break;
		}
		else if(GetAsyncKeyState( 0x1B )& 0x8000)  //Esc键退出	
			exit(0);
		Sleep(20);
	}
}
 
 
void NextLevel()
{
	int timing=0,color=1;
	level++;
	if(level<=MAX_LEVEL)
		while(1)
		{
			if(timing++%10==0)//颜色频闪
			{
				ColorChoose(color);   //颜色选择   
				GoToxy(37,20);        //主屏幕中心打印
				printf("恭喜过关!");
				GoToxy(100,13);       //副屏幕打印
				printf("等待下关");
				GoToxy(87,17);
				printf("请按回车键进入下一关!");
				GoToxy(88,18);
				printf("或按 Esc键退出游戏!");
				if(++color==8)	
					color=1;
			}
			if (GetAsyncKeyState( 0xD )& 0x8000)  //回车键
			{
				GoToxy(88,17);        //抹除副屏幕中的提示
				printf("                     ");
				GoToxy(88,18);
				printf("                     ");
				ClearMainScreen();   //主屏清屏函数，无需再次打印框架
				Initialize();        //初始化从下一关开始,level已++
				break;
			}
			else if(GetAsyncKeyState( 0x1B )& 0x8000)  //Esc键退出	
				exit(0);
			Sleep(20);
		}
	else   //level>8 通关
		while(1)
		{
			if(timing++%5==0)
			{
				ColorChoose(color);
				GoToxy(33,20);        //主屏幕中心打印
				printf("恭喜通过全部关卡!");
				GoToxy(100,13);       //副屏幕打印
				printf("已通全关");
				GoToxy(88,17);
				printf("恭喜通过全部关卡!");
				GoToxy(88,19);
				printf("按 Esc键退出游戏!");
				if(++color==8)	
					color=1;
			}
			if(GetAsyncKeyState( 0x1B )& 0x8000)  //Esc键退出	
				exit(0);
			Sleep(10);
		}
}
 
 
void GameCheak()
{                           //剩余敌人为0且四坦克全部不存活
	if(remain_enemy<=0 && !AI_tank[0].alive && !AI_tank[1].alive && !AI_tank[2].alive && !AI_tank[3].alive )
		NextLevel();        //进入下一关
	if(my_tank.revive>=MAX_LIFE)   //我的生命值(复活次数)全部用完 MAX_LIFE
		GameOver(0);        //游戏结束，传入0代表我的复活次数用光(生命值为0)。游戏结束有两种判断，另一种是老家被毁
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
 
 
void Initialize()      //初始化
{
	remain_enemy=16;
	my_tank.revive=0;  //我的坦克复活次数为0
	position=0;
	bul_num=0;
	GetMap();
	BuildMyTank( &my_tank );
	for(int i=0;i<12;i++)     //子弹初始化
	{
		bullet [i].exist=0;
		bullet [i].initial=0;
	}
	for(int i=0;i<=3;i++)         //AI坦克初始化
	{
		AI_tank [i].revive=0;
		AI_tank [i].alive=0;  //初始化坦克全是不存活的，BuildAITank()会建立重新建立不存活的坦克
		AI_tank [i].stop=0;
		AI_tank [i].num=i;
		AI_tank [i].my=0;
		AI_tank [i].CD=0;
	}
	GoToxy(97,2);                        //在副屏幕上关卡数
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
	printf("%d",level);
	GoToxy(102,5);                       //在副屏幕上打印分数
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	printf("%d   ",score);
	GoToxy(102,7);                       //在副屏幕打印我的剩余生命值
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printf("%d", MAX_LIFE-my_tank.revive);
	GoToxy(102,9);                       //在副屏幕上打印剩余坦克数
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	printf("%d ",remain_enemy);
	GoToxy(100,13);                      //在副屏幕上打印状态
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN);
	printf("正在游戏");
}