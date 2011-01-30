#ifndef SCREEN_H
#define SCREEN_H

#include <curses.h>

class Screen{
public:
	static Screen& Get(){
		static Screen screen;
		return screen;
	}

	void Init();
	void Close();

	int getW() const;
	int getH() const;
	void fillScreen(char fill);

private:
	Screen();
	virtual ~Screen();

	int w, h;
};

#endif //SCREEN_H
