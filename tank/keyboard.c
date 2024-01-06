#include <windows.h>

#include "define.h"
#include "whole.h"

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
    if(my_tank.CD==7)
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

    if(GetAsyncKeyState( VK_UP ) && state == 0){
        
    }
    
    if (GetAsyncKeyState( 0x1B )& 0x8000){  // Esc键
		exit(0);                                //退出程序函数
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

