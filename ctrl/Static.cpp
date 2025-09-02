#include "Static.h"


Static::Static(const char *text, int x, int y, Ctrl *parent): Ctrl(parent) {
  this->text = text;
  this->pos.X = x;
  this->pos.Y = y;
}

void Static::toShow(int focus) {
  printf(this->text.c_str());
}
