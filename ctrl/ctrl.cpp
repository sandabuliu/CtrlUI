#include"ctrl.h"
#include<time.h>
#include<conio.h>

void Event::set(int type, int value) {
  this->type = type;
  this->value = value;
}

Ctrl::Ctrl(Ctrl *p) {
  this->parent = p;
  this->visible = true;
  this->focus = false;
  this->accessEvent = 0;
  this->isRelease = false;
  
  if(p) {
    p->addChild(this);
	this->setApp(p->app);
  }
}

void Ctrl::release() {
  this->isRelease = true;
}

void Ctrl::setPosition(int x, int y) {
  this->pos.X = x;
  this->pos.Y = y;
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

  int focus = pFocus && this->focus;
  short x, y;
  this->getCursor(x, y);
  this->setCursor(pos.X, pos.Y);
  this->toShow(focus);
  this->setCursor(x, y);

  std::vector<Ctrl*>::iterator iter;
  for(iter=children.begin();iter!=children.end();iter++) {
    (*iter)->show(focus);
  }
}

void Ctrl::toShow(int focus) {/*printf("ctrl!\n");*/}

void Ctrl::unsetFocus() {
  this->focus = false;
}

void Ctrl::setFocus() {
  this->focus = true;
}

void Ctrl::addChild(Ctrl *p) {
  this->children.push_back(p);
  bool hasFocus=false;
  for(int i=0; i<this->children.size(); i++) {
	if(this->children[i]->getFocus()) {
	  hasFocus=true;
	  break;
	}
  }
  if(!hasFocus) {
	this->children[0]->setFocus();
  }
}

void Ctrl::subscribe(int accessEvents) {
  this->accessEvent = accessEvents;
}

bool Ctrl::isSub(int accessEvent) {
  int ret = accessEvent & this->accessEvent;
  return ret != 0;
}

int Ctrl::onEvent(Event &e) {
  if(!this->focus && e.type!=EVENT_TYPE_TIME) {
	return 0;
  }

  int retChild=0, retParent=0, idx=0;
  std::vector<Ctrl*>::iterator iter;
  std::vector<int> indexes;
  for(iter=children.begin();iter!=children.end();iter++) {
	int ret = (*iter)->onEvent(e);
	if(ret < 0) {
      return ret;
	}
	retChild = retChild | ret;

	if((*iter)->isRelease) {
	  indexes.push_back(idx);
	  (*iter)->toRelease();
	}
	idx++;
  }

  for(int i=0; i < indexes.size(); i++) {
	children.erase(children.begin()+indexes[i], children.end());
  }

  if(!this->isSub(e.type)) {
    return retChild;
  }
  if (e.type==EVENT_TYPE_KEY) {
    if(e.value==27) {
      retParent = this->Esc();
    } else if (e.value==13) {
      retParent = this->Enter();
    } else if (e.value==9) {
      retParent = this->Tab();
    } else if (e.value==8) {
      retParent = this->BackSpace();
    } else if (e.value==72) {
      retParent = this->Up();
    } else if (e.value==80) {
      retParent = this->Down();
    } else if (e.value==75) {
      retParent = this->Left();
    } else if (e.value==77) {
      retParent = this->Right();
    }
  }
  else if(e.type==EVENT_TYPE_CHAR) {
    retParent = this->CharEvent((char)(e.value));
  }
  else if(e.type==EVENT_TYPE_TIME) {
	retParent = this->TimeEvent(e.value);  
  }

  if(retParent < 0) {
    return retParent;
  }
  return retParent | retChild;
}

int Ctrl::TimeEvent(int timestamp) {return 0;}

int Ctrl::CharEvent(char key) {return 0;}

int Ctrl::Enter() {return 0;}

int Ctrl::Esc() {return 0;}

int Ctrl::BackSpace() {return 0;}

int Ctrl::Tab() {return 0;}

int Ctrl::Up() {return 0;}

int Ctrl::Down() {return 0;}

int Ctrl::Left() {return 0;}

int Ctrl::Right() {return 0;}

void Ctrl::toRelease() {}


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
  this->subscribe(EVENT_TYPE_KEY | EVENT_TYPE_CHAR);
}

const char* Select::text() {
  return this->items[this->select];
}

void Select::toShow(int focus) {
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
}

void Select::next() {
  this->select++;
  if(this->select >= this->items.size()) {
    this->select=0;
  }
}


BackGround::BackGround(int h, int w, bool fillSpace, Ctrl *parent): Ctrl(parent) {
  this->height = h;
  this->width = w;
  this->fillSpace = fillSpace;
  for(int i=0; i<MAX_SCREEN; i++) {
	for(int j=0; j<MAX_SCREEN; j++) {
	  if(i==0 || j==0 || i==this->height-1 || j == this->width-1) {data[i][j] = 1;}
      else {this->data[i][j] = 0;}
	}
  }
  srand(time(0));
}

void BackGround::toShow(int focus) {
  for(int i=0; i<this->height; i++) {
    for(int j=0; j<this->width; j++) {
	  this->setCursor(this->pos.X+j, this->pos.Y+i);
      if(this->data[i][j]) {	
        printf("*");
	  } else if(this->fillSpace) {
		printf(" ");
	  }
	}
  }
}

Application::Application(Ctrl *main, int timeDlt) {
  this->main = main;
  this->main->setFocus();
  this->main->setApp(this);
  this->timeDlt = timeDlt;
}

void Application::ShowCursor(int nShow) {
  CONSOLE_CURSOR_INFO ConsoleCursorInfo;
  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ConsoleCursorInfo);
  ConsoleCursorInfo.bVisible=nShow;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ConsoleCursorInfo);
}

void Application::Start() {
  this->main->show();

  int ts = clock();
  while(1) {
	int ret1=0, ret2=0;
	if(kbhit()) {
      Event event;
      char key = getch();
      if(key < 0) {
        char k = getch();
        if(k==72 || k==80 || k==75 || k==77) event.set(EVENT_TYPE_KEY, k);
        else if(k<0) {
          event.set(EVENT_TYPE_CHAR, key);
          this->main->onEvent(event);
          event.set(EVENT_TYPE_CHAR, k);
		}
	  } else if(key==27 || key==13 || key==9 || key==8) {
        event.set(EVENT_TYPE_KEY, key);
	  } else {
        event.set(EVENT_TYPE_CHAR, key);
	  }
	  ret1 = this->main->onEvent(event);
      if(ret1<0) break;
	}

	int now = clock();
	if(now-ts >= this->timeDlt) {
	  Event event;
	  event.set(EVENT_TYPE_TIME, now);
      ret2 = this->main->onEvent(event);
	  if(ret2<0) break;
	  ts = clock();
    }

	if(ret1 || ret2) {
      this->main->show();
	}
  }
  this->main->show();
}

Application *Ctrl::app = NULL;