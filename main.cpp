#include"tetris.h"

int main()
{
    int x=40-14/2, y=4;
    Wall bg(20, 20, true);
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