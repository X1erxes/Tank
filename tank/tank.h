#ifndef TANK
#define TANK
#include "struct.h"
#include "header.h"

void BuildAITank (int* position, Tank* AI_tank); //建立AI坦克
void BuildMyTank (Tank *my_tank);                //建立我的坦克
void MoveAITank  (Tank *AI_tank);                //AI坦克移动
void MoveMyTank  (int turn);                     //我的坦克移动，只通过keyboard函数调用，既键盘控制
void ClearTank   (int x,int y);                  //清除坦克（人机共用）
void PrintTank   (Tank tank);                    //打印坦克（人机共用）
int TankCheak   (Tank tank,int direction);      //检测坦克dirtection方向的障碍物,返值1阻碍,0 畅通
int  AIPositionCheak (int position);           //检测AI坦克建立位置是否有障碍物AIPositionCheak
#endif