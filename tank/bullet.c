#include "define.h"
#include "struct.h"
#include "whole.h"

#include<windows.h>


void BuildAIBullet(Tank *tank)   //AI子弹发射(建立)含有对my_tank的读取
{
	if(tank->CD==ai_cd)
	{
		if(!(rand()%11))     //冷却结束后在随后的每个游戏周期中有10分之一的可能发射子弹
		{
			BuildBullet(*tank);
			tank->CD=0;
		}
	}
	else
		tank->CD++;
	if(tank->CD >= 10)       //AI强化部分，在冷却到达一定范围即可使用
	{
		if(tank->y==38 )     //如果坦克在底部(这个最优先)
		{
			if(tank->x < 20) //在老家左边
			{
				if(tank->direction==RIGHT)  //坦克方向朝左
				{
					BuildBullet(*tank);     //发射子弹
					tank->CD=0;
				}
			}
			else             //在老家右边
				if(tank->direction==LEFT)   //坦克方向朝右
				{
					BuildBullet(*tank);     //发射子弹
					tank->CD=0;
				}
		}
		else if(tank->x==my_tank.x+1 || tank->x==my_tank.x || tank->x==my_tank.x-1)  //AI坦克在纵向上"炮口"对准我的坦克
		{
			if( (tank->direction==DOWN && my_tank.y > tank->y) || (tank->direction==UP && my_tank.y < tank->y) )
			{                               //若是AI朝下并且我的坦克在AI坦克下方(数值大的在下面)或者AI朝上我的坦克在AI上方
				int big=my_tank.y , smal=tank->y , i; 
				if(my_tank.y < tank->y)
				{
					big=tank->y;
					smal=my_tank.y;
				}
				for(i=smal+2;i<=big-2;i++)  //判断AI炮口的直线上两坦克间有无障碍
					if(map[i][tank->x]!=0 || map[i][tank->x]!=5)      //若有障碍
						break;
				if(i==big-1)                //若i走到big-1说明无障碍
				{
					BuildBullet(*tank);     //则发射子弹
					tank->CD=0;
				}
			}
		}
		else if(tank->y==my_tank.y+1 || tank->y==my_tank.y || tank->y==my_tank.y-1) //AI坦克在横向上"炮口"对准我的坦克
		{
			if((tank->direction==RIGHT && my_tank.x > tank->x) || (tank->direction==LEFT && my_tank.x < tank->x))
			{                  //若是AI朝右并且我的坦克在AI坦克右方(数值大的在下面)或者AI朝左我的坦克在AI左方
				int big=my_tank.y , smal=tank->y , i;
				if(my_tank.x < tank->x)
				{
					big=tank->x;
					smal=my_tank.x;
				}
				for(i=smal+2;i<=big-2;i++)  //判断AI炮口的直线上两坦克间有无障碍
					if(map[tank->y][i]!=0 || map[tank->y][i]!=5)      //若有障碍
						break;
				if(i==big-1)   //若i走到big-1说明无障碍
				{
					BuildBullet(*tank);     //则发射子弹
					tank->CD=0;
				}
			}
		}
	}
}

void BuildBullet(Tank tank)  //子弹发射（建立）,传入结构体Tank,这里包含改变了全局变量结构体bullet
{                            //∵实现方式为顺序循环建立子弹，每次调用改变的bullet数组元素都不同
	switch(tank.direction)   //∴为了方便,不将bullet放入参数,bullet作为全局变量使用
	{
    	case UP    :
				bullet [bul_num].x = tank.x;
				bullet [bul_num].y = tank.y-2;
				bullet [bul_num].direction=1;
				break;
		case DOWN  :
				bullet [bul_num].x = tank.x;
				bullet [bul_num].y = tank.y+2;
				bullet [bul_num].direction=2;
				break;
		case LEFT  :
				bullet [bul_num].x = tank.x-2;
				bullet [bul_num].y = tank.y;
				bullet [bul_num].direction=3;
	    		break;
		case RIGHT :
				bullet [bul_num].x = tank.x+2;                   		          
				bullet [bul_num].y = tank.y; 
				bullet [bul_num].direction=4;
				break; 
	}     
	bullet [bul_num].exist = 1;    //子弹被建立,此值为1则此子弹存在
	bullet [bul_num].initial = 1;  //子弹处于初建立状态
	bullet [bul_num].my=tank.my;   //如果是我的坦克发射的子弹bullet.my=1，否则为0
	bul_num++;
	if(bul_num==BULLET_NUM)        //如果子弹编号增长到20号，那么重头开始编号
		bul_num=0;                 //考虑到地图上不可能同时存在20颗子弹，所以数组元素设置20个
}

