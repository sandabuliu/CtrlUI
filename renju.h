#ifndef	__RENJU_H__
#define __RENJU_H__

#include"ctrl/ctrl.h"

class ChessBoard: public Ctrl {
  public:
	char data[MAX_SCREEN][MAX_SCREEN];
	int height, width;
	int x, y, num;
	char shape[2];
	int current;
	ChessBoard(int num, Ctrl *parent=NULL);
	void toShow(int focus);

	int Up();
    int Down();
    int Left();
    int Right();
	int Enter();

	bool isWin(int x, int y);
};

#endif
