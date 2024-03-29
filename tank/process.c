#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "whole.h"
#include "define.h"
#include "savedata.h"

void Initialize()      //初始化
{

	time_t t;
	struct tm *lt;
	time(&t); //获取时间戳。
	lt=localtime(&t);//转为时间结构。

	Player *temp = head;
	while(temp != NULL){
		if(!strcmp(temp->name,name)){
			temp->level_num = level;
			temp->score_num = score;
			temp->diffi_num = 11-speed;
			temp->tank_num = enemy_num;
			temp->my_cd_num = player_cd;
			temp->ai_cd_num = ai_cd;
			temp->year = lt->tm_year+1900;
			temp->month = lt->tm_mon+1;
			temp->day = lt->tm_mday;
			temp->hour = lt->tm_hour;
			temp->min = lt->tm_min;
			break;
		}
		temp = temp->next;
	}
	
	if(temp == NULL){
		temp = head;
		while(temp->next != NULL) temp = temp->next;
		Player *m1 = (Player *)malloc(LEN);
		strcpy(m1->name,name);
		m1->level_num = level;
		m1->score_num = score;
		m1->diffi_num = 11-speed;
		m1->tank_num = enemy_num;
		m1->my_cd_num = player_cd;
		m1->ai_cd_num = ai_cd;
		m1->next = NULL;
		m1->year = lt->tm_year+1900;
		m1->month = lt->tm_mon+1;
		m1->day = lt->tm_mday;
		m1->hour = lt->tm_hour;
		m1->min = lt->tm_min;
		temp->next = m1;
		sum++;
	}

	SavetoFile();

	remain_enemy=enemy_num;
	my_tank.revive=0;  //我的坦克复活次数为0
	position=0;
	bul_num=0;
	GetMap();
	BuildMyTank( &my_tank );
	for(int i=0;i<20;i++)     //子弹初始化
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
		AI_tank [i].CD=ai_cd-2;
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

void GameCheak()
{                           //剩余敌人为0且四坦克全部不存活
	if(remain_enemy<=0 && !AI_tank[0].alive && !AI_tank[1].alive && !AI_tank[2].alive && !AI_tank[3].alive )
		NextLevel();        //进入下一关
	if(my_tank.revive>=MAX_LIFE)   //我的生命值(复活次数)全部用完 MAX_LIFE
		GameOver(0);        //游戏结束，传入0代表我的复活次数用光(生命值为0)。游戏结束有两种判断，另一种是老家被毁
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
			score-= 1000*(11-speed);
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

