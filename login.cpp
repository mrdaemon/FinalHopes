#include "login.hpp"

Login::Login(){
	//Declare constants
	title = "-Login-";
	usernamestr = "Username:";
	passwordstr = "Password:";
	loginButstr = "Login";
	exitButstr = "Exit";

	curs_set(true);
	init_pair(2, COLOR_BLACK, COLOR_WHITE); //Button color

	//Prepare window
	window = new Window(
			8, 40, 
			(Screen::Get().getH() - 8) / 2, (Screen::Get().getW() - 40) / 2);
	wattron(window->getWin(), COLOR_PAIR(1));
	window->fillWindow(' ');

	window->printMiddle(0, title);
	mvwprintw(window->getWin(), 2, 1, usernamestr);
	mvwprintw(window->getWin(), 4, 1, passwordstr);

	wattron(window->getWin(), COLOR_PAIR(2));
	mvwprintw(window->getWin(), 6, window->pos.w / 3 - strlen(loginButstr) / 2, loginButstr);
	mvwprintw(window->getWin(), 6, window->pos.w * 2 / 3 - strlen(exitButstr) / 2, exitButstr);

	wattron(window->getWin(), COLOR_PAIR(1));
	wmove(window->getWin(), 2, strlen(usernamestr) + 2);
}
Login::~Login(){
	wattroff(window->getWin(), COLOR_PAIR(1));
	delete window;
}

bool Login::loop(){
	bool done;
	int keyPressed;
	int i = 0;  //Window focus: 0: Username ; 1: Password ; 2: Login button ; 3: Exit button
	do{
		done = false;

		keyPressed = wgetch(window->getWin());

		switch(keyPressed){
			case 0x20 ... 0x7E: //If valid character in ASCII table
				if(i == 0 && username.size() <= 23){ //Username maximum character is 23
					username.insert(username.size(), 1, keyPressed);
					mvwprintw(window->getWin(), 2, strlen(usernamestr) + 2, username.c_str());
				}else if(i == 1 && password.size() <= 23){ //Password maximum character is 24
					password.insert(password.size(), 1, keyPressed);
					std::string hidden = password;
					mvwprintw(window->getWin(), 4, strlen(passwordstr) + 2, hidden.replace(0, password.size(), password.size(), '*').c_str());
				}
				break;
			case 0x09: //Tab
				if(i == 0){
					wmove(window->getWin(), 4, strlen(passwordstr) + password.size() + 2);
					i++;
				}else if(i == 1){
					wmove(window->getWin(), 6, window->pos.w / 3 - strlen(loginButstr) / 2);
					i++;
				}else if(i == 2){
					wmove(window->getWin(), 6, window->pos.w * 2 / 3 - strlen(exitButstr) / 2);
					i++;
				}else{
					wmove(window->getWin(), 2, strlen(usernamestr) + username.size() + 2);
					i = 0;
				}
				break;

			case 0x0A: //Enter
				if(i >= 0 && i <= 2){
					if(username.empty() && password.empty()){
						clearLine(5, 1, window->pos.w - 2);
						window->printMiddle(5, "Empty fields.");
						if(i == 0){
							wmove(window->getWin(), 2, strlen(usernamestr) + username.size() + 2);
						}else if(i == 1){
							wmove(window->getWin(), 4, strlen(passwordstr) + password.size() + 2);
						}else{
							wmove(window->getWin(), 6, window->pos.w / 3 - strlen(loginButstr) / 2);
						}
					}else{
						struct packet_login_request packet;
						struct packet_login_response response;

						//send packet to server
						memset(&packet, 0, sizeof(struct packet_login_request));
						packet.packetID = ID_LOGIN_REQUEST;
						packet.length = sizeof(struct packet_login_request);
						sscanf(username.c_str(), "%23s", packet.username);
						sscanf(password.c_str(), "%24s", packet.password);
						SocketServer::Get().send((struct packet*)&packet, packet.length);

						//Receive packet
						memcpy(&response, SocketServer::Get().receive(), sizeof(struct packet_login_response));
							clearLine(5, 1, window->pos.w - 2);
						if(response.status == 0x00){
							window->printMiddle(5, "Login succeed.");
							return true;
						}else{
							window->printMiddle(5, "Login failed.");
							if(i == 0){
								wmove(window->getWin(), 2, strlen(usernamestr) + username.size() + 2);
							}else if(i == 1){
								wmove(window->getWin(), 4, strlen(passwordstr) + password.size() + 2);
							}else{
								wmove(window->getWin(), 6, window->pos.w / 3 - strlen(loginButstr) / 2);
							}
						}
					}
				}else if(i == 3){
					done = true;
				}
				break;

			case 0x7F: //Backspace
				if(i == 0 && !username.empty()){
					username.resize(username.size() - 1);
					mvwprintw(window->getWin(), 2, strlen(usernamestr) + 2 + username.size(), " ");
					mvwprintw(window->getWin(), 2, strlen(usernamestr) + 2, username.c_str());
				}else if(i == 1 && !password.empty()){
					password.resize(password.size() - 1);
					mvwprintw(window->getWin(), 4, strlen(passwordstr) + 2 + password.size(), " ");
					std::string hidden = password;
					mvwprintw(window->getWin(), 4, strlen(passwordstr) + 2, hidden.replace(0, password.size(), password.size(), '*').c_str());
				}
				break;

			default:
				break;

		}

		window->winrefresh();

	}while(!done);

	return false;
}

void Login::clearLine(int y, int x, int length){
	std::string pad(length, ' ');
	mvwprintw(window->getWin(), y, x, pad.c_str());
}
