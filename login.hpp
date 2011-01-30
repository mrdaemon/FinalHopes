#ifndef LOGIN_H
#define LOGIN_H

#include <curses.h>
#include <string>
#include <cstring>

#include "window.hpp"
#include "screen.hpp"
#include "packets.hpp"
#include "socketserver.hpp"

class Login{
public:
	Login();
	virtual ~Login();

	bool loop();
private:
	Window* window;

	const char* title;
	const char* usernamestr;
	const char* passwordstr;
	const char* loginButstr;
	const char* exitButstr;

	std::string errormsg;
	std::string username;
	std::string password;

	void clearLine(int y, int x, int length);
};

#endif // LOGIN_H
