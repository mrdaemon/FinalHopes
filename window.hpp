#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

struct position{
	int w;
	int h;
	int y;
	int x;
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
	void setBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright);
private:
	WINDOW* window;

	void clearWindow();
	void setCurrBorder();
};

#endif //WINDOW_H
