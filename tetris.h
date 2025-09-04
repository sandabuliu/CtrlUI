#ifndef	__DIAMOND_H__
#define __DIAMOND_H__

#include"ctrl/ctrl.h"

#define MAX_SIZE    4

class Cube: public Ctrl {
  protected:
    int data[MAX_SIZE][MAX_SIZE];
    int length;

  public:
    Cube(int length, Ctrl *parent=NULL);
	void init();
	void toShow(int focus);
    void setShape(const int data[][MAX_SIZE]);
	bool canMove(int xDlt, int yDlt);
	int Up();
    int Down();
    int Left();
    int Right();
	int TimeEvent(int timestamp);
};

class Wall: public BackGround {
  public:
	Wall(int h, int w, bool fillSpace=false, Ctrl *parent=NULL): BackGround(h, w, fillSpace, parent){};
	bool inRange(int x, int y);
	bool addPix(int x, int y);
	int erase();
};

#endif
