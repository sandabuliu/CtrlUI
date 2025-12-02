#ifndef	__EATBEAN_H__
#define __EATBEAN_H__

#include"ctrl/ctrl.h"
#include<time.h>

class EatbeanBg: public BackGround {
  public:
	EatbeanBg(int h, int w, bool fillSpace=false, Ctrl *parent=NULL);
	void toShow(int focus);
	bool isWin();
};

class Ball: public Ctrl {
  public:
    Ball(Ctrl *parent=NULL): Ctrl(parent){};
	void toShow(int focus);
	int Up();
    int Down();
    int Left();
    int Right();
};


#endif
