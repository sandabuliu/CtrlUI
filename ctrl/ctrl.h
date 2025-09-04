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

#define EVENT_TYPE_CHAR 0x1
#define EVENT_TYPE_KEY  0x2
#define EVENT_TYPE_TIME 0x4

class Application;

class Ctrl {
  protected:
    Ctrl *parent;
    std::vector<Ctrl*> children;
    bool visible;
    bool focus;
	bool isRelease;
	int accessEvent;
    Ctrl *lastScreen;
    static Application *app;

  public:
    Ctrl(Ctrl *p=NULL);
	COORD pos;
    std::vector<Ctrl*> getChildren() {return children;}
	bool getFocus() {return focus;}
	Ctrl *GetParent() {return parent;}
    void setApp(Application *app);
	void setPosition(int x, int y);
    void getCursor(short &x, short &y);
    void setCursor(short x, short y);
    void hide(bool visible=0);
	void unsetFocus();
    void setFocus();
	void subscribe(int accessEvents);
	bool isSub(int accessEvent);
	void release();
	virtual void toRelease();
    virtual void addChild(Ctrl *p);
    virtual int onEvent(Event &e);
    virtual int CharEvent(char key);
	virtual int TimeEvent(int timestamp);
    virtual int Enter();
    virtual int Esc();
    virtual int BackSpace();
    virtual int Tab();
    virtual int Up();
    virtual int Down();
    virtual int Left();
    virtual int Right();
	virtual void show(int pFocus=1);
    virtual void toShow(int focus);
	~Ctrl() {}
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
    void toShow(int focus);
    void prev();
    void next();
};

#define MAX_SCREEN 500

class BackGround: public Ctrl {
  public:
    int height;
    int width;
	bool fillSpace;
	int data[MAX_SCREEN][MAX_SCREEN];
    BackGround(int h, int w, bool fillSpace=false, Ctrl *parent=NULL);
	void toShow(int focus);
};

class Application {
  public:
    Ctrl *main;
	int timeDlt;

    Application(Ctrl *main, int timeDlt=100);
    void Start();
	void ShowCursor(int nShow);
};
#endif