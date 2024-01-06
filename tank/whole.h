#ifndef WHOLE
#define WHOLE

#include "struct.h"
#include "define.h"


extern LevInfo level_info[];
extern Tank AI_tank[] , my_tank;
extern Bullet bullet[];  //考虑到地图上不太可能同时存在20颗子弹，所以数组元素设置20个


//全局变量
extern int map[][41];  //地图二维数组
extern int key_x;        // X键是否被“读入”的变量，也是子弹是否可以发射的变，
extern int bul_num;      //子弹编号
extern int position;     //位置计数,对应AI坦克生成位置,-1为左位置,0为中间,1为右,2为我的坦克位置
extern int speed;      //游戏速度,调整用
extern int level;      //游戏关卡数
extern int score;      //游戏分数
extern int remain_enemy; //剩余敌人(未出现的敌人)
extern int state;
extern int sel;
extern int sel2;
extern int player_cd;
extern int ai_cd;
extern int enemy_num;

extern char *tank_figure[][3][4];

char MenuText[][menu_length];

#endif WHOLE