make:
	g++ -g -Wall window.cpp screen.cpp main.cpp socket.cpp socketserver.cpp packets.cpp -c
	g++ -lpanel -lncurses window.o screen.o main.o socket.o socketserver.o packets.o -o this
clean:
	rm -f window.o screen.o main.o socket.o socketserver.o packets.o
