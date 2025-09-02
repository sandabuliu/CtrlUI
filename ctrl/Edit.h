#ifndef	__EDIT_H__
#define __EDIT_H__

#include"ctrl.h"

class Edit: public Ctrl {
  protected:
    int max;
	COORD cur;
    std::string title;
    std::string text;

  public:
    Edit(const char *title, int x, int y, int max=-1, Ctrl *parent=NULL);
    void toShow(int focus);
	void show(int pFocus=1);
    virtual int CharEvent(char key);
    virtual int BackSpace();
};

#endif
