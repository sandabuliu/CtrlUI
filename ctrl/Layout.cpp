#include "Layout.h"


Layout::Layout(Ctrl *p): Ctrl(p) {
  this->index=0;
}

void Layout::next() {
  if(!this->children.size()) return;

  int old = this->index;
  this->index--;
  if(this->index<0){
    this->index = this->children.size()-1;
  }
  this->children[this->index]->setFocus(this->children[old]);
  this->show();
}

void Layout::prev() {
  if(!this->children.size()) return;

  int old = this->index;
  this->index++;
  if(this->index>=this->children.size()){
    this->index = 0;
  }
  this->children[this->index]->setFocus(this->children[old]);
  this->show();
}

HLayout::HLayout(Ctrl *p): Layout(p) {}

int HLayout::Left() {
  this->prev();
  return 1;
}

int HLayout::Right() {
  this->next();
  return 1;
}

VLayout::VLayout(Ctrl *p): Layout(p) {}

int VLayout::Up() {
  this->prev();
  return 1;
}

int VLayout::Down() {
  this->next();
  return 1;
}

