#ifndef	__FLAPPY_H__
#define __FLAPPY_H__

#include"ctrl/ctrl.h"
#include<time.h>

class Obstacle: public BackGround {
  public:
	int rate, count, lastTimestamp;
    Obstacle(int rate, BackGround *parent=NULL);
	void move();
	int TimeEvent(int timestamp);
};

class Bird: public Ctrl {
  public:
	int lastTimestamp;
	Bird(BackGround *parent=NULL);
	void toShow(int focus);
	int TimeEvent(int timestamp);
	int Up();
};


#endif
