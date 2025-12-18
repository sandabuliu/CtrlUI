#include "emit.h"

Blocks::Blocks(BackGround *p): BackGround(p->height-4, p->width-4, true, p) {
  this->setPosition(p->pos.X+2, p->pos.Y+1);
  for(int i=0; i<MAX_SCREEN; i++) {
	for(int j=0; j<MAX_SCREEN; j++) {
	  this->data[i][j] = 0;
	}
  }
  this->addLine();
  this->addLine();
  this->addLine();
  this->addLine();
  this->name="Blocks";
}

void Blocks::addLine() {
  for(int i=this->height-1; i>0; i--) {
    for(int j=0; j<this->width; j++) {
	  this->data[i][j]=this->data[i-1][j];
	}
  }
  int th=rand()%25+60, needErase=1;
  for(int j=0; j<this->width; j++) {
	int num = rand() % 100;
	this->data[0][j]=num>th?0:1;
	if(this->data[0][j]==0) {
	  needErase=0;
	}
  }
  if(needErase) {
	this->data[0][1]=0;
  }
}

void Blocks::erase() {
  bool goErase=false;
  for(int line=0; line<this->height; line++) {
	bool needErase=true;
    for(int i=0; i<this->width; i++) {
      if(!this->data[line][i]) {
        needErase=false;
        break;
	  }
	}
    if(!needErase) {
	  continue;
	}

	goErase=true;
    for(i=line; i<this->height-1; i++) {
	  for(int j=0; j<this->width; j++) {
	    this->data[i][j] = this->data[i+1][j];
	  }
	}
    for(int j=0; j<this->width; j++) {
	  this->data[this->height-1][j]=0;
	}
    break;
  }

  if(goErase) {
	this->erase();
  }
}

int Blocks::TimeEvent(int timestamp) {
  for(int j=0; j<this->width; j++) {
	if(this->data[this->height-1][j]) {
	  return -1;
	}
  }

  if(timestamp-this->lastTimestamp < 3000) {
	return 0;
  }

  Bullet *bullet=(Bullet*)this->parent->getChild("Bullet");
  if(bullet==NULL) {
	return -1;
  }
  bullet->change();
  this->addLine();
  this->lastTimestamp=timestamp;
  return 1;
}

Player::Player(BackGround *p): Ctrl(p) {
  this->length=3;
  this->setPosition(p->pos.X+p->width/2-this->length/2, p->pos.Y+p->height-3);
  this->name="Player";
}

void Player::toShow(int focus) {
  for(int i=0; i<this->length; i++) {
    this->setCursor(this->pos.X+i, this->pos.Y+1);
	printf("*");
  }
  this->setCursor(this->pos.X+1, this->pos.Y);
  printf("*");

  Blocks *blocks=(Blocks*)this->parent->getChild("Blocks");
  if(blocks==NULL) {
	return;
  }
  short blocksX=this->pos.X+1-blocks->pos.X, blocksY=0;
  for(i=blocks->height-1; i>=0; i--) {
	if(blocks->data[i][blocksX]) {
	  blocksY=i;
	  break;
	}
  }

  for(i=blocksY+blocks->pos.Y+1; i<this->pos.Y; i++) {
    this->setCursor(this->pos.X+1, i);
    printf(".");
  }
}

int Player::Left() {
  if(pos.X-1 <= this->parent->pos.X) {
	return 0;
  }

  this->setCursor(this->pos.X+1, this->pos.Y);
  printf(" ");
  this->setCursor(this->pos.X+this->length-1, this->pos.Y+1);
  printf(" ");
  pos.X--;
  return 1;
}

int Player::Right() {
  BackGround *bg = (BackGround*)this->parent;
  if(pos.X+length >= bg->pos.X+bg->width-1) {
    return 0;
  }

  this->setCursor(this->pos.X+1, this->pos.Y);
  printf(" ");
  this->setCursor(this->pos.X, this->pos.Y+1);
  printf(" ");
  pos.X++;
  return 1;
}

int Player::Up() {
  Bullet *bullet=(Bullet*)this->parent->getChild("Bullet");
  if(bullet==NULL) {
	return -1;
  }

  bullet->add(this->pos.X+1, this->pos.Y-1);
  return 1;
}

Bullet::Bullet(BackGround *p): Ctrl(p) {
  this->name="Bullet";
}

void Bullet::add(short x, short y) {
  COORD p={x, y};
  this->pixel.push_back(p);
}

void Bullet::toShow(int focus) {
  std::vector<COORD>::iterator iter;
  for(iter=this->pixel.begin();iter!=this->pixel.end();iter++) {
    setCursor((*iter).X, (*iter).Y);
    printf("o");
  }
}

bool Bullet::change() {
  Blocks *blocks=(Blocks*)this->parent->getChild("Blocks");
  if(blocks==NULL) {
	return false;
  }

  std::vector<COORD> items;
  for(int i=0; i<this->pixel.size(); i++) {
    short blocksX=this->pixel[i].X-blocks->pos.X;
    short blocksY=this->pixel[i].Y-blocks->pos.Y;
    if(blocks->data[blocksY-1][blocksX]) {
	  blocks->data[blocksY][blocksX]=1;
	} else {
	  items.push_back(this->pixel[i]);
	}
  }

  if(items.size()==this->pixel.size()) {
	return false;
  }
  this->pixel=items;
  blocks->erase();
  return true;
}

int Bullet::TimeEvent(int timestamp) {
  int ret=this->change();

  for(int i=0; i<this->pixel.size(); i++) {
	ret=1;
    this->pixel[i].Y--;
  }

  return ret;
}