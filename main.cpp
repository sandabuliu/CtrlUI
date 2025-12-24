#include"flappy.h"

int main()
{
  int x=10, y=5;
  BackGround bg(15, 40);
  bg.setPosition(x, y);

  Obstacle obstacle(6, &bg);
  obstacle.unsetFocus();
  obstacle.subscribe(EVENT_TYPE_TIME);

  Bird bird(&bg);
  bird.setFocus();
  bird.subscribe(EVENT_TYPE_TIME | EVENT_TYPE_KEY);

  Application app((Ctrl*)(&bg), 20);
  app.ShowCursor(0);
  app.Start();
  return 0;
}