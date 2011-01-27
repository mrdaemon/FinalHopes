#include "stats.hpp"

Stats::Stats(){
	//Declare constants
//	bannerstr =  "";
	button1str = "Play now!";
	button2str = "Achievement";
	button3str = "History";
	button4str = "Join chat";
//	namestr =    "";
//	infostr =    "";

	name =    new Window(3, 52, 1, 1);
	info =    new Window(1, 24, 4, 1);
	banner =  new Window(5, 24, 1, Screen::Get().getW() - 25);
	button1 = new Window(3, 15, (Screen::Get().getH() - 5) / 5 + 4, 1);
	button2 = new Window(3, 15, (Screen::Get().getH() - 5) * 2 / 5 + 4, 1);
	button3 = new Window(3, 15, (Screen::Get().getH() - 5) * 3 / 5 + 4, 1);
	button4 = new Window(3, 15, (Screen::Get().getH() - 5) * 4 / 5 + 4, 1);
	stats =   new Window(Screen::Get().getH() - 7, Screen::Get().getW() - 19, 6, 18);

	stats->setBorder('|', '|', '=', '=', '+', '+', '+', '+');
	button1->setBorder('|', '|', '=', '=', '+', '+', '+', '+');
	button2->setBorder('|', '|', '=', '=', '+', '+', '+', '+');
	button3->setBorder('|', '|', '=', '=', '+', '+', '+', '+');
	button4->setBorder('|', '|', '=', '=', '+', '+', '+', '+');

	ycur = 2;

	name->fillWindow('n');
	info->fillWindow('i');
	banner->fillWindow('b');
	button1->printCenter(button1str);
	button2->printCenter(button2str);       //for test
	button3->printCenter(button3str);
	button4->printCenter(button4str);
	mvwprintw(stats->getWin(), 1, stats->pos.w - 2, "^");
	for(int i = 2; i < stats->pos.h - 2; i++){
		mvwprintw(stats->getWin(), i, stats->pos.w - 2, "|");
	}
	mvwprintw(stats->getWin(), stats->pos.h - 2, stats->pos.w - 2, "v");

	button1->setFocus(1, (button1->pos.w - strlen(button1str)) / 2);
	button2->setFocus(1, (button2->pos.w - strlen(button2str)) / 2);
	button3->setFocus(1, (button3->pos.w - strlen(button3str)) / 2);
	button4->setFocus(1, (button4->pos.w - strlen(button4str)) / 2);
	stats->setFocus(ycur, stats->pos.w - 2);
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
	int focus; //Window focus: 0: 1: 2: 3: buttons ; 4: stats
	bool done = false;
	int keyPressed;

	name->winrefresh();
	info->winrefresh();
	banner->winrefresh();
	button1->winrefresh();
	button2->winrefresh();
	button3->winrefresh();
	button4->winrefresh();
	stats->winrefresh();

	button1->focus();
	focus = BUTTON1;

	do{
		keyPressed = wgetch(stats->getWin());

		switch(keyPressed){
			case 0x09: //Tab
				switch(focus){
					case BUTTON1:
						button2->focus();
						focus = BUTTON2;
						break;

					case BUTTON2:
						button3->focus();
						focus = BUTTON3;
						break;

					case BUTTON3:
						button4->focus();
						focus = BUTTON4;
						break;

					case BUTTON4:
						stats->focus();
						focus = STATS;
						break;

					case STATS:
						button1->focus();
						focus = BUTTON1;
						break;
				}
				break;

			case 0x0A: //Enter
				switch(focus){
					case BUTTON1:
						//Start seeking game
						break;

					case BUTTON2:
						//Switch stats for achievements
						break;

					case BUTTON3:
						//Switch stats for history
						break;

					case BUTTON4:
						//Switch for char screen
						break;

					case STATS:
						//Page down
						break;
				}
				break;

			case KEY_LEFT:
				switch(focus){
					case STATS:
						button4->focus();
						focus = BUTTON4;
						break;
				}
				break;

			case KEY_RIGHT:
				switch(focus){
					case BUTTON1:
					case BUTTON2:
					case BUTTON3:
					case BUTTON4:
						stats->focus();
						focus = STATS;
						break;
				}
				break;

			case KEY_UP:
				switch(focus){
					case BUTTON2:
						button1->focus();
						focus = BUTTON1;
						break;

					case BUTTON3:
						button2->focus();
						focus = BUTTON2;
						break;

					case BUTTON4:
						button3->focus();
						focus = BUTTON3;
						break;

					case STATS:
						//Scroll up
						break;
				}
				break;

			case KEY_DOWN:
				switch(focus){
					case BUTTON1:
						button2->focus();
						focus = BUTTON2;
						break;

					case BUTTON2:
						button3->focus();
						focus = BUTTON3;
						break;

					case BUTTON3:
						button4->focus();
						focus = BUTTON4;
						break;

					case STATS:
						//Scroll down
						break;
				}
				break; 
		}

	}while(!done);

	return false;
}

void Stats::moveCenter(Window* window){
	wmove(window->getWin(), window->pos.h / 2, window->pos.w / 2);
}
