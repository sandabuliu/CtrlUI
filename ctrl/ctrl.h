#ifndef	__CTRL_H__
#define __CTRL_H__

#include<vector>
#include<windows.h>

class Event{
  public:
    int type;
    int value;
    void set(int type, int value);
};

class Application;

class Ctrl {
  protected:
    COORD pos;
    COORD cur;
    Ctrl *parent;
    std::vector<Ctrl*> children;
    bool visible;
    bool focus;
    Ctrl *lastScreen;
    static Application *app;

  public:
    Ctrl(Ctrl *p=NULL);
    void setApp(Application *app);
    void screen(Ctrl *ctrl);
    void revert();
    void getCursor(short &x, short &y);
    void setCursor(short x, short y);
    void hide(bool visible=0);
    virtual void show(int pFocus=1);
    virtual void unsetFocus();
    virtual void setFocus(Ctrl *pOld=NULL);
    virtual void addChild(Ctrl *p);
    virtual int onEvent(Event &e);
    virtual int CharEvent(char key);
    virtual int Enter();
    virtual int Esc();
    virtual int BackSpace();
    virtual int Tab();
    virtual int Up();
    virtual int Down();
    virtual int Left();
    virtual int Right();
    virtual void toShow(int pFocus);
};

class Select: public Ctrl {
  protected:
    std::string title;
    std::vector<const char*> items;

    virtual void getNextCursor(int index, short &x, short &y);
    virtual void printTitle();

  public:
    int select;

    Select(const char *title, int x, int y, const char *items[], int size, Ctrl *parent=NULL);
    const char* text();
    virtual void toShow(int pFocus);
    void prev();
    void next();
};

class Application {
  public:
    Ctrl *main;

    Application(Ctrl *main);
    void start();
};
#endif