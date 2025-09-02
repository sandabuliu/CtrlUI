#ifndef	__STATIC_H__
#define __STATIC_H__

#include"ctrl.h"

class Static: public Ctrl {
  protected:
    std::string text;

  public:
    Static(const char *text, int x, int y, Ctrl *parent=NULL);
    virtual void toShow(int focus);
};

#endif