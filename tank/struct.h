#include "define.h"
#ifndef STRUCT
#define STRUCT


typedef struct      //坦克结构体
{
	int x,y;        //坦克中心坐标
	int direction;  //坦克方向
	int color;      //颜色参方向数，1到6分别代表不同颜色，具体在PrintTank函数定义有说明
	int model;      //坦克图案模型，值为1,2,3，分别代表不同的坦克图案,0为我的坦克图案，AI不能使用
	int stop;       //只能是AI坦克使用的参数，非0代表坦克停止走动,0为可以走动
	int revive;     //坦克复活次数
	int num;        //AI坦克编号（固定值，为常量，初始化函数中定下）0~3
	int CD;         //发射子弹冷却计时
	int my;        //是否敌方坦克参数，我的坦克此参数为1,为常量
	int alive;     //存活为1，不存活为0
}  Tank;


typedef struct             //这里的出现次序指的是一个AI_tank变量中的次序，游戏共有四个AI_tank变量
{                          //∵设定每个AI_tank每种特殊坦克只出现一次 ∴fast_tank & firm_tank 最多出现次数不超过1
	int fast_tank_order;   //fast_tank出现的次序(在第fast_tank_order次复活出现,从第0次开始)，且每个AI_tank只出现一次
	int firm_tank_order;   //firm_tank出现的次序，同上
} LevInfo;


typedef struct      //子弹结构体
{
	int x,y;        //子弹坐标,假坐标
	int direction;  //子弹方向变量
	int exist;     //子弹存在与否的变量,1为存在，0不存在
	int initial;   //子弹是否处于建立初状态的值，1为处于建立初状态，0为处于非建立初状态
	int my;        //区分AI子弹与玩家子弹的标记,0为AI子弹，1为玩家（我的）子弹
} Bullet;

#endif