#  CtrlUI

### 说明
一个很久前开发的`windows`控制台控制UI，包含编辑框，选择框等控件，重新整理出来纪念一下


### Examples
---------------

##### 对话框

```c++
#include"ctrl/msgbox.h"

int main()
{
    MsgBox mb("对话框测试\n(左右光标移动)", 40-14/2, 4);
    Application app((Ctrl*)(&mb));
    app.start();
    return 0;
}
```

##### 编辑框

```c++
#include"ctrl/edit.h"

int main()
{
    Edit e("选择", 0, 0, -1, (Ctrl*)(&vlay));
    Application app((Ctrl*)(&e));
    app.start();
    return 0;
}
```

##### 组合使用

```c++
#include"ctrl/edit.h"
#include"ctrl/layout.h"

int main()
{
    HLayout hlay;
    VLayout vlay(&hlay);
    Edit e1("测试1", 2, 2, -1, (Ctrl*)(&vlay));
    Edit e2("测试2", 2, 4, 10, (Ctrl*)(&vlay));
    Edit e3("测试3", 20, 4, -1, (Ctrl*)(&hlay));

    Application app((Ctrl*)(&hlay));
    app.start();
    return 0;
}
```

##### 事件响应

```c++
#include"ctrl/radio.h"
#include"ctrl/msgbox.h"

class Menu: public Radio {
  public:
    Menu(const char *title, int x, int y, bool vertical=false, Ctrl *parent=NULL):
      Radio(title, x, y, vertical, parent){}

    virtual int Enter() {
	  std::string title="确定选择: ";
	  title+=this->text();
      MsgBox message(title.c_str(), 40-14/2, 4);
      int ret = message.execute();
      if(ret!=-1) {
        system("cls");
        this->setCursor(40-14/2, 4);
        if(ret==0) {
          printf("选择: %s", this->text());
        } else {
          printf("未选择！");
        }
        return -1;
      }
      return 1;
    }
};

int main()
{
    Menu menu("请选择:", 40-14/2, 4, 1);
    menu.addItem("abcde");
    menu.addItem("12345");
    menu.addItem("!@#$%");
    menu.addItem("+-*/=");
    Application app((Ctrl*)(&menu));
    app.start();
    return 0;
}
```

Copyright © 2017 [g_tongbin@foxmail.com](mailto:g_tongbin@foxmail.com)