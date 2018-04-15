#ifndef	__RADIO_H__
#define __RADIO_H__

#include "ctrl.h"

class Radio: public Select {
  protected:
    int delta;
    bool vertical;

    virtual void getNextCursor(int index, short &x, short &y);
    virtual void printTitle();

  public:
    Radio(const char *title, int x, int y, bool vertical=false, Ctrl *parent=NULL);
    void setDelta(int delta);
    void addItem(const char *item);
    virtual int Up();
    virtual int Down();
    virtual int Left();
    virtual int Right();
};

#endif
