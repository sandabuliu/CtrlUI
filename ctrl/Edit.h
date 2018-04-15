#ifndef	__EDIT_H__
#define __EDIT_H__

#include"ctrl.h"

class Edit: public Ctrl {
  protected:
    int max;
    std::string title;
    std::string text;

  public:
    Edit(const char *title, int x, int y, int max=-1, Ctrl *parent=NULL);
    virtual void toShow(int pFocus);
    virtual int CharEvent(char key);
    virtual int BackSpace();
};

#endif
