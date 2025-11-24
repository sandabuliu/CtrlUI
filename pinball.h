#ifndef	__PINBALL_H__
#define __PINBALL_H__

#include"ctrl/ctrl.h"
#include<time.h>

class Scene: public BackGround {
  public:
	Scene(int h, int w, bool fillSpace=false, Ctrl *parent=NULL);
	bool inRange(int x, int y);
	void erasePix(int x, int y);
};

class Pad: public Ctrl {
  public:
	int length;
    Pad(int length, Ctrl *parent=NULL);
	void toShow(int focus);
    int Left();
    int Right();

	int lastX, lastTime, direct;
	int TimeEvent(int timestamp);
};


class PinBall: public Ctrl {
  protected:
	Pad *pad;
	int xSpeed, ySpeed;

  public:
	PinBall(Pad *pad, Ctrl *parent=NULL): Ctrl(parent) {
      this->pad=pad;
      xSpeed=ySpeed=0;
	}
    void toShow(int focus);
	int TimeEvent(int timestamp);
	int CollisionDetect();
	int EraseDetect();
};

#endif
