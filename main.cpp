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
