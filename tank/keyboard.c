#include <windows.h>

#include "define.h"
#include "whole.h"
#include "frame.h"

void keyboardtank ()
{                       
/* 
   函数功能:该函数判断在此函数被调用时,某个键是处于UP状态还是处于DOWN状态,及前次调用GetAsyncKeyState函数后,
   是否按过此键.如果返回值的最高位被置位,那么该键处于DOWN状态;如果最低位被置位,那么在前一次调用此函数后,此键被按过,
   否则表示该键没被按过.
*/
	if (GetAsyncKeyState(0x57)& 0x8000)
		MoveMyTank( UP );
	else if (GetAsyncKeyState(0x53)& 0x8000)  
		MoveMyTank( DOWN );
	else if (GetAsyncKeyState(0x41)& 0x8000)
        MoveMyTank( LEFT );
	else if (GetAsyncKeyState(0x44)& 0x8000)  
		MoveMyTank( RIGHT );
}


void keyboardbullet (){
    if(my_tank.CD==player_cd)
	{
		if(GetAsyncKeyState( 0x4A )& 0x8000)//发射键
		{
			BuildBullet(my_tank);
			my_tank.CD=0;
		}
	}
	else
		my_tank.CD++;
}

void keyboardmenu(){
	Player *temp = head;
	if(state == 0){
		if( (GetAsyncKeyState( VK_DOWN )& 0x8000) && state == 0){
			if(sel < menu_num){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(52,17+sel);
				printf("  ");
				GoToxy(58,17+sel);
				printf("  ");
				sel++;
				GoToxy(52,17+sel);
				printf("<<");
				GoToxy(58,17+sel);
				printf(">>");
			}
		}
		if((GetAsyncKeyState( VK_UP )& 0x8000) && state == 0){
			if(sel > 1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(52,17+sel);
				printf("  ");
				GoToxy(58,17+sel);
				printf("  ");
				sel--;
				GoToxy(52,17+sel);
				printf("<<");
				GoToxy(58,17+sel);
				printf(">>");
			}
		}
		if( (GetAsyncKeyState( 0xD )& 0x8000) && state == 0){
			if(sel == 1){
				state = 1;
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				printf("新的玩家名:\n");
				scanf("%s",name);
Start:
				printf("%s，欢迎来到坦克的世界\n按回车键开始游戏！",name);
				getchar();
				if( getchar() ){
					state = 2;
					unsigned int interval[13]={1,1,1,1,1,1,1,1,1,1,1,1,1} ;  //间隔计数器数组，用于控制速度
					Frame ();                             //打印游戏主体框架
					Initialize();                         //初始化，全局变量level初值便是1 
					for(;;)
					{
						GameCheak();                  //游戏胜负检测
						if(interval[0]++%speed==0)        //速度调整用,假设interval[0]为a, 语句意为 a % 2==0,a=a+1; 
						{
							BulletFly ( bullet );
							for(int i=0 ; i<=3 ; i++)         //AI坦克移动循环
							{
								if(AI_tank[i].model==2 && interval[i+1]++%2==0) //四个坦克中的快速坦克单独使用计数器1,2,3,4
									MoveAITank( & AI_tank[i]);
								if(AI_tank[i].model!=2 && interval[i+5]++%3==0) //四个坦克中的慢速坦克单独使用计数器5,6,7,8
									MoveAITank( & AI_tank[i]);
							}
						

							for(int i=0;i<=3;i++){      
								int sum = AI_tank[0].revive+AI_tank[1].revive+AI_tank[2].revive+AI_tank[3].revive;                             //建立AI坦克部分
								if(AI_tank[i].alive==0 && sum < enemy_num && interval[9]++%90==0)  
								{                                               //如果坦克不存活。计时,每次建立有间隔  1750 ms
									BuildAITank( &position, & AI_tank[i] );     //建立AI坦克（复活）
									break;                                      //每次循环只建立一个坦克
								}
								if(!AI_tank[0].alive && !AI_tank[1].alive && !AI_tank[2].alive && !AI_tank[3].alive && sum < enemy_num ){
									BuildAITank( &position, & AI_tank[i] );     //建立AI坦克（复活）
									break;                                      //每次循环只建立一个坦克
								}
							}

							for(int i=0;i<=3;i++){
								if(AI_tank[i].alive)
									BuildAIBullet(&AI_tank[i]);                 //AIshoot自带int自增计数CD,不使用main中的CD interval
							}
						}


						if(my_tank.alive==0 && interval[10]++%100==0 && my_tank.revive < MAX_LIFE)
							BuildMyTank( &my_tank );
						if(my_tank.alive && interval[11]++%6==0 )
							keyboardtank ();
						if(my_tank.alive && interval[12]++%7==0 )
							keyboardbullet ();
			
						keyboardmenu();
						Sleep(5);
					}
				}
			}

			if(sel == 2){
				state = 3;
				system("cls");
				MenuFrame();
				GoToxy(45,11);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
   				printf("======================");
				GoToxy(47,13);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				printf("玩家名：%-100s",temp->name);
				GoToxy(47,15);
				printf("关卡：%-10d",temp->level_num);
				GoToxy(47,17);
				printf("分数：%-10d",temp->score_num);
				GoToxy(47,19);
				printf("难度：%-10d",temp->diffi_num);
				GoToxy(47,21);
				printf("敌坦克数量：%2d",temp->tank_num);
				GoToxy(47,23);
				printf("玩家子弹冷却：%2d",temp->my_cd_num);
				GoToxy(47,25);
				printf("电脑子弹冷却：%2d",temp->ai_cd_num);
				GoToxy(47,29);
				printf("按下空格继续");
				GoToxy(45,27);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("======================");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(43,13);
				printf(">>");

			}

			if(sel == 3){
				state = 5;
				system("cls");
				MenuFrame();
				GoToxy(45,17);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("======================");
				GoToxy(50,18);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("敌坦克数量：%2d",enemy_num);
				GoToxy(49,19);
				printf("玩家子弹冷却：%2d",player_cd);
				GoToxy(49,20);
				printf("电脑子弹冷却：%2d",ai_cd);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(44,17+sel2);
				printf("<<");
				GoToxy(67,17+sel2);
				printf(">>");
				GoToxy(45,21);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("======================");
			}
		
			if(sel == 4){
				exit(0);
			}
		}
	}
	if( state == 2){
		if (GetAsyncKeyState( 0x1B )& 0x8000){  // Esc键
			system("cls");
			MenuFrame();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			GoToxy(54,16);
			printf("保存成功！");
			GoToxy(52,22);
			printf("按下回车以退出");
			while(1){
				if (GetAsyncKeyState( 0xD )& 0x8000) exit(0);
			}
		}
		else if (GetAsyncKeyState( 0x20 )& 0x8000){  //空格
			Stop();
		}else	if (speed>1 && GetAsyncKeyState( VK_PRIOR )& 0x8000)   // PgUp键
			{
				Sleep(200);
				speed--;
				GoToxy(102,11);           //在副屏幕打印出当前速度
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
				printf("%d ",11-speed);   //副屏幕显示的速度为1~10
			}
			else if (speed<10 && GetAsyncKeyState( VK_NEXT )& 0x8000)  // PgDown 键
			{
				Sleep(200);
				speed++;
				GoToxy(102,11);           //在副屏幕打印出当前速度
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
				printf("%d ",11-speed);   //副屏幕显示的速度为1~10
			}
	}

	if( state == 3){
		if( (GetAsyncKeyState( VK_RIGHT )& 0x8000) && state == 3 && sel3 < sum){
			temp = head;
			sel3++;
			for(int i = 1;i < sel3;i++) temp = temp->next;
			GoToxy(47,13);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			printf("玩家名：%-100s",temp->name);
			GoToxy(47,15);
			printf("关卡：%-10d",temp->level_num);
			GoToxy(47,17);
			printf("分数：%-10d",temp->score_num);
			GoToxy(47,19);
			printf("难度：%-10d",temp->diffi_num);
			GoToxy(47,21);
			printf("敌坦克数量：%2d",temp->tank_num);
			GoToxy(47,23);
			printf("玩家子弹冷却：%2d",temp->my_cd_num);
			GoToxy(47,25);
			printf("电脑子弹冷却：%2d",temp->ai_cd_num);
		}

		if( (GetAsyncKeyState( VK_LEFT )& 0x8000) && state == 3 && sel3 > 1){
			temp = head;
			sel3--;
			for(int i = 1;i < sel3;i++) temp = temp->next;
			GoToxy(47,13);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			printf("玩家名：%-100s",temp->name);
			GoToxy(47,15);
			printf("关卡：%-10d",temp->level_num);
			GoToxy(47,17);
			printf("分数：%-10d",temp->score_num);
			GoToxy(47,19);
			printf("难度：%-10d",temp->diffi_num);
			GoToxy(47,21);
			printf("敌坦克数量：%2d",temp->tank_num);
			GoToxy(47,23);
			printf("玩家子弹冷却：%2d",temp->my_cd_num);
			GoToxy(47,25);
			printf("电脑子弹冷却：%2d",temp->ai_cd_num);
		}
	
		if( (GetAsyncKeyState( 0x20 )& 0x8000) && state == 3 ){
			for(int i = 1;i < sel3;i++) temp = temp->next;
			strcpy(name,temp->name);
			level = temp->level_num;
			score = temp->score_num;
			speed = 11 - temp->diffi_num;
			enemy_num = temp->tank_num;
			player_cd = temp->my_cd_num;
			ai_cd = temp->ai_cd_num;
			system("cls");
			goto Start;
		}
	
		if( (GetAsyncKeyState( 0x1B )& 0x8000) && state == 3){
			system("cls");
			displaymenu();
			state = 0;
		}
	}

	if( state == 5 ){
		if( (GetAsyncKeyState( VK_DOWN )& 0x8000) && state == 5){
			if(sel2 < 3){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(44,17+sel2);
				printf("  ");
				GoToxy(67,17+sel2);
				printf("  ");
				sel2++;
				GoToxy(44,17+sel2);
				printf("<<");
				GoToxy(67,17+sel2);
				printf(">>");
			}
		}

		if((GetAsyncKeyState( VK_UP )& 0x8000) && state == 5){
			if(sel2 > 1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				GoToxy(44,17+sel2);
				printf("  ");
				GoToxy(67,17+sel2);
				printf("  ");
				sel2--;
				GoToxy(44,17+sel2);
				printf("<<");
				GoToxy(67,17+sel2);
				printf(">>");
			}
		}

		if( (GetAsyncKeyState( VK_RIGHT )& 0x8000) && state == 5 ){
			if(sel2 == 2 && player_cd < 20){
				player_cd++;
				GoToxy(49,19);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("玩家子弹冷却：%2d",player_cd);
			}
			if( sel2 == 3 && ai_cd < 24 ){
				ai_cd++;
				GoToxy(49,20);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("电脑子弹冷却：%2d",ai_cd);
			}
			if( sel2 == 1 && enemy_num < 32){
				enemy_num++;
				GoToxy(50,18);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("敌坦克数量：%2d",enemy_num);
			}
		}

		if( (GetAsyncKeyState( VK_LEFT )& 0x8000) && state == 5 ){
			if( sel2 == 2 && player_cd > 7 ){
				player_cd--;
				GoToxy(49,19);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("玩家子弹冷却：%2d",player_cd);
			}
			if( sel2 == 3 && ai_cd > 15 ){
				ai_cd--;
				GoToxy(49,20);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("电脑子弹冷却：%2d",ai_cd);
			}
			if( sel2 == 1 && enemy_num > 16){
				enemy_num--;
				GoToxy(50,18);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
				printf("敌坦克数量：%2d",enemy_num);
			}
		}

		if( (GetAsyncKeyState( 0x1B )& 0x8000) && state == 5){
			system("cls");
			displaymenu();
			state = 0;
		}
	

	}



}

