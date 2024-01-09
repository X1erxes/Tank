#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "frame.h"		//界面框架部分
#include "bullet.h"		//子弹部分
#include "tank.h"		//坦克部分
#include "map.h"		//地图部分
#include "keyboard.h"	//键盘接收部分
#include "process.h"	//游戏进程部分
#include "savedata.h"	//数据保存部分
 
//∵所有的函数都有可能对全局变量map进行读写(改变)，
//∴函数中不另说明是否会对全局变量map读写

 
int main (void){
	int record = 1;						  //控制键盘接收频率
	srand(time(NULL)); 					  //设置随机数种子
	HideCursor();                         //隐藏光标
	system("mode con cols=112 lines=43"); //控制窗口大小
	StartFile();						  //初始化一个存档
	GetfromFile();						  //读取文件中的链表
	displaymenu();						  //打印主菜单
	while(1){
		if(record++ % 100 == 0){	      //避免键盘接收过快
			keyboardmenu();				  //对应操作
			Sleep(60);					  //避免键盘接收过快
		}
	}
	return 0;
}