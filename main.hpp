#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include <cstring>
#include <string>

#include "window.hpp"
#include "screen.hpp"
#include "packets.hpp"
#include "socketserver.hpp"

int main(int argc, char** argv);

void putAuthWindow();

#endif //MAIN_H
