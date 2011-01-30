#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <cstring>

struct position{
	int w,
	    h,
	    y,
	    x;

};
struct border{
	char left;
	char right;
	char top;
	char bot;
	char topleft;
	char topright;
	char botleft;
	char botright;
};

class Window{
public:
	Window(int h, int w, int y, int x);
	virtual ~Window();

	struct position pos;
	struct border border;

	WINDOW* getWin() const;
	void winrefresh();
	void fillWindow(char fill);
	void fillNoBorder(char fill);
	void printMiddle(int y, const char* message);
	void printCenter(const char* message);
	void setBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright);
	void setFocus(int y, int x);
	void focus();
private:
	WINDOW* window;

	void clearWindow();
	void setCurrBorder();

	int fy, fx;
};

#endif //WINDOW_H
