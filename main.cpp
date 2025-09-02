#include"ctrl/msgbox.h"

int main()
{
    MsgBox mb("对话框测试\n(左右光标移动)", 40-14/2, 4);
    Application app((Ctrl*)(&mb));
    app.Start();
    return 0;
}