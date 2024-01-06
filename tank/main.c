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
	unsigned int interval[13]={1,1,1,1,1,1,1,1,1,1,1,1,1} ;  //间隔计数器数组，用于控制速度

	srand(time(NULL)); //设置随机数种子(若不设置种子而调用rand会使每次运行的随机数序列一致)随机数序列指:如首次调用rand得到1,第二次得2,第三次3,则此次随机数序列为1,2,3
	HideCursor();                         //隐藏光标
	system("mode con cols=112 lines=43"); //控制窗口大小
	//Frame ();                             //打印游戏主体框架
	displaymenu(1);
	scanf("%d");
	//Initialize();                         //初始化，全局变量level初值便是1 


	/*for(;;)
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
			for(int i=0;i<=3;i++)                                   //建立AI坦克部分
	  		   	if(AI_tank[i].alive==0 && AI_tank[i].revive<4 && interval[9]++%90==0)  //一个敌方坦克每局只有4条命
				{                                               //如果坦克不存活。计时,每次建立有间隔  1750 ms
             	  	BuildAITank( &position, & AI_tank[i] );     //建立AI坦克（复活）
			  		break;                                      //每次循环只建立一个坦克
		  		}
			for(int i=0;i<=3;i++)
				if(AI_tank[i].alive)
					BuildAIBullet(&AI_tank[i]);                 //AIshoot自带int自增计数CD,不使用main中的CD interval
		}
    	if(my_tank.alive==0 && interval[10]++%100==0 && my_tank.revive < MAX_LIFE)
     		BuildMyTank( &my_tank );
		if(my_tank.alive && interval[11]++%6==0 )
        	keyboardtank ();
		if(my_tank.alive && interval[12]++%7==0 )
         	keyboardbullet ();
		
		keyboardmenu();
		Sleep(5);
	}*/
	return 0;
}
 

 