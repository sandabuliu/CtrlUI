#ifndef	__MSGBOX_H__
#define __MSGBOX_H__

#include"ctrl.h"

class MsgBox: public Select {
  protected:
    virtual void getNextCursor(int index, short &x, short &y);
    virtual void printTitle();

  public:
    MsgBox(const char *title, int x, int y, const char *items[], int size, Ctrl *parent=NULL);
    MsgBox(const char *title, int x, int y, Ctrl *parent=NULL);
    virtual int execute();
    virtual int Enter();
    virtual int Esc();
    virtual int Left();
    virtual int Right();
};

#endif
