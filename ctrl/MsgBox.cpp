#include "MsgBox.h"


void MsgBox::getNextCursor(int index, short &x, short &y) {
  int i, pos=0, length=0, size=0;
  for(i=0;i<this->title.length();i++) {
    if(this->title[i] == '\n') {
      if(i-pos > length) length=i-pos;
      pos=i+1;
    }
  }
  length = i-pos>length?i-pos:length;

  for(i=0;i<this->items.size();i++) size+=strlen(this->items[i]);
  size += (this->items.size()-1)*4;
  int start = this->pos.X+length/2-size/2<0?0:this->pos.X+length/2-size/2;

  this->getCursor(x, y);
  x=start;

  if(index == 0) {
    y++;
    return;
  }
  for(i=0;i<index;i++) {
    x+=4+strlen(this->items[i]);
  }
}

MsgBox::MsgBox(const char *title, int x, int y, const char *items[], int size, Ctrl *parent): Select(title, x, y, items, size, parent) {
  this->title = title;
  this->pos.X = x;
  this->pos.Y = y;
  this->select = 0;
  for(int i=0;i<size;i++) this->items.push_back(items[i]);
}

MsgBox::MsgBox(const char *title, int x, int y, Ctrl *parent): Select(title, x, y, NULL, 0, parent) {
  this->title = title;
  this->pos.X = x;
  this->pos.Y = y;
  this->select = 0;
  const char *items[]={"OK", "Cancel"};
  for(int i=0;i<2;i++) this->items.push_back(items[i]);
}

int MsgBox::execute() {
  Application *oApp = this->app;

  system("cls");
  Application app((Ctrl*)(this));
  app.Start();
  this->setApp(oApp);

  system("cls");
  this->app->main->show();
  return this->select;
}

int MsgBox::Esc() {
  this->select = -1;
  return -1;
}

int MsgBox::Enter() {
  return -1;
}

int MsgBox::Left() {
  this->prev();
  return 1;
}

int MsgBox::Right() {
  this->next();
  return 1;
}

void MsgBox::printTitle() {
  int line = 0;
  const char *title=this->title.c_str();
  for(const char *ch=title;*ch;ch++)
  {
    if(*ch != '\n') {
      putchar(*ch);
    } else {
      this->setCursor(this->pos.X, this->pos.Y+(++line));
    }
  }
  putchar('\n');
}
