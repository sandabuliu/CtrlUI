#include "snake.h"
#include<time.h>

Wall::Wall(int h, int w, Ctrl *parent): Ctrl(parent) {
  this->height = h;
  this->width = w;
  for(int i=0; i<MAX_SCREEN; i++) {
	for(int j=0; j<MAX_SCREEN; j++) {
	  if(i==0 || j==0 || i==this->height-1 || j == this->width-1) {data[i][j] = 1;}
      else {this->data[i][j] = 0;}
	}
  }
  srand(time(0));
}

void Wall::toShow(int focus) {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width; j++) {
	  this->setCursor(this->pos.X+j, this->pos.Y+i);
      if(this->data[i][j]) {	
        printf("*");
	  }
	}
  }
}

Snake::Snake(int x1, int y1, int length, Ctrl *parent): Ctrl(parent) {
  this->direct = 4;
  for(int i=0;i<length;i++) {
    COORD p={x1+i,y1};
    this->pixel.push_back(p);
  }
  this->makeFood();
}

void Snake::makeFood() {
  Wall *bg = (Wall*)this->parent;
  COORD pos1 = {bg->pos.X, bg->pos.Y};
  COORD pos2 = {bg->pos.X+bg->width, bg->pos.Y+bg->height};

  bool finish=false;
  while(!finish) {
	finish = true;
    this->food.X = rand() % ((pos2.X-1) - (pos1.X+1) + 1) + pos1.X+1;
    this->food.Y = rand() % ((pos2.Y-1) - (pos1.Y+1) + 1) + pos1.Y+1;
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

bool Snake::verify() {
  Wall *bg = (Wall*)this->parent;
  COORD pos1 = {bg->pos.X, bg->pos.Y};
  COORD pos2 = {bg->pos.X+bg->width, bg->pos.Y+bg->height};

  COORD cur = this->pixel.back();
  if(cur.X >= pos2.X || cur.X <= pos1.X) {
    return false;
  }
  if(cur.Y >= pos2.Y || cur.Y <= pos1.Y) {
    return false;
  }
  return true;
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

void Snake::toShow(int focus) {
  std::vector<COORD>::iterator iter;
  for(iter=this->pixel.begin();iter!=this->pixel.end();iter++) {
    setCursor((*iter).X, (*iter).Y);
    printf("*");
  }
}

int Snake::Up() {
  if(this->direct == 2) {
    return 0;
  }
  if(this->direct == 1) {
	return this->TimeEvent(clock());
  }
  this->direct = 1;
  return 0;
}

int Snake::Down() {
  if(this->direct == 1) {
    return 0;
  }
  if(this->direct == 2) {
	return this->TimeEvent(clock());
  }
  this->direct = 2;
  return 0;
}

int Snake::Left() {
  if(this->direct == 4) {
    return 0;
  }
  if(this->direct == 3) {
	return this->TimeEvent(clock());
  }
  this->direct = 3;
  return 0;
}

int Snake::Right() {
  if(this->direct == 3) {
    return 0;
  }
  if(this->direct == 4) {
	return this->TimeEvent(clock());
  }
  this->direct = 4;
  return 0;
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