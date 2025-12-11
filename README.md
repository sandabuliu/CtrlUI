#  CtrlUI

### 说明
一个很久前开发的`windows`控制台控制UI，包含编辑框，选择框等控件，重新整理出来纪念一下


### Examples
---------------

##### 五子棋

```c++
#include"renju.h"
#include<time.h>

int main()
{
	int x=20, y=0;
    ChessBoard cb(9);
    cb.setPosition(x, y);
    cb.subscribe(EVENT_TYPE_KEY);

    Application app((Ctrl*)(&cb), 300);
    app.ShowCursor(0);
    app.Start();

    printf("WINNER IS [%c]!!!\n", cb.shape[cb.current]);
    Sleep(1000);
    putchar(0);
    return 0;
}

```

##### 吃豆豆

```c++
#include"eatbean.h"
#include<time.h>

int main()
{
	int x=10, y=5, height=20, width=60;
    EatbeanBg bg(height, width, true);
    bg.setPosition(x, y);

    Ball ball((Ctrl*)(&bg));
    ball.setPosition(x+1, y+1);
    ball.subscribe(EVENT_TYPE_KEY);

    Application app((Ctrl*)(&bg), 300);
    app.ShowCursor(0);
    app.Start();

    printf("Game Over!\n");
    Sleep(1000);
    putchar(0);
    return 0;
}

```

##### 弹球

```c++
#include"pinball.h"

int main()
{
    int x=10, y=5, height=20, width=60;
    Scene bg(height, width, false);
    bg.setPosition(x, y);

    Pad pad(6, (Ctrl*)(&bg));
    pad.setPosition(x+width/2-pad.length/2, y+height-2);
    pad.subscribe(EVENT_TYPE_KEY | EVENT_TYPE_TIME);

    PinBall ball(&pad, (Ctrl*)(&bg));
    ball.setPosition(x+width/2, 15);
    ball.subscribe(EVENT_TYPE_TIME);

    Application app((Ctrl*)(&bg), 300);
    app.ShowCursor(0);
    app.Start();

    printf("Game Over!\n");
    Sleep(1000);
    putchar(0);
    return 0;
}

```

##### 贪吃蛇

```c++
#include"snake.h"

int main()
{
    int x=10, y=5;
    BackGround bg(20, 60);
    bg.setPosition(x, y);

    Snake snake(11, 8, 3, (Ctrl*)(&bg));
    snake.subscribe(EVENT_TYPE_TIME | EVENT_TYPE_KEY);

    Application app((Ctrl*)(&bg), 200);
    app.ShowCursor(0);
    app.Start();

    printf("Game Over!\n");
    Sleep(1000);
    putchar(0);
    return 0;
}

```

##### 俄罗斯方块

```c++
#include"tetris.h"

int main()
{
    int x=40-14/2, y=4;
    Wall bg(20, 20);
    bg.setPosition(x, y);

    Cube cb(MAX_SIZE, (Ctrl*)(&bg));
    cb.init();
	cb.subscribe(EVENT_TYPE_TIME | EVENT_TYPE_KEY);

    Application app((Ctrl*)(&bg), 200);
    app.ShowCursor(0);
    app.Start();

    printf("Game Over!\n");
    Sleep(1000);
    putchar(0);
    return 0;
}
```

##### 对话框

```c++
#include"ctrl/msgbox.h"

int main()
{
    MsgBox mb("对话框测试\n(左右光标移动)", 40-14/2, 4);
    Application app((Ctrl*)(&mb));
    app.Start();
    return 0;
}
```

##### 编辑框

```c++
#include"ctrl/edit.h"

int main()
{
    Edit e("选择", 0, 0, -1);
    Application app((Ctrl*)(&e));
    app.Start();
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
    app.Start();
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
    app.Start();
    return 0;
}
```

Copyright © 2017 [g_tongbin@foxmail.com](mailto:g_tongbin@foxmail.com)


