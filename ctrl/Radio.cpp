#include "Radio.h"


void Radio::getNextCursor(int index, short &x, short &y) {
  if(this->vertical) {
    std::string str = this->items[index];
    this->getCursor(x, y);
    x = this->pos.X+this->title.length()/2-str.length()/2;
    x = x<0?0:x;
    y += this->delta;
  } else {
    this->getCursor(x, y);
    x += this->delta;
  }
}

void Radio::printTitle() {
  if(this->vertical) {
    printf("%s\n", this->title.c_str());
  } else {
    printf("%s: ", this->title.c_str());
  }
}

Radio::Radio(const char *title, int x, int y, bool vertical, Ctrl *parent): Select(title, x, y, NULL, 0, parent) {
  this->vertical = vertical;
  this->delta = 1;
}

void Radio::setDelta(int delta) {
  this->delta=delta;
}

void Radio::addItem(const char *item) {
  this->items.push_back(item);
}

int Radio::Up() {
  if(!this->vertical) return 1;
  this->prev();
  return 1;
}

int Radio::Down() {
  if(!this->vertical) return 1;
  this->next();
  return 1;
}

int Radio::Left() {
  if(this->vertical) return 1;
  this->prev();
  return 1;
}

int Radio::Right() {
  if(this->vertical) return 1;;
  this->next();
  return 1;
}
