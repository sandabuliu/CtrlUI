#include "Layout.h"
#include<time.h>


Layout::Layout(Ctrl *p): Ctrl(p) {
  this->index=0;
  this->subscribe(EVENT_TYPE_KEY);
}

void Layout::next() {
  if(!this->children.size()) {
	return;
  }

  int size = this->children.size();
  int nextIdx = (this->index+size-1) % size;
  for(int i=0; i<size; i++) {
	if(i == nextIdx) {
	  this->children[i]->setFocus();
	} else {
	  this->children[i]->unsetFocus();
	}
  }
  this->index = nextIdx;
}

void Layout::prev() {
  if(!this->children.size()) {
	return;
  }

  int size = this->children.size();
  int prevIdx = (this->index+1) % size;
  for(int i=0; i<size; i++) {
	if(i == prevIdx) {
	  this->children[i]->setFocus();
	} else {
	  this->children[i]->unsetFocus();
	}
  }
  this->index = prevIdx;
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

