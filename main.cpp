#include"ctrl/msgbox.h"

int main()
{
    MsgBox mb("�Ի������\n(���ҹ���ƶ�)", 40-14/2, 4);
    Application app((Ctrl*)(&mb));
    app.Start();
    return 0;
}