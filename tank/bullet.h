#ifndef BULLET
#define BULLET
#include "struct.h"
#include "define.h"

void BuildAIBullet(Tank *tank);                //AI坦克发射子弹（含有对my_tank的读取,只读取了my_tank坐标）
void BuildBullet  (Tank tank);                 //子弹发射（建立）（人机共用）(含全局变量bullet的修改)我的坦克发射子弹直接调用该函数,AI通过AIshoot间接调用
void BulletFly    (Bullet bullet[BULLET_NUM]); //子弹移动和打击（人机共用）,
void BulletHit    (Bullet* bullet);            //子弹碰撞（人机共用）(含Tank全局变量的修改)，只通过BulletFly调用，子弹间的碰撞不在本函数,子弹间碰撞已在BulletShoot中检测并处理
void PrintBullet  (int x,int y,int T);         //打印子弹（人机共用）
void ClearBullet  (int x,int y,int T);         //清除子弹（人机共用）
int  BulletCheak  (int x,int y);               //判断子弹前方情况（人机共用）
#endif