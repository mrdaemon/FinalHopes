make:
	g++ -g -Wall login.cpp window.cpp screen.cpp main.cpp socket.cpp socketserver.cpp packets.cpp -c
	g++ -lpanel -lncurses login.o window.o screen.o main.o socket.o socketserver.o packets.o -o this
clean:
	rm -f login.o window.o screen.o main.o socket.o socketserver.o packets.o
