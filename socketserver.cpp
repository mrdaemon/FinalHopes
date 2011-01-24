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
#include "socketserver.hpp"

SocketServer::SocketServer(){
	socket = new Socket(SOCK_DGRAM);
	data = (struct packet*)malloc(sizeof(struct packet));
}
SocketServer::~SocketServer(){
	delete socket;
	delete data;
}

bool SocketServer::Init(){
	clilen = sizeof(struct sockaddr_in);
	servlen = sizeof(struct sockaddr_in);

	//0 out the struct, for protection
	memset(&server, 0, servlen);
	server.sin_family = AF_INET; //IPv4
	server.sin_port = htons(4056); //host to unsigned short, port
	server.sin_addr.s_addr = inet_addr("24.203.212.197");

	if(bind(socket->getFD(), (struct sockaddr*)&server, sizeof(struct sockaddr_in)) < 0){
		//std::cout << "Error binding socket." << std::endl;
	}

	return true;
}
bool SocketServer::Close(){
	return true;
}

struct packet* SocketServer::receive(){
	if(recvfrom(socket->getFD(), data, PACKET_MAX_SIZE, 0, (struct sockaddr*)&server, &servlen) < 0){
		std::cout << "Error reading packet" << std::endl;
		perror("Error");
	}
	return data;
}
void SocketServer::send(struct packet* packet, int length){
	struct packet sendPacket;
	memcpy(&sendPacket, packet, length);
	if(sendto(socket->getFD(), &sendPacket, length, 0, (struct sockaddr*)&server, servlen) < 0){
		std::cout << "Error writing packet." << std::endl;
		perror("Error");
	}
}