void BulletFly(Bullet bullet[BULLET_NUM]) //子弹移动和打击
{                                         //含有全局变量Bullet的改变
	for(int i =0; i<BULLET_NUM;i++)
	{
		if(bullet [i].exist)              //如果子弹存在
		{   
			if(bullet [i].initial==0)     //如果子弹不是初建立的
			{                           
				if(map[bullet[i].y] [bullet[i].x]==0 || map[bullet[i].y] [bullet[i].x]==5)   //如果子弹坐标当前位置无障碍
					ClearBullet( bullet[i].x , bullet[i].y , BulletCheak(bullet[i].x , bullet[i].y ));     //抹除子弹图形
    			switch(bullet [i].direction)                                      //然后子弹坐标变化（子弹变到下一个坐标）
				{
        			case UP    :(bullet [i].y)--;break;
        			case DOWN  :(bullet [i].y)++;break;
        			case LEFT  :(bullet [i].x)--;break;
        			case RIGHT :(bullet [i].x)++;break;
				}
			}
			int collide = BulletCheak ( bullet [i].x , bullet [i].y );   //判断子弹当前位置情况,判断子弹是否碰撞,是否位于水面上。
			if( collide )                                                //如果检测到当前子弹坐标无障碍(无碰撞)（包括在地面上与在水面上）
				PrintBullet( bullet[i].x , bullet[i].y , collide);       //则打印子弹，若有碰撞则不打印
			else
				BulletHit( & bullet [i] );     //若有碰撞则执行子弹碰撞函数                  
			if(bullet [i].initial)             //若子弹初建立，则把初建立标记去除
				bullet [i].initial = 0;
			for(int j=0; j< BULLET_NUM ; j++)  //子弹间的碰撞判断,若是我方子弹和敌方子弹碰撞则都删除,若为两敌方子弹则无视
				if(bullet [j].exist && j!=i && (bullet[i].my || bullet[j].my) && bullet[i].x==bullet[j].x && bullet[i].y==bullet[j].y)
				{                              //同样的两颗我方子弹不可能产生碰撞
					bullet [j].exist=0;
					bullet [i].exist=0;
					ClearBullet( bullet[j].x , bullet[j].y , BulletCheak(bullet[j].x , bullet[j].y ));  //抹除j子弹图形,子弹i图形已被抹除
					break;
				}
		}
	}
}

