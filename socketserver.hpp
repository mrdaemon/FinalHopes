/*
	Copyright 2011 Test of Survival. All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are
	permitted provided that the following conditions are met:

	1.	Redistributions of source code must retain the above copyright notice, this list of
		conditions and the following disclaimer.

	2.	Redistributions in binary form must reproduce the above copyright notice, this list
		of conditions and the following disclaimer in the documentation and/or other materials
		provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND ANY EXPRESS OR IMPLIED
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	The views and conclusions contained in the software and documentation are those of the
	authors and should not be interpreted as representing official policies, either expressed
	or implied, of Test of Survival.
*/
#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.hpp"
#include "packets.hpp"

#define LISTEN_BACKLOG 50
#define PACKET_MAX_SIZE 2048

class SocketServer{
public:
	static SocketServer& Get(){
		static SocketServer sockServer;
		return sockServer;
	}

	bool Init();
	bool Close();

	struct packet* receive();
	void send(struct packet* packet, int length);
	char* getIP();
private:
	SocketServer();
	virtual ~SocketServer();

	struct sockaddr_in server, client;
	unsigned int clilen, servlen;
	struct packet* data;
	Socket* socket;
};

#endif //SOCKET_SERVER_H
