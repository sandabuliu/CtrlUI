#ifndef	__DIAMOND_H__
#define __DIAMOND_H__

#include"ctrl/ctrl.h"

#define MAX_SIZE    4
#define MAX_SCREEN  100

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

class BackGround: public Ctrl {
  protected:
    int height;
    int width;
	int data[MAX_SCREEN][MAX_SCREEN];
	Cube *cb;

  public:
    BackGround(int h, int w, Ctrl *parent=NULL);
	void toShow(int focus);
	bool inRange(int x, int y);
	bool addPix(int x, int y);
	int erase();
};

#endif
