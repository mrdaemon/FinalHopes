#include "main.hpp"

int main(int argc, char** argv){
	Screen::Get().Init();

	move(0, 0);
	addstr("By: Vargeux");

	if(!has_colors()){
		mvprintw(
				Screen::Get().getY() / 2,
				Screen::Get().getX() / 2 - strlen("No color!") / 2,
				"No color!");
		return -1;
	}
	start_color();                          //Start color handling
	init_color(COLOR_WHITE, 500, 500, 500); //White will be gray
	init_pair(1, COLOR_WHITE, COLOR_BLUE);  //Regular window color
	attron(COLOR_PAIR(1));

	refresh();                 //Swap buffers, print result
	getch();                   //Read key

	SocketServer::Get().Init();

	Login* login = new Login();

	int window = 1;
	switch(window){
		case 0:
			break;

		case 1:
			login->loop() ? window++ : window--;
			break;

		case 2:
			//Stats
			break;
	}

	delete login;

	SocketServer::Get().Close();

	Screen::Get().Close();

	return 0;
}