void BulletHit(Bullet* bullet)  //含有Tank全局变量的修改,子弹间的碰撞不在本函数,子弹间碰撞已在BulletShoot中检测并处理
{                               //∵每次打中的坦克都不一样，不可能把所有坦克放在参数表中
	int x=bullet->x;            //∴这里的Tank使用全局变量
	int y=bullet->y;            //这里传入的值是子弹坐标,这两个值不需要改变
	int i;
	if(map[y][x]==1 || map[y][x]==2)  //子弹碰到砖块
	{
		if(bullet->direction==UP || bullet->direction==DOWN)   //如果子弹是纵向的
			for(i = -1 ; i<=1 ; i++)
            	if(map[y][x+i]==1 || map[y][x+i]==2)  //如果子弹打中砖块两旁为砖块,则删除砖,若不是(一旁为坦克或其他地形)则忽略
				{
		    		map[y][x+i]=0;    //砖块碎
                 	GoToxy(2*x+2*i,y);
		    		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); //背景黑色
                 	printf("  ");
				}
		if(bullet->direction==LEFT || bullet->direction==RIGHT)     //若子弹是横向的  (与子弹纵向实现同理)
			for(i = -1 ; i<=1 ; i++)
				if(map[y+i][x]==1 || map[y+i][x]==2)
				{
		    		map[y+i][x]=0;
                 	GoToxy(2*x,y+i);
	    			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); //背景黑色
                 	printf("  "); 
				}
		bullet->exist=0;           //这颗子弹已经不存在了
	}
	else if(map[y][x]==4 || map[y][x]==6 )  //子弹碰到边框或者不可摧毁方块
        bullet->exist=0;
	else if(bullet->my && map[y][x]>=100 && map[y][x]<104 )  //若我的子弹碰到了敌方坦克
	{
		int num = map[y][x]%100;   //map[y][x]%100 等同于 tank.num ，可通过map值读取该坦克信息
		if(AI_tank[num].model==3 && AI_tank[num].color==2)   //若为firm tank,且color==2。该坦克为绿色,表明没有受到伤害
				AI_tank[num].color=3;                        //则变成黄色，color=3为黄色
		else if (AI_tank[num].model==3 && AI_tank[num].color==3)
				AI_tank[num].color=4;                        //4为红色
		else                       //其他类型的坦克或者firm tank为红色的情况
		{
			AI_tank[num].alive=0;
			ClearTank(AI_tank[num].x , AI_tank[num].y);      //清除该坦克
		}
		bullet->exist=0;
		score += (100 * (11-speed) );
		GoToxy(102,5);             //在副屏幕上打印出分数
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("%d ",score);
	}
	else if(map[y][x]==200 && bullet->my==0 )   //若敌方子弹击中我的坦克
	{
		my_tank.alive=0;
		ClearTank(my_tank.x , my_tank.y);
		bullet->exist=0;
		my_tank.revive++;      //我的坦克复活次数+1(∵我的坦克复活次数与生命值有关∴放在这里自减)
		score-=100*(11-speed); //分数减少
		GoToxy(102,5);         //在副屏幕上打印出分数
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("%d   ",score);
		GoToxy(102,7);         //在副屏幕打印出我的剩余生命值
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
		printf("%d   ", MAX_LIFE-my_tank.revive);
	}
	else if(map[y][x]==9)      //子弹碰到家(无论是谁的子弹)
	{
		bullet->exist=0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
		GoToxy(38,37);	 printf("      ");
		GoToxy(38,38);	 printf("◢◣  ");
		GoToxy(38,39);	 printf("███");
		GameOver(1);           //游戏结束,传入1代表老家被毁
	}
}

void PrintBullet (int x,int y,int T)   //当前坐标BulletCheak 的值做参量 T
{
	if(T==1)          //  T==1 表示子弹当前坐标在陆地上
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	else if(T==2)     //  T==2 表示子弹当前坐标在水面上
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
    GoToxy(2*x,y);
    printf("☉");
}

void ClearBullet(int x,int y,int T)   //当前坐标BulletCheak 的值做参量 T
{
	GoToxy(2*x,y);
	if(T==2)        //  T==2 表示子弹当前坐标在水面上
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_GREEN);
		printf("～");
	}
	else if(T==1)   //  T==1 表示子弹当前坐标在陆地上
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
		printf("  ");
	}
}

int BulletCheak (int x,int y)  //判断子弹当前位置情况,判断子弹是否碰撞,是否位于水面上。
{                              //有障碍返回0,无障碍且子弹在地面返回1，子弹在水面上返回2
	if(map[y][x]==0)
		return 1;
	else if(map[y][x]==5)
		return 2;
	else
		return 0;
}


