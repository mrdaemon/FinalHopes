#include "window.hpp"

Window::Window(int h, int w, int y, int x){
	this->pos.h = h;               //Set position structure
	this->pos.w = w;
	this->pos.y = y;
	this->pos.x = x;

	this->window = newwin(h, w, y, x);

	setBorder(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}
Window::~Window(){
	setBorder(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	fillWindow(' ');
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
void Window::fillNoBorder(char fill){
	for(int i = 1; i < this->pos.h - 1; i++){
		for(int j = 1; j < this->pos.w - 1; j++){
			mvwaddch(window, i, j, fill);
		}
	}
}
void Window::printMiddle(int y, const char* message){
	mvwprintw(window, y, (pos.w - strlen(message)) / 2, message);
}
void Window::printCenter(const char* message){
	mvwprintw(window, pos.h / 2, (pos.w - strlen(message)) / 2, message);
}
void Window::setBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright){
	this->border.left     = left;    //Set border structure
	this->border.right    = right;
	this->border.top      = top;
	this->border.bot      = bottom;
	this->border.topleft  = topleft;
	this->border.topright = topright;
	this->border.botleft  = botleft;
	this->border.botright = botright;

	wborder(window, left, right, top, bottom, topleft, topright, botleft, botright);
}

void Window::clearWindow(){
	fillWindow(' ');
}
void Window::setCurrBorder(){
	setBorder(border.left, border.right, border.top, border.bot, border.topleft, border.topright, border.botleft, border.botright);
}
void Window::setFocus(int y, int x){
	this->fy = y;
	this->fx = x;
}
void Window::focus(){
	wmove(window, fy, fx);
	winrefresh();
}
