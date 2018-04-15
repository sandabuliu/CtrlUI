#ifndef	__LAYOUT_H__
#define __LAYOUT_H__

#include "ctrl.h"

class Layout: public Ctrl {
  protected:
    int index;

  public:
    Layout(Ctrl *p=NULL);
    void next();
    void prev();
};


class HLayout: public Layout {
  public:
    HLayout(Ctrl *p=NULL);
    virtual int Left();
    virtual int Right();
};


class VLayout: public Layout {
  public:
    VLayout(Ctrl *p=NULL);
    virtual int Up();
    virtual int Down();
};

#endif
