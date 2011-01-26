#include "main.hpp"

int main(int argc, char** argv){
	Screen::Get().Init();

	move(0, 0);
	addstr("By: Vargeux");

	if(!has_colors()){
		mvprintw(
				Screen::Get().getH() / 2,
				Screen::Get().getW() / 2 - strlen("No color!") / 2,
				"No color!");
		return -1;
	}
	start_color();                          //Start color handling
	init_color(COLOR_WHITE, 500, 500, 500); //White will be gray
	init_pair(1, COLOR_WHITE, COLOR_BLUE);  //Regular window color

	refresh();                 //Swap buffers, print result
	getch();                   //Read key

	SocketServer::Get().Init();

	int window = 1;
	bool end = false;
	do{
		if(window == 0){
			//Exit
			end = true;
		}else if(window == 1){
			Login* login = new Login();
			login->loop() ? window++ : window--;
			delete login;
			Screen::Get().fillScreen(' ');
		}else if(window == 2){
			Stats* stats = new Stats();
			stats->loop() ? window++ : window--;
			delete stats;
			Screen::Get().fillScreen(' ');
		}else{
			end = true;
		}
	}while(!end);

	SocketServer::Get().Close();

	Screen::Get().Close();

	return 0;
}
