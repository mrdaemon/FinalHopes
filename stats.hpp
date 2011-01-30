#ifndef STATS_H
#define STATS_H

#include <curses.h>
#include <string>
#include <cstring>

#include "screen.hpp"
#include "window.hpp"

enum{
	BUTTON1, BUTTON2, BUTTON3, BUTTON4, STATS
};

class Stats{
public:
	Stats();
	virtual ~Stats();

	bool loop();
private:
	Window* name;
	Window* info;
	Window* banner;
	Window* button1;
	Window* button2;
	Window* button3;
	Window* button4;
	Window* stats;

	const char** bannerstr;
	const char* button1str;
	const char* button2str;
	const char* button3str;
	const char* button4str;
	const char** namestr;
	const char* infostr;

	int ycur; //Cursor of scroll bar in stats window

	void moveCenter(Window* button);
};

#endif // STATS_H
