#include "pinball.h"

Scene::Scene(int h, int w, bool fillSpace, Ctrl *parent): BackGround(h, w, fillSpace, parent) {
  for(int i=2; i<8; i++) {
	for(int j=2; j<this->width-2; j++) {
	  this->data[i][j] = 1;
	}
  }
}

bool Scene::inRange(int x, int y) {
  int rx=x-this->pos.X;
  int ry=y-this->pos.Y;
  if(rx < 0 || rx > this->width || ry > this->height) {
    return false;
  }

  for(int i=0; i<this->height; i++) {
	for(int j=0; j<this->width; j++) {
	  if(data[i][j] && rx==j && ry==i && ry!=0) {
	    return false;
	  }
	}
  }
  return true;
}

void Scene::erasePix(int x, int y) {
  if(!this->data[y][x]) {
	return;
  }
  this->data[y][x] = 0;
  short originX, originY;
  this->getCursor(originX, originY);
  this->setCursor(this->pos.X+x, this->pos.Y+y);
  printf(" ");
  this->setCursor(originX, originY);
}

Pad::Pad(int length, Ctrl *parent): Ctrl(parent) {
  this->length = length;
}

void Pad::toShow(int focus) {
  for(int i=0;i<this->length;i++) {
    printf("*");
  }
}

int Pad::Left() {
  if(pos.X-1 <= this->parent->pos.X) {
	return 0;
  }
  lastTime = clock();
  lastX = this->pos.X;

  short x, y;
  this->getCursor(x, y);
  this->setCursor(pos.X+this->length-1, pos.Y);
  printf(" ");
  this->setCursor(x, y);
  this->pos.X--;
  return 1;
}

int Pad::Right() {
  Scene *bg = (Scene*)this->parent;
  if(pos.X+length >= bg->pos.X+bg->width-1) {
    return 0;
  }
  lastTime = clock();
  lastX = this->pos.X;

  short x, y;
  this->getCursor(x, y);
  this->setCursor(pos.X, pos.Y);
  printf(" ");
  this->setCursor(x, y);
  this->pos.X++;
  return 1;
}

int Pad::TimeEvent(int timestamp) {
  if(timestamp - lastTime >= 400) {
	this->direct = 0; 
  } else {
	this->direct = lastX-this->pos.X;
  }
  return 0;
}

void PinBall::toShow(int focus) {
  printf("*");
}

int PinBall::TimeEvent(int timestamp) {
  if(xSpeed == 0 && ySpeed == 0) {
    ySpeed = 1;
  }

  short originX, originY;
  this->getCursor(originX, originY);
  this->setCursor(this->pos.X, this->pos.Y);
  printf(" ");
  this->setCursor(originX, originY);

  this->pos.X += xSpeed;
  this->pos.Y += ySpeed;

  if(this->EraseDetect() < 0) {
	return -1;
  }
  return 1;
}

int PinBall::EraseDetect() {
  int ret = this->CollisionDetect();
  if(ret) {
    return ret;
  }

  Scene *bg = (Scene*)this->parent;
  int nextX = this->pos.X+xSpeed-bg->pos.X;
  int nextY = this->pos.Y+ySpeed-bg->pos.Y;
  int currentX = this->pos.X-bg->pos.X;
  int currentY = this->pos.Y-bg->pos.Y;

  if(bg->data[nextY][currentX]) {
	bg->erasePix(currentX, nextY);
	ySpeed = -ySpeed;
    return 1;
  }

  if(bg->data[currentY][nextX]) {
	bg->erasePix(nextX, currentY);
	xSpeed = -xSpeed;
    return 1;
  }

  if(bg->data[nextY][nextX]) {
	bg->erasePix(nextX, nextY);
	xSpeed = -xSpeed;
	ySpeed = -ySpeed;
    return 1;
  }
  return 0;
}

int PinBall::CollisionDetect() {
  Scene *bg = (Scene*)this->parent;
  if(this->pos.X >= bg->pos.X+bg->width-1) {
	return -1;
  }
  if(this->pos.X <= bg->pos.X) {
	return -1;
  }
  if(this->pos.Y >= bg->pos.Y+bg->height-2) {
	return -1;
  }
  if(this->pos.Y <= bg->pos.Y) {
	return -1;
  }

  int nextX = this->pos.X+xSpeed;
  int nextY = this->pos.Y+ySpeed;

  int yPad = this->pad->pos.Y;
  int xPad = this->pad->pos.X;
  if(nextY == yPad && nextX >= xPad && nextX < xPad+this->pad->length) {
	if(this->pad->direct > 0) {
	  xSpeed = xSpeed-1<-1?-1:xSpeed-1;
	} else if(this->pad->direct < 0) {
	  xSpeed = xSpeed+1>1?1:xSpeed+1;
	}
	ySpeed = -ySpeed;
    return 1;
  }

  int ret = 0;
  if(nextX == bg->pos.X || nextX == bg->pos.X+bg->width-1) {
	xSpeed = -xSpeed;
	ret = 1;
  }
  if(nextY == bg->pos.Y || nextY == bg->pos.Y+bg->height-1) {
	ySpeed = -ySpeed;
	ret = 1;
  }
  return ret;
}
