#ifndef	__SNAKE_H__
#define __SNAKE_H__

#include"ctrl/ctrl.h"

class Snake: public Ctrl {
  public:
    Snake(int x1, int y1, int length, Ctrl *parent=NULL);
	std::vector<COORD> pixel;
	COORD food;
	int direct; // 1-4 иообвСср
	void toShow(int focus);
    int Left();
    int Right();
    int Up();
    int Down();
    void eat();
	bool canEat();
    int TimeEvent(int timestamp);
	bool verify();
	void makeFood();
};

#endif
