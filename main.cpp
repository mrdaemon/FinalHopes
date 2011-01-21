#include "main.hpp"

int main(int argc, char** argv){

	Init();

	Print();

	Close();

	return 0;
}

void Init(){
	initscr();			//Start screen mode
	raw();				//Read every keys
	noecho();			//Don't show key pressed
	keypad(stdscr, true);		//Enable more keys (F1, F2, ...)
}
void Print(){
	int y,
		x;
	getmaxyx(stdscr, y, x);		//Get size of window

	mvprintw(y/2, x/2, "Sup");	//Move and then print

	move(0, 0);			//Move cursor
	addstr("By: Vargeux");		//Self-explained

	refresh();			//Swap buffers, print result
	getch();			//Read key
}
void Close(){
	endwin();			//Close window
}
