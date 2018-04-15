#include "Edit.h"


Edit::Edit(const char *title, int x, int y, int max, Ctrl *parent): Ctrl(parent) {
  this->title = title;
  this->pos.X = x;
  this->pos.Y = y;
  this->max = max;
}

void Edit::toShow(int pFocus) {
  if(!(pFocus && this->focus)) {
    printf("%s:%s", title.c_str(), text.c_str());
  } else {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0080);
    printf("%s", title.c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
    printf(":%s", text.c_str());
  }
}

int Edit::CharEvent(char key) {
  static char last_key = 0;
  if(this->max>0 && this->text.length()>=this->max) {
    return 1;;
  }

  if(key<0 && !last_key) {
    last_key=key;
  } else {
    if (last_key) {
      this->text+=last_key;
      last_key=0;
    }
    this->text+=key;
    this->show();
  }
  return 1;
}

int Edit::BackSpace() {
  static int times=1;
  if (text.length()==0) return 1;

  char c = text[text.length()-1];
  text[text.length()-1] = ' ';
  this->show();
  this->setCursor(this->cur.X-1, this->cur.Y);
  text.erase(text.end()-1);

  if(c < 0 && times==1) {
    times=2;
    this->BackSpace();
    times=1;
  }
  return 1;
}
