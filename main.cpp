#include"emit.h"
#include<time.h>

int main()
{
    int x=30, y=0;
    BackGround bg(25, 20);
    bg.setPosition(x, y);

    Blocks blocks(&bg);
    blocks.unsetFocus();
    blocks.subscribe(EVENT_TYPE_TIME);
	
    Player player(&bg);
    player.setFocus();
    player.subscribe(EVENT_TYPE_KEY);

    Bullet bullet(&bg);
    bullet.unsetFocus();
    bullet.subscribe(EVENT_TYPE_TIME);

    Application app((Ctrl*)(&bg), 20);
    app.ShowCursor(0);
    app.Start();

    printf("Game Over!\n");
    Sleep(1000);
    putchar(0);
    return 0;
}
