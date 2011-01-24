#include "main.hpp"

int main(int argc, char** argv){
	Screen::Get().Init();

	move(0, 0);                //Move cursor
	addstr("By: Vargeux"); 	   //Self-explained

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
	init_pair(2, COLOR_BLACK, COLOR_WHITE); //Button color
	attron(COLOR_PAIR(1));

	refresh();                 //Swap buffers, print result
	getch();                   //Read key

	SocketServer::Get().Init();

	putAuthWindow();

	SocketServer::Get().Close();

	Screen::Get().Close();

	return 0;
}

void putAuthWindow(){
	int i = 0;
	bool done;
	std::string username;
	std::string password;
	char keyPressed;

	//Set cursor on
	curs_set(true);

	//Prepare window
	Window* window = new Window(
			8, 40, 
			(Screen::Get().getY() / 2) - (7 / 2), (Screen::Get().getX() / 2) - (40 / 2));
	wattron(window->getWin(), COLOR_PAIR(1));
	window->fillWindow(' ');
	mvwprintw(window->getWin(), 0, window->pos.w / 2 - strlen("-Login-") / 2, "-Login-");
	mvwprintw(window->getWin(), 2, 1, "Username:");
	mvwprintw(window->getWin(), 4, 1, "Password:");
	wattron(window->getWin(), COLOR_PAIR(2));
	mvwprintw(window->getWin(), 6, window->pos.w / 3 - strlen("Login") / 2, "Login");
	mvwprintw(window->getWin(), 6, window->pos.w * 2 / 3 - strlen("Cancel") / 2, "Cancel");

	wattron(window->getWin(), COLOR_PAIR(1));
	wmove(window->getWin(), 2, strlen("Username:") + 2);

	//Keys handling
	do{
		done = false;

		keyPressed = wgetch(window->getWin());

		if(keyPressed >= 0x20 && 
           keyPressed < 0x7F){
			if(i == 0 && username.size() <= 23){
				username.insert(username.size(), 1, keyPressed);
				mvwprintw(window->getWin(), 2, strlen("Username:") + 2, username.c_str());
			}else if(i == 1 && username.size() <= 23){
				password.insert(password.size(), 1, keyPressed);
				mvwprintw(window->getWin(), 4, strlen("Password:") + 2, password.c_str());
			}
		}

		if(keyPressed == 0x7F){
			if(i == 0 && !username.empty()){
				username.erase(username.size() - 1);
				mvwprintw(window->getWin(), 2, strlen("Username:") + 2 + username.size(), " ");
				mvwprintw(window->getWin(), 2, strlen("Username:") + 2, username.c_str());
			}else if(i == 1 && !password.empty()){
				password.erase(password.size() - 1);
				mvwprintw(window->getWin(), 4, strlen("Password:") + 2 + password.size(), " ");
				mvwprintw(window->getWin(), 4, strlen("Password:") + 2, password.c_str());
			}
		}

		switch(keyPressed){
			case 0x09:
				if(i == 0){
					wmove(window->getWin(), 4, strlen("Password:") + password.size() + 2);
					i++;
				}else if(i == 1){
					wmove(window->getWin(), 6, window->pos.w / 3 - strlen("Login") / 2);
					i++;
				}else if(i == 2){
					wmove(window->getWin(), 6, window->pos.w * 2 / 3 - strlen("Cancel") / 2);
					i++;
				}else{
					wmove(window->getWin(), 2, strlen("Username:") + username.size() + 2);
					i = 0;
				}
				break;
			case 0x0A:
				if(i == 2){
					if(username.empty() && password.empty()){
						mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Login succeed.") / 2, "               ");
						mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Empty fields.") / 2, "Empty fields.");
						wmove(window->getWin(), 6, window->pos.w / 3 - strlen("Login") / 2);
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
						if(response.status == 0x00){
							mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Login succeed.") / 2, "               ");
							mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Login succeed.") / 2, "Login succeed.");
							wmove(window->getWin(), 6, window->pos.w / 3 - strlen("Login") / 2);
						}else{
							mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Login succeed.") / 2, "               ");
							mvwprintw(window->getWin(), 5, window->pos.w / 2 - strlen("Login failed.") / 2, "Login failed.");
							wmove(window->getWin(), 6, window->pos.w / 3 - strlen("Login") / 2);
						}
					}
				}else if(i == 3){
					done = true;
				}
				break;
			default:
				break;

		}

		window->winrefresh();

	}while(!done);

}
