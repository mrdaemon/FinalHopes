#include "stats.hpp"

Stats::Stats(){
	name =    new Window(3, 52, 1, 1);
	info =    new Window(1, 24, 4, 1);
	banner =  new Window(5, 24, 1, Screen::Get().getW() - 25);
	button1 = new Window(3, 15, (Screen::Get().getH() - 5) / 5 + 4, 1);
	button2 = new Window(3, 15, (Screen::Get().getH() - 5) * 2 / 5 + 4, 1);
	button3 = new Window(3, 15, (Screen::Get().getH() - 5) * 3 / 5 + 4, 1);
	button4 = new Window(3, 15, (Screen::Get().getH() - 5) * 4 / 5 + 4, 1);
	stats =   new Window(Screen::Get().getH() - 7, Screen::Get().getW() - 19, 6, 18);

	stats->setBorder('|', '|', '=', '=', '+', '+', '+', '+');

	name->fillWindow('n');
	info->fillWindow('i');
	banner->fillWindow('b');
	button1->fillNoBorder('1');
	button2->fillNoBorder('2');       //for test
	button3->fillNoBorder('3');
	button4->fillNoBorder('4');
	stats->fillNoBorder('o');

}
Stats::~Stats(){
	delete name;
	delete info;
	delete button1;
	delete button2;
	delete button3;
	delete button4;
	delete stats;
}

bool Stats::loop(){
	int i = 0; //Window focus: 0: 1: 2: buttons ; 3: stats.
	bool done;
	int keyPressed;
	int barx; //Cursor of scroll bar

	do{
		done = false;

		name->winrefresh();
		info->winrefresh();
		banner->winrefresh();
		button1->winrefresh();
		button2->winrefresh();
		button3->winrefresh();
		button4->winrefresh();
		stats->winrefresh();

		keyPressed = wgetch(stats->getWin());

		switch(keyPressed){
			case 0x09: //Tab
				if(i == 0){
					
				}else if(i == 1){

				}else if(i == 2){

				}else{

				}
				break;

			case 0x0A: //Enter
				if(i == 0){

				}else if(i == 1){

				}else if(i == 2){

				}else{

				}
				break;

			case KEY_LEFT:
				if(i == 0){

				}else if(i == 1){

				}else if(i == 2){

				}else{

				}
				break;

			case KEY_RIGHT:
				if(i == 0){

				}else if(i == 1){

				}else if(i == 2){

				}
				break;

			case KEY_UP:
				if(i == 0){

				}else if(i == 1){

				}else if(i == 2){

				}else if(i == 3){

				}
				break;

			case KEY_DOWN:
				if(i == 0){

				}else if(i == 1){

				}else if(i == 2){

				}else if(i == 3){

				}
				break; 
		}

	}while(!done);

	return false;
}

void Stats::printCenter(const char* message, Window* window){
	mvwprintw(window->getWin(), window->pos.h / 2, (window->pos.w + strlen(message)) / 2, message);
}
void Stats::moveCenter(Window* window){
	wmove(window->getWin(), window->pos.h / 2, window->pos.w / 2);
}
