#include "window.hpp"

Window::Window(int h, int w, int y, int x){
	this->pos.h = h;               //Set position structure
	this->pos.w = w;
	this->pos.y = y;
	this->pos.x = x;

	this->window = newwin(h, w, y, x);

	setBorder(' ', ' ', ' ', ' ', ' ');
}
Window::~Window(){
	setBorder(' ', ' ', ' ', ' ', ' ');
	wrefresh(window);
	delwin(this->window);
}

WINDOW* Window::getWin() const{
	return window;
}
void Window::winrefresh(){
	wrefresh(window);
}
void Window::fillWindow(char fill){
	for(int i = 0; i < this->pos.h; i++){
		for(int j = 0; j < this->pos.w; j++){
			mvwaddch(window, i, j, fill);
		}
	}
}

void Window::setBorder(char left, char right, char top, char bottom, char corner){
	this->border.left   = left;    //Set border structure
	this->border.right  = right;
	this->border.top    = top;
	this->border.bot    = bottom;
	this->border.corner = corner;

	wborder(window, left, right, top, bottom, corner, corner, corner, corner);
}
