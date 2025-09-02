#include "tetris.h"
#include<time.h>

struct SHAPE {
  int length;
  int shape[MAX_SIZE][MAX_SIZE]; 
};

SHAPE shapes[] = {
	{3, {{0, 1, 1}, {0, 0, 1}, {0, 0, 1}}}, 
	{4, {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}}},
	{2, {{1, 1}, {1, 1}}},
	{3, {{1, 1, 0}, {0, 1, 1}}},
	{3, {{0, 1, 0}, {1, 1, 1}}},
};

BackGround::BackGround(int h, int w, Ctrl *parent): Ctrl(parent) {
  this->height = h;
  this->width = w;
  this->cb = NULL;
  for(int i=0; i<this->height; i++) {
	for(int j=0; j<this->width; j++) {
	  if(i==0 || j==0 || i==this->height-1 || j == this->width-1) {data[i][j] = 1;}
      else {data[i][j] = 0;}
	}
  }
  srand(time(0));
}

int BackGround::erase() {
  int line;
  bool needErase=false;

  for(int i=1; i<this->width-1; i++) {
	if(this->data[1][i]) {
	  return -1;
	}
  }

  for(line=1; line<this->height-1; line++) {
	bool isErase=true;
	for(int i=1; i<this->width-1; i++) {
	  if(!this->data[line][i]) {
	    isErase=false;
		break;
	  }
	}

	if(isErase) {
	  needErase = true;
	  break;
	}
  }

  if(!needErase) {
	return 0;
  }

  for(i=line; i>1; i--) {
	for(int j=1; j<this->width-1; j++) {
	  this->data[i][j] = this->data[i-1][j];
	}
  }

  for(int j=1; j<this->width-1; j++) {
	this->data[1][j] = 0;
  }
  this->erase();
  return 1;
}

bool BackGround::addPix(int x, int y) {
  int rx=x-this->pos.X;
  int ry=y-this->pos.Y;
  if(rx < 0 || ry < 0 || rx > this->width || ry > this->height) {
    return false;
  }

  if(this->data[ry][rx]) {
	return false;
  }
  this->data[ry][rx] = 1;
  return true;
}

bool BackGround::inRange(int x, int y) {
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

void BackGround::toShow(int focus) {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width; j++) {
      char *showChar;
      if(this->data[i][j]) {showChar = "*";}
      else {showChar = " ";}
      this->setCursor(this->pos.X+j, this->pos.Y+i);
      printf(showChar);
	}
  }
}

int BackGround::TimeEvent(int timestamp) {
  if(this->children.size() == 0) {
	if(this->cb) {
	  delete this->cb;
	}

	int size = sizeof(shapes)/sizeof(SHAPE);
	int index = rand() % size;
	SHAPE shape = shapes[index];

    this->cb = new Cube(shape.length, (Ctrl*)this);
    cb->setPosition(this->pos.X+5, this->pos.Y-shape.length);
    cb->setShape(shape.shape);
    cb->subscribe(EVENT_TYPE_TIME | EVENT_TYPE_KEY);
  }
  return 0;
}

Cube::Cube(int length, Ctrl *parent): Ctrl(parent) {
  if(length > MAX_SIZE) {
    throw exception("length must be less than 4");
  }
  this->length = length;
}

void Cube::toShow(int focus) {
  BackGround *bg = (BackGround*)this->parent;
  for(int i=0;i<this->length;i++) {
    for(int j=0;j<this->length;j++) {
      int x=this->pos.X+j, y=this->pos.Y+i;
	  if(this->data[i][j] && bg->inRange(x, y) && y>bg->pos.Y) {
	    this->setCursor(x, y);
        printf("*");
	  }
	}
  }
}

void Cube::setShape(const int data[][MAX_SIZE]) {
  for(int i=0;i<this->length;i++) {
    for(int j=0;j<this->length;j++) {
	  this->data[i][j] = data[i][j];
	}
  }
}

bool Cube::canMove(int xDlt, int yDlt) {
  BackGround *bg = (BackGround*)this->parent;
  for(int i=0;i<this->length;i++) {
    for(int j=0;j<this->length;j++) {
      int x=this->pos.X+xDlt+j, y=this->pos.Y+yDlt+i;
	  if(this->data[i][j] && !bg->inRange(x, y)) {
	    return false;
	  }
	}
  }
  return true;
}

int Cube::Up() {
  int n = this->length;
  int temp[4][4];
  BackGround *bg = (BackGround*)this->parent;

  for(int i=0; i<n; i++) {
	for(int j=0; j<n; j++) {
      temp[i][j] = this->data[j][n-1-i];

	  int x=this->pos.X+j, y=this->pos.Y+i;
	  if(temp[i][j] && !bg->inRange(x, y)) {
		return 0;
	  }
	}
  }

  for(i=0; i<n; i++) {
	for(int j=0; j<n; j++) {
      this->data[i][j] = temp[i][j];
	}
  }
  return 1;
}

int Cube::Down() {
  if(!this->canMove(0, 0)) {
    this->pos.Y++;
    return 1;
  }

  if(this->canMove(0, 1)) {
    this->pos.Y++;
    return 1;
  }

  BackGround *bg = (BackGround*)this->parent;
  for(int line=0; line<this->length; line++) {
	for(int row=0; row<this->length; row++) {
	  if(this->data[line][row]) {
	    bg->addPix(this->pos.X+row, this->pos.Y+line);
	  }
	}
  }
  this->hide();
  this->release();
  if(bg->erase() < 0) {
	return -1;
  }
  return 0;
}

int Cube::Left() {
  if(!this->canMove(-1, 0)) {
    return 0;
  }
  this->pos.X--;
  return 1;
}

int Cube::Right() {
  if(!this->canMove(1, 0)) {
    return 0;
  }
  this->pos.X++;
  return 1;
}

int Cube::TimeEvent(int timestamp) {
  return this->Down();
}