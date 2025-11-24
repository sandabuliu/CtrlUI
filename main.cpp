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
