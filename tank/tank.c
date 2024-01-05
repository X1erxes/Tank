#include "struct.h"
#include "header.h"
#include <windows.h>

//position为坦克生成位置,-1为左位置,0为中间,1为右,2为我的坦克位置
void BuildAITank(int* position, Tank* AI_tank)   //执行一次该函数只建立一个坦克
{                                         //rand函数公式：0<=rand()%(a+1)<=a  0+m<=rand()%(n-m+1)+m<=n  
                                          //rand函数实现1到n：1<=rand()%(n)+1<=n
   	if(AIPositionCheak(*position))        //若此位置无障碍,可生成。position参数详见AIPositionCheak函数定义
	{
		AI_tank->x= 20 + 18*(*position);  //20 + 18 * position 对应三个生成位置的x假坐标
		AI_tank->y=2;
		if(AI_tank->revive==level_info[level-1].firm_tank_order)  //坦克出现(复活)次序==关卡信息(level_info)中firm tank的出现次序
		{
			AI_tank->model = 3;           //3为firm tank的模型(外观)
			AI_tank->color = 2;           //颜色参数2为绿色，具体详见函数ColorChoose
		}
		else if(AI_tank->revive==level_info[level-1].fast_tank_order)  //同上if，这里是fast_tank的
		{
			AI_tank->model = 2;
			AI_tank->color = rand()%6+1;  //若不是firm tank则随机颜色，颜色参数为1~6,分别代表不同颜色,详见函数ColorChoose
		}
		else      //普通坦克
		{
			AI_tank->model = 1;
	 	  	AI_tank->color = rand()%6+1;  //若不是firm tank则随机颜色
		}
		AI_tank->alive = 1;       //坦克变为存在
		AI_tank->direction = 2 ;  //方向朝下
		AI_tank->revive++;        //复活次数+1
		PrintTank(*AI_tank);
		(*position)++; 
		remain_enemy--;
		GoToxy(102,9);            //在副屏幕上打印剩余坦克数
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		printf("%d ",remain_enemy);
		if(*position==2)          //position只能为0,1，-1，这里position循环重置
    		*position = -1;
  	   	return ;                  //若生成了一辆坦克，则结束该函数
	}
}

void BuildMyTank (Tank* my_tank) //建立我的坦克
{
	my_tank->x=15;
   	my_tank->y=38;
   	my_tank->stop=0;
   	my_tank->direction=1;
    my_tank->model=0;
    my_tank->color=1;
    my_tank->alive=1;
    my_tank->my=1;
	my_tank->CD=7;
    PrintTank (*my_tank) ;   //打印我的坦克
}


