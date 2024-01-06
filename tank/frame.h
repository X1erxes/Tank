void Frame ();               //打印游戏主体框架
void SideScreen ();          //副屏幕打印
void ColorChoose(int color); //颜色选择函数
void ClearMainScreen();      //主屏幕清屏函数∵system("cls")后打印框架有一定几率造成框架上移一行的错误∴单独编写清屏函数
void HideCursor();           //隐藏光标
void GoToxy(int x,int y);    //光标移动
void displaymenu(int hilight);