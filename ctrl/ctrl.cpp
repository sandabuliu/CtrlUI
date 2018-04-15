#include"ctrl.h"

#include<conio.h>

void Event::set(int type, int value) {
  this->type = type;
  this->value = value;
}

Ctrl::Ctrl(Ctrl *p) {
  this->parent = p;
  this->visible = true;
  this->focus = false;
  if(p) p->addChild(this);
}

void Ctrl::setApp(Application *app) {
  this->app = app;
}

void Ctrl::getCursor(short &x, short &y) {
  CONSOLE_SCREEN_BUFFER_INFO bInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&bInfo);
  x=bInfo.dwCursorPosition.X;
  y=bInfo.dwCursorPosition.Y;
}

void Ctrl::setCursor(short x, short y) {
  COORD pos={x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Ctrl::hide(bool visible) {
  this->visible = visible;
}

void Ctrl::show(int pFocus) {
  if(!this->visible) {
    return;
  }

  short x, y, cx, cy;
  this->getCursor(x, y);
  this->setCursor(pos.X, pos.Y);
  this->toShow(pFocus);
  this->getCursor(cx, cy);
  cur.X = cx;
  cur.Y = cy;
  this->setCursor(x, y);

  if(pFocus && this->focus) this->setCursor(cx, cy);
  std::vector<Ctrl*>::iterator iter;
  for(iter=children.begin();iter!=children.end();iter++) {
    (*iter)->show(this->focus);
  }
}

void Ctrl::screen(Ctrl *ctrl) {
  system("cls");
  Ctrl *pParent;
  for(pParent=this;pParent->parent;pParent=pParent->parent);
  pParent->hide();

  for(pParent=ctrl;pParent->parent;pParent=pParent->parent);
  pParent->hide(1);
  pParent->setFocus(this);
  pParent->show();
  pParent->lastScreen = pParent;
  this->app->main = ctrl;
}

void Ctrl::revert() {
  if (!this->lastScreen) return;
  system("cls");
  Ctrl *pParent;
  for(pParent=this;pParent->parent;pParent=pParent->parent);
  pParent->hide();

  for(pParent=this->lastScreen;pParent->parent;pParent=pParent->parent);
  pParent->hide(1);
  pParent->setFocus(this);
  pParent->show();
  this->app->main = this->lastScreen;
}

void Ctrl::unsetFocus() {
  this->focus = false;
}

void Ctrl::setFocus(Ctrl *pOld) {
  this->focus = true;
  if(pOld) pOld->focus = false;

  bool focus=true;
  std::vector<Ctrl*>::iterator iter;
  for(iter=children.begin();iter!=children.end();iter++) {
    if((*iter)->focus) {
      focus=false;
      break;
    }
  }
  if(focus && children.size()) {
    for(iter=children.begin();iter!=children.end();iter++) {
      (*iter)->setFocus();
      if((*iter)->focus) break;
    }
  }
}

void Ctrl::addChild(Ctrl *p) {
  this->children.push_back(p);
}

int Ctrl::onEvent(Event &e) {
  int ret=1;
  std::vector<Ctrl*>::iterator iter;
  for(iter=children.begin();iter!=children.end();iter++) {
    if((*iter)->focus) {
      ret=(*iter)->onEvent(e);
      break;
    }
  }

  if (ret == 0) {
    return 0;
  } else if(ret < 0) {
    return ret;
  }
  if (e.type==1) {
    if(e.value==27) {
      return this->Esc();
    } else if (e.value==13) {
      return this->Enter();
    } else if (e.value==9) {
      return this->Tab();
    } else if (e.value==8) {
      return this->BackSpace();
    } else if (e.value==72) {
      return this->Up();
    } else if (e.value==80) {
      return this->Down();
    } else if (e.value==75) {
      return this->Left();
    } else if (e.value==77) {
      return this->Right();
    }
  }
  else {
    return this->CharEvent((char)(e.value));
  }
  return 1;
}

int Ctrl::CharEvent(char key) {return 1;}

int Ctrl::Enter() {return 1;}

int Ctrl::Esc() {return 1;}

int Ctrl::BackSpace() {return 1;}

int Ctrl::Tab() {return 1;}

int Ctrl::Up() {return 1;}

int Ctrl::Down() {return 1;}

int Ctrl::Left() {return 1;}

int Ctrl::Right() {return 1;}

void Ctrl::toShow(int pFocus) {}

void Select::getNextCursor(int index, short &x, short &y) {
  this->getCursor(x, y);
}

void Select::printTitle() {
  printf("%s\n", this->title.c_str());
}


Select::Select(const char *title, int x, int y, const char *items[], int size, Ctrl *parent): Ctrl(parent) {
  this->title = title;
  this->pos.X = x;
  this->pos.Y = y;
  this->select = 0;
  for(int i=0;i<size;i++) this->items.push_back(items[i]);
}

const char* Select::text() {
  return this->items[this->select];
}

void Select::toShow(int pFocus) {
  short x, y;
  this->printTitle();
  for(int i=0;i<this->items.size();i++) {
    this->getNextCursor(i, x, y);
    this->setCursor(x, y);
    if(this->select != i) {
      printf("%s", this->items[i]);
    } else {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0080);
      printf("%s", this->items[i]);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
    }
  }
}

void Select::prev() {
  this->select--;
  if(this->select < 0) {
    this->select=this->items.size()-1;
  }
  this->show();
}

void Select::next() {
  this->select++;
  if(this->select >= this->items.size()) {
    this->select=0;
  }
  this->show();
}

Application::Application(Ctrl *main) {
  this->main = main;
  this->main->setFocus();
  this->main->setApp(this);
}

void Application::start() {
  this->main->show();

  while(1) {
    Event event;
    char key = getch();
    if(key < 0)
    {
      char k = getch();
      if(k==72 || k==80 || k==75 || k==77) event.set(1, k);
      else if(k<0) {
        event.set(0, key);
        this->main->onEvent(event);
        event.set(0, k);
      }
    }
    else if(key==27 || key==13 || key==9 || key==8) {
      event.set(1, key);
    }
    else {
      event.set(0, key);
    }
    if(this->main->onEvent(event)<0) break;
  }
}

Application *Ctrl::app = NULL;