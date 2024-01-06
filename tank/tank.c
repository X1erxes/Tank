#include "struct.h"
#include "whole.h"

#include <windows.h>
#include <stdio.h>

//position为坦克生成位置,-1为左位置,0为中间,1为右,2为我的坦克位置
void BuildAITank(int* position, Tank* AI_tank)   //执行一次该函数只建立一个坦克
{                                         //rand函数公式：0<=rand()%(a+1)<=a  0+m<=rand()%(n-m+1)+m<=n  
                                          //rand函数实现1到n：1<=rand()%(n)+1<=n
   	if(AIPositionCheak(*position))        //若此位置无障碍,可生成。position参数详见AIPositionCheak函数定义
	{
		AI_tank->x= 20 + 18*(*position);  //20 + 18 * position 对应三个生成位置的x假坐标
		AI_tank->y=2;
		if(AI_tank->revive==(level_info[level-1]).firm_tank_order)  //坦克出现(复活)次序==关卡信息(level_info)中firm tank的出现次序
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

void MoveAITank(Tank* AI_tank) //AI专用函数，该函数主要为AI加强
{
   	if(AI_tank->alive)         //如果坦克活着
	{
		if(AI_tank->stop!=0)   //坦克是否停止运动的判断，若stop参数不为0
		{
			AI_tank->stop--;   //则此坦克本回合停止运动
			return;
		}
		if( !(rand()%23) )     //22分之1的概率执行方向重置
		{
			AI_tank->direction = rand()%4+1;
			if( rand()%3 )     //在方向重置后有2分之1的概率停止走动3步的时间
			{
				AI_tank->stop=2;
				return;
			}
		}
		ClearTank (AI_tank->x , AI_tank->y);
		if(TankCheak ( *AI_tank , AI_tank->direction))   //如果前方无障碍
			switch ( AI_tank->direction )
			{
	       		case UP   : AI_tank->y--; break;  //上前进一格
        		case DOWN : AI_tank->y++; break;  //下前进一格
         		case LEFT : AI_tank->x--; break;  //左前进一格
        		case RIGHT: AI_tank->x++; break;  //右前进一格
			}
		else                     //前方有障碍
		{
			if(!(rand()%4))      //3分之1的概率乱转
			{
				AI_tank->direction=rand()%4+1;
				AI_tank->stop=2; //乱转之后停止走动3步的时间
				PrintTank(*AI_tank);
				return;          //∵continue会跳过下面的打印函数,∴这里先打印
			}
			else                 //另外3分之2的几率选择正确的方向
			{
				int j;
	    		for(j=1;j<=4;j++)
	        		if(TankCheak ( *AI_tank , j ))  //循环判断坦克四周有无障碍,此函数返值1为可通过
	    				break;
    			if(j==5)         //j==5说明此坦克四周都有障碍物，无法通行
				{
					PrintTank(*AI_tank);
	    			return;      //则跳过下面的while循环以防程序卡死
				}
    			while(TankCheak ( *AI_tank , AI_tank->direction) == 0)  //如果前方仍有障碍
	    			AI_tank->direction=(rand()%4+1);                    //则换个随机方向检测
			}
		}
		PrintTank(*AI_tank);     //打印AI坦克
	}
}

void MoveMyTank(int turn )   //玩家专用函数，turn为keyboard函数里因输入不同方向键而传入的不同的值
{
	ClearTank(my_tank.x , my_tank.y);        //map 数组中“我的坦克”参数清除工作已在此函数中完成
	my_tank.direction=turn;                  //将键盘输入的方向值传入我的坦克方向值
	if(TankCheak ( my_tank , my_tank.direction ))  //若此时我的坦克当前方向上无障碍
		switch (turn)
		{
			case UP   : my_tank.y--; break;  //上前进一格
			case DOWN : my_tank.y++; break;  //下前进一格
			case LEFT : my_tank.x--; break;  //左前进一格
			case RIGHT: my_tank.x++; break;  //右前进一格
	}                                        //若坦克当前方向上有障碍则跳过坐标变化直接打印该转向的坦克
	PrintTank (my_tank);
}

void ClearTank(int x,int y)   //清除坦克函数（人机共用）
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{                     //将坦克占用的地图上的九格去掉
	     	map[y+j-1][x+i-1]=0;
	        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
			GoToxy(2*x+2*j-2,y+i-1);
			printf("  ");
		}
}

void PrintTank(Tank tank)     //打印坦克（人机共用） 由于读取的Tank参数较多,故就不将参数一一传入了
{                             // tank.color参数对应不同的颜色,范围 1 ~ 6
	ColorChoose(tank.color);  //颜色选择函数   定义一个数组里装着字符指针(既装字符串)的数组指针(指向一维数组首地址的指针)
    char *(*tankF)[4] = tank_figure[tank.model];  //将二维数组首址赋初值给数组指针 model==0为我的坦克,4为电脑1坦克,8为电脑2,类推
	for(int i = 0; i < 3; i++)   
	{
        GoToxy((tank.x-1)*2 , tank.y-1+i);        //在坦克中心坐标的左边，上中下三行打印
        printf("%s", tankF[i][tank.direction-1]); //打印的是地址，地址既字符串
     	for(int j=0;j<3;j++)
			if(tank.my)       //若为我的坦克
	            map[tank.y+j-1][tank.x+i-1]=200;  //在map上把"坦克"九格填满代表敌我坦克的参数。敌方此值为100~103,我方为200
			else
		    	map[tank.y+j-1][tank.x+i-1]=100+tank.num;  //这样可以通过map值读取坦克编号,读取操作在BulletHit 函数
	}
}

int TankCheak(Tank tank,int direction)  //检测坦克前方障碍函数,参量为假坐标。返值1为可通过,返值0为阻挡(人机共用)
{
	switch(direction)                    //direction变量   1上，2下，3左，4右
	{
    	case UP:
			if (map[tank.y-2][tank.x]==0 && map[tank.y-2][tank.x-1]==0 && map[tank.y-2][tank.x+1]==0)
				return 1;
			else
				return 0;
        case DOWN:
			if (map[tank.y+2][tank.x]==0 && map[tank.y+2][tank.x-1]==0 && map[tank.y+2][tank.x+1]==0)
				return 1;
			else
				return 0;
		case LEFT:
			if (map[tank.y][tank.x-2]==0 && map[tank.y-1][tank.x-2]==0 && map[tank.y+1][tank.x-2]==0)
				return 1;
			else
				return 0;
		case RIGHT:
			if (map[tank.y][tank.x+2]==0 && map[tank.y-1][tank.x+2]==0 && map[tank.y+1][tank.x+2]==0)
				return 1;
			else
				return 0;
		default:
			printf("错误！！");
			Sleep(5000);
			return 0;
	}
}

int AIPositionCheak( int position )    //position为坦克生成位置2为我的坦克位置，其余为AI位，-1为左位，0为中间位置，1为右位
{
	int	x,y;
	if(position==2)                    //2为我的坦克位置，现在暂时用不到
		x=15,y=38;
	else
    	y=2 , x= 20 + 18 * position ;  //20 + 18 * position 对应三个生成位置的x假坐标
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if( map[y+j-1][x+i-1]!=0)  //如果遍历的九宫格里有障碍物
				return 0;              //则返回0，表示此生成位置有阻碍
    return 1;                          //否则生成1，表示此生成位置无阻碍
}