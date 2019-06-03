//
//  NetSocketUDP.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef NETSOCKETUDP_H
#define NETSOCKETUDP_H
#include "NetAddress.h"

/*
	UDP is a really simple Network Protocol
	wich sends data to any IP and port you like
	but if it really arrives isn't save.
	(1%-5% of the packages get lost)
*/
class NetSocketUDP
{
private:
	SOCKET m_handle = -1;
public:

	NetSocketUDP();
	NetSocketUDP(const NetSocketUDP&);
	~NetSocketUDP();

	/*
		To open a socket on a specific port,
		use Ports between 1025 and 49999
		or use 0 to get a random free port.
	*/
	NetResult OpenSocket(unsigned short port);

	//Close the socket, than you can reuse the port.
	NetResult CloseSocket();

	//To send data you need to have a pointer to your dataArray and the length of the array.
	NetResult Send(NetAddress netAddress, char* dataArray, int dataArrayLength);

	/*
		For reiving you need an array collect all data
		The array has to be long enough for the message
		(if the message has 50 chars and your array has a lenght of
		40 chars you didn't get the first 40 you get nothing of the message).
	*/
	NetAddress Receive(char* dataArray, int dataArrayLength);

	/*
		Standardmode = NonBlocking disabled
		With enabling NonBlocking the programm will 
		continue also if it don't receive any data
	*/
	NetResult EnableNonBlocking();

	/*
		Standardmode = NonBlocking disabled
		With disabling NonBlocking the programm will
		stop if you try to receive data, if any data occur
		the programm will continue
	*/
	NetResult DisableNonBlocking();

	//Check if this port is allready opened 
	bool IsOpen() const;
};

#endif