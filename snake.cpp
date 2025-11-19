#include "snake.h"
#include<time.h>

Snake::Snake(int x1, int y1, int length, Ctrl *parent): Ctrl(parent) {
  this->direct = 4;
  for(int i=0;i<length;i++) {
    COORD p={x1+i,y1};
    this->pixel.push_back(p);
  }
  this->makeFood();
}

void Snake::toShow(int focus) {
  std::vector<COORD>::iterator iter;
  for(iter=this->pixel.begin();iter!=this->pixel.end();iter++) {
    setCursor((*iter).X, (*iter).Y);
    printf("*");
  }
}

bool Snake::verify() {
  BackGround *bg = (BackGround*)this->parent;
  COORD pos1 = {bg->pos.X, bg->pos.Y};
  COORD pos2 = {bg->pos.X+bg->width-1, bg->pos.Y+bg->height-1};

  COORD cur = this->pixel.back();
  if(cur.X >= pos2.X || cur.X <= pos1.X) {
    return false;
  }
  if(cur.Y >= pos2.Y || cur.Y <= pos1.Y) {
    return false;
  }
  return true;
}

int Snake::Up() {
  if(this->direct == 2) {
    return 1;
  }
  if(this->direct == 1) {
	return this->TimeEvent(clock());
  }
  this->direct = 1;
  return 1;
}

int Snake::Down() {
  if(this->direct == 1) {
    return 1;
  }
  if(this->direct == 2) {
	return this->TimeEvent(clock());
  }
  this->direct = 2;
  return 1;
}

int Snake::Left() {
  if(this->direct == 4) {
    return 1;
  }
  if(this->direct == 3) {
	return this->TimeEvent(clock());
  }
  this->direct = 3;
  return 1;
}

int Snake::Right() {
  if(this->direct == 3) {
    return 1;
  }
  if(this->direct == 4) {
	return this->TimeEvent(clock());
  }
  this->direct = 4;
  return 1;
}

void Snake::makeFood() {
  BackGround *bg = (BackGround*)this->parent;
  COORD pos1 = {bg->pos.X, bg->pos.Y};
  COORD pos2 = {bg->pos.X+bg->width-1, bg->pos.Y+bg->height-1};

  bool finish=false;
  while(!finish) {
	finish = true;
    this->food.X = rand() % (pos2.X-pos1.X-1)+pos1.X+1;
    this->food.Y = rand() % (pos2.Y-pos1.Y-1)+pos1.Y+1;
	std::vector<COORD>::iterator iter;
    for(iter=this->pixel.begin();iter!=this->pixel.end();iter++) {
	  if(food.X == (*iter).X && food.Y == (*iter).Y) {
	    finish = false;
	  } 
	}
  }

  setCursor(this->food.X, this->food.Y);
  printf("*");
}

bool Snake::canEat() {
  COORD cur = this->pixel.back();
  if(cur.X == this->food.X && cur.Y == this->food.Y) {
    return true;
  }
  return false;
}

void Snake::eat() {
  COORD *begin = this->pixel.begin();
  this->pixel.insert(begin, *begin);
}

int Snake::TimeEvent(int timestamp) {
  COORD *begin = this->pixel.begin();
  this->setCursor(begin->X, begin->Y);
  printf(" ");
  this->pixel.erase(begin);
  COORD item = this->pixel.back();
  COORD p = {item.X, item.Y};

  if(this->direct == 1) {
    p.Y = item.Y-1;
  } else if(this->direct == 2) {
    p.Y = item.Y+1;
  } else if(this->direct == 3) {
    p.X = item.X-1;
  } else {
    p.X = item.X+1;
  }
  this->pixel.push_back(p);

  if(!this->verify()) {
	return -1;
  }
  if(this->canEat()) {
	this->eat();
	this->makeFood();
  }
  return 1;
}
