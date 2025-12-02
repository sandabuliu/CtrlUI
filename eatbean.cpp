#include "eatbean.h"

EatbeanBg::EatbeanBg(int h, int w, bool fillSpace, Ctrl *parent): BackGround(h, w, fillSpace, parent) {
  srand((unsigned)time(NULL));
  for(int i=1; i<this->height-1; i++) {
	for(int j=1; j<this->width-1; j++) {
	  int num = rand() % 100;
	  this->data[i][j] = num>80?1:0;
      if(this->data[i][j] == 0) {
        int num = rand() % 100;
	    this->data[i][j] = num>80?2:0;
	  }
	}
  }
  this->data[1][1] = 0;
}

void EatbeanBg::toShow(int focus) {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width; j++) {
	  this->setCursor(this->pos.X+j, this->pos.Y+i);
      if(this->data[i][j] == 1) {	
        printf("*");
	  } else if(this->data[i][j] == 2) {
		printf(".");
	  } else if(this->fillSpace) {
		printf(" ");
	  }
	}
  }
}

bool EatbeanBg::isWin() {
  for(int i=1; i<this->height-1; i++) {
	for(int j=1; j<this->width-1; j++) {
	  if(this->data[i][j] == 2) {
		return false;
	  }
	}
  }
  return true;
}

void Ball::toShow(int focus) {
  printf("O");
}

int Ball::Up() {
  EatbeanBg *bg = (EatbeanBg*)this->parent;
  int x=this->pos.X-bg->pos.X;
  int y=this->pos.Y-bg->pos.Y-1;
  if(bg->data[y][x] == 1) {
	return 0;
  } else if(bg->data[y][x] == 2) {
    bg->data[y][x] = 0;
  }
  this->pos.Y--;
  if(bg->isWin()) {
	return -1;
  }
  return 1;
}

int Ball::Down() {
  EatbeanBg *bg = (EatbeanBg*)this->parent;
  int x=this->pos.X-bg->pos.X;
  int y=this->pos.Y-bg->pos.Y+1;
  if(bg->data[y][x] == 1) {
	return 0;
  } else if(bg->data[y][x] == 2) {
    bg->data[y][x] = 0;
  }
  this->pos.Y++;
  if(bg->isWin()) {
	return -1;
  }
  return 1;
}

int Ball::Left() {
  EatbeanBg *bg = (EatbeanBg*)this->parent;
  int x=this->pos.X-bg->pos.X-1;
  int y=this->pos.Y-bg->pos.Y;
  if(bg->data[y][x] == 1) {
	return 0;
  } else if(bg->data[y][x] == 2) {
    bg->data[y][x] = 0;
  }
  this->pos.X--;
  if(bg->isWin()) {
	return -1;
  }
  return 1;
}

int Ball::Right() {
  EatbeanBg *bg = (EatbeanBg*)this->parent;
  int x=this->pos.X-bg->pos.X+1;
  int y=this->pos.Y-bg->pos.Y;
  if(bg->data[y][x] == 1) {
	return 0;
  } else if(bg->data[y][x] == 2) {
    bg->data[y][x] = 0;
  }
  this->pos.X++;
  if(bg->isWin()) {
	return -1;
  }
  return 1;
}
