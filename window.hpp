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
	char corner;
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
private:
	WINDOW* window;

	void setBorder(char left, char right, char top, char bottom, char corner);
};

#endif //WINDOW_H
