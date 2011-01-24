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
#ifndef PACKETS_H
#define PACKETS_H

#include <cstdio>
#include <cstdlib>

void err();

enum{
//Client to server
	//Connection
	ID_KEEP_ALIVE       = 0x00,
	ID_LOGIN_REQUEST    = 0x01,
	ID_CONNECTING       = 0x02,
	ID_DISCONNECT       = 0x03,

	//Player actions
	ID_PLAYER_INFO      = 0x04,
	ID_PLAYER_MOVE      = 0x05,
	ID_PLAYER_ATTACK    = 0x06,

	//Inventory
	ID_LOOT_ITEM        = 0x10,
	ID_DESTROY_ITEM     = 0x12,
	ID_USE_ITEM         = 0x13,
	ID_EQUIP_ITEM       = 0x15,
	ID_UNEQUIP_ITEM     = 0x16,
	ID_DROP_ITEM        = 0x17,


//Server to client
	//Connection
	ID_PING_RETURN      = 0x00,
	ID_LOGIN_RESPONSE   = 0x01,
	ID_CONNECTED        = 0x02,
	ID_KICK             = 0x03,
	
	//Player actions
	ID_PLAYER_MOVED     = 0x04,
	ID_PLAYER_ENGAGED   = 0x05,
	ID_PLAYER_ATTACKED  = 0x06,
	ID_PLAYER_STATUS    = 0x07,

	//Inventory
	ID_LOOTED_ITEM      = 0x10,
	ID_DESTROYED_ITEM   = 0x12,
	ID_USED_ITEM        = 0x13,
	ID_CONSUMED_ITEM    = 0x14,
	ID_EQUIPED_ITEM     = 0x15,
	ID_UNEQUIPED_ITEM   = 0x16,
	ID_DROPED_ITEM      = 0x17,

	//Mob actions
	ID_MOB_MOVED        = 0x20,
	ID_MOB_ENGAGED      = 0x21,
	ID_MOB_ATTACKED     = 0x22,

	//Events
	ID_SPAWN_PLAYER     = 0x40,
	ID_SPAWN_MOB        = 0x41,

	ID_UNSPAWN_PLAYER   = 0x48,
	ID_UNSPAWN_MOB      = 0x49,

//Server to auth
	ID_CHECK_ACCOUNT    = 0x80,


//Auth to server
	ID_CHECK_RESPONSE   = 0x80,
};

//Regular Packet
struct packet{
	unsigned char packetID;
	unsigned int length;
	unsigned char buffer[251];
};


//Client to server
//Connection
struct packet_keep_alive{
	unsigned char packetID;
	unsigned int length;
	unsigned char pad[3];
};
struct packet_login_request{
	unsigned char packetID;
	unsigned int length;
	char username[23];
	char password[24];
};
struct packet_connecting{
	unsigned char packetID;
	unsigned int length;
	unsigned char pad[3];
};
struct packet_disconnect{
	unsigned char packetID;
	unsigned int length;
	unsigned char pad[3];
};
//Player actions
struct packet_player_info{
	unsigned char packetID;
	unsigned int length;
	int health;
	int power;
	int damage;
	unsigned char pad[3];
};
struct packet_player_move{
	unsigned char packetID;
	unsigned int length;
	int speed;
	int direction;
	int pitch;
	unsigned char pad[1];
};

//Server to client
//Connection
struct packet_ping_return{
	unsigned char packetID;
	unsigned int length;
	unsigned char pad[1];
};
struct packet_login_response{
	unsigned char packetID;
	unsigned int length;
	unsigned char status;
	unsigned char pad[2];
};
struct packet_connected{
	unsigned char packetID;
	unsigned int length;
	unsigned char pad[3];
};
struct packet_kick{
	unsigned char packetID;
	unsigned int length;
	unsigned char reason;
	unsigned char pad[2];
};

//Server to auth
struct packet_check_account{
	unsigned char packetID;
	unsigned char username[23];
	unsigned char password[24];
};

//Auth to server
struct packet_check_response{
	unsigned char packetID;
	unsigned char status;
	unsigned char pad[2];
};

#endif //PACKETS_H
