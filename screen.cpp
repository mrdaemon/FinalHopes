#include "screen.hpp"

Screen::Screen(){
}
Screen::~Screen(){
}

void Screen::Init(){
	initscr();            //Start screen mode
	cbreak();             //raw() otherwise
	noecho();             //Don't show key pressed
	keypad(stdscr, true); //Every keys
	getmaxyx(stdscr, this->h, this->w);
}
void Screen::Close(){
	endwin();             //Stop screen mode
}

int Screen::getW() const{
	return w;
}
int Screen::getH() const{
	return h;
}
void Screen::fillScreen(char fill){
	for(int i = 0; i < this->w; i++){
		for(int j = 0; j < this->h; j++){
			mvwaddch(stdscr, j, i, fill);
		}
	}
}
