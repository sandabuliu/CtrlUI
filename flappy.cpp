#include "flappy.h"

Obstacle::Obstacle(int rate, BackGround *p): BackGround(p->height-2, p->width-2, true, p) {
  this->setPosition(p->pos.X+p->width-1-this->width, p->pos.Y+1);
  for(int i=0; i<MAX_SCREEN; i++) {
	for(int j=0; j<MAX_SCREEN; j++) {
	  this->data[i][j] = 0;
	}
  }

  this->rate=rate;
  this->count=0;
  for(i=0; i<this->width*3/4; i++) {
    this->move();
  }
  this->name="obstacle";
  srand((unsigned)time(NULL));
}

void Obstacle::move() {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width-1; j++) {
	  this->data[i][j] = this->data[i][j+1];
	}
  }

  int l1=rand()%(this->height*1/2);
  int l2=this->height*1/4;
  int length=(this->count % this->rate ? 0 : (l1+l2));
  int direct=rand() % 2;
  for(i=0; i<this->height; i++) {
	int value=i<length?1:0;
	int line=direct?i:this->height-1-i;
	this->data[line][this->width-1]=value;
  } 
  this->count++;
}

int Obstacle::TimeEvent(int timestamp) {
  if(timestamp-this->lastTimestamp < 500) {
	return 0;
  }
  this->move();
  this->lastTimestamp=timestamp;
  return 1;
}

Bird::Bird(BackGround *p): Ctrl(p) {
  this->setPosition(p->pos.X+6, p->pos.Y+p->height/2);
  this->name="bird";
}

void Bird::toShow(int focus) {
  this->setCursor(this->pos.X, this->pos.Y);
  printf("+");
  this->setCursor(this->pos.X+1, this->pos.Y);
  printf(">");
}

int Bird::TimeEvent(int timestamp) {
  if(timestamp-this->lastTimestamp < 200) {
	return 0;
  }

  BackGround *bg = (BackGround*)this->parent;
  if(this->pos.Y+1 >= bg->pos.Y+bg->height-1) {
	return -1;
  }

  Obstacle *obs=(Obstacle*)this->parent->getChild("obstacle");
  if(obs==NULL) {
	return -1;
  }
  int obsX=this->pos.X-obs->pos.X;
  int obsY=this->pos.Y-obs->pos.Y;
  if(obs->data[obsY][obsX] || obs->data[obsY][obsX+1]) {
	return -1;
  }

  this->lastTimestamp=timestamp;
  this->pos.Y++;
  return 1;
}

int Bird::Up() {
  if(this->pos.Y-1 <= this->parent->pos.Y) {
	return 0;
  }
  this->lastTimestamp=clock();
  this->pos.Y--;
  return 1;
}