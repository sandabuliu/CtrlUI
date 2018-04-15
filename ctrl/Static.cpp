#include "Static.h"


Static::Static(const char *text, int x, int y, Ctrl *parent): Ctrl(parent) {
  this->text = text;
  this->pos.X = x;
  this->pos.Y = y;
}

void Static::setFocus(Ctrl *pOld) {
  this->focus = false;
  if(pOld) pOld->setFocus();
}

void Static::toShow(int pFocus) {
  printf(this->text.c_str());
}
