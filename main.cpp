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
