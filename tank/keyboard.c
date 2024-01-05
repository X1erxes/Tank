#include <windows.h>
#include "define.h"
#include "header.h"

void keyboard ()
{               // kbhit()   getch()  用法可用但是不好用            
/* 
   函数功能:该函数判断在此函数被调用时,某个键是处于UP状态还是处于DOWN状态,及前次调用GetAsyncKeyState函数后,
   是否按过此键.如果返回值的最高位被置位,那么该键处于DOWN状态;如果最低位被置位,那么在前一次调用此函数后,此键被按过,
   否则表示该键没被按过.
   这里GetAsyncKeyState比 kbhit() + getch() 好用,操作更顺畅.   GetAsyncKeyState的返回值表示两个内容，
   一个是最高位bit的值，代表这个键是否被按下。一个是最低位bit的值,代表上次调用GetAsyncKeyState后，这个键是否被按下。
   &为与操作，&0x8000就是判断这个返回值的高位字节。如果high-order bit是1,则是按下状态，否则是弹起状态，为0
*/
	int count=0;
	if (GetAsyncKeyState(VK_UP)& 0x8000)  
		MoveMyTank( UP );
	else if (GetAsyncKeyState(VK_DOWN)& 0x8000)  
		MoveMyTank( DOWN );
	else if (GetAsyncKeyState(VK_LEFT)& 0x8000)
        MoveMyTank( LEFT );
	else if (GetAsyncKeyState(VK_RIGHT)& 0x8000)  
		MoveMyTank( RIGHT );
	else if (GetAsyncKeyState( 0x1B )& 0x8000)  // Esc键
		exit(0);                                //退出程序函数
	else if (GetAsyncKeyState( 0x20 )& 0x8000)  //空格
		Stop();
	else if (count++%7==0)            //这里添加计数器是为了防止按键粘连不能达到微调效果
	{
		if (speed>1 && GetAsyncKeyState( VK_PRIOR )& 0x8000)   // PgUp键
		{
			speed--;
			GoToxy(102,11);           //在副屏幕打印出当前速度
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
			printf("%d ",21-speed);   //副屏幕显示的速度为1~10
		}
		else if (speed<20 && GetAsyncKeyState( VK_NEXT )& 0x8000)  // PgDown 键
		{
			speed++;
			GoToxy(102,11);           //在副屏幕打印出当前速度
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
			printf("%d ",21-speed);   //副屏幕显示的速度为1~10
		}
	}


	if(my_tank.CD==7)
	{
		if(GetAsyncKeyState( 88 )& 0x8000)//发射键
		{
			BuildBullet(my_tank);
			my_tank.CD=0;
		}
	}
	else
		my_tank.CD++;
}

