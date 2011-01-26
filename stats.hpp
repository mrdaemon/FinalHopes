#ifndef STATS_H
#define STATS_H

#include <ncurses.h>
#include <string>
#include <cstring>

#include "screen.hpp"
#include "window.hpp"

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

	const char* bannerstr;
	const char* button1str;
	const char* button2str;
	const char* button3str;
	const char* button4str;
	const char** namestr;
	const char* infostr;

	void printCenter(const char* message, Window* window);
	void moveCenter(Window* button);
};

#endif // STATS_H
