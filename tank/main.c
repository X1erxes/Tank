#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "frame.h"
#include "bullet.h"
#include "tank.h"
#include "map.h"
#include "keyboard.h"
#include "process.h"


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
 
//注意map数组应是纵坐标在前，横坐标在后，既map[y][x]，(∵数组行长度在前，列长度在后)
//map里的值: 个位数的值为地图方块部分，百位数的值为坦克,子弹在map上没有值(子弹仅仅是一个假坐标)
//map里的值: 0为可通过陆地，1为红砖，2黄砖，5为水，100~103为敌方坦克，200为我的坦克，

 
int main ()                               //主函数
{
	int record = 1;
	srand(time(NULL)); //设置随机数种子(若不设置种子而调用rand会使每次运行的随机数序列一致)随机数序列指:如首次调用rand得到1,第二次得2,第三次3,则此次随机数序列为1,2,3
	HideCursor();                         //隐藏光标
	system("mode con cols=112 lines=43"); //控制窗口大小
	displaymenu();
	while(1){
		if(record++ % 100 == 0){
			keyboardmenu();
			Sleep(105);
		}
	}
	return 0;
}
 

 