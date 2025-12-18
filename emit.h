#ifndef	__EMIT_H__
#define __EMIT_H__

#include"ctrl/ctrl.h"
#include<time.h>

class Blocks: public BackGround {
  public:
	int lastTimestamp;
    Blocks(BackGround *parent=NULL);

	void addLine();
    void erase();

	int TimeEvent(int timestamp);
};

class Player: public Ctrl {
  public:
	int length;
	Player(BackGround *parent=NULL);

	void toShow(int focus);
	int Left();
	int Right();
	int Up();
};

class Bullet: public Ctrl {
  public:
	Bullet(BackGround *parent=NULL);

	std::vector<COORD> pixel;
	void add(short x, short y);
    bool change();

	void toShow(int focus);
	int TimeEvent(int timestamp);
};


#endif
