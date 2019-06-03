//
//  NetSocketTCP.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef NETSOCKETTCP_H
#define NETSOCKETTCP_H
#include "NetAddress.h"

/*
	TCP establishes a connction between two PC's 
	and the socket can only send to the connected 
	PC and can't send to anyone else
*/
class NetSocketTCP
{
private:
	SOCKET m_handle = -1;

public:
	NetSocketTCP();
	NetSocketTCP(const NetSocketTCP&);
	~NetSocketTCP();

	/*
		To open a socket on a specific port,
		use Ports between 1025 and 49999
		or use 0 to get a random free port.
	*/
	NetResult OpenSocket(unsigned short port);

	//Close the socket, than you can reuse the port.
	NetResult CloseSocket();

	//To send data you need to have a pointer to your dataArray and the length of the array.
	NetResult Send(char* dataArray, int dataArrayLength);

	/*
		For reiving you need an array collect all data
		The array has to be long enough for the message
		(if the message has 50 chars and your array has a lenght of
		40 chars you didn't get the first 40 you get nothing of the message).
	*/
	NetResult Receive(char* dataArray, int dataArrayLength);

	/*
		In listenning mode the socket can receive an ConnectTo event
		(To disable the ListeningMode you have to close the socket)
	*/
	NetResult SetListeningMode();

	/*
		Normally used in in loop continusly to accept if someone asked for connection
		if a acceptConnection happens a new socket will be created wich can send an receive.
		(newSocket is a pointer were the new socket will be stored)
		(connectedAddress will give you also the address of the transmitter)
	*/
	NetResult AcceptConnection(NetSocketTCP& newSocket, NetAddress& connectedAddress);
	/*
		Normally used in in loop continusly to accept if someone asked for connection
		if a acceptConnection happens a new socket will be created wich can send an receive.
		(newSocket is a pointer were the new socket will be stored)
	*/
	NetResult AcceptConnection(NetSocketTCP& newSocket);
	
	/*
		connecting to a TCP Port wich is in listening mode
		(Warning: You don't connect to the actul port for what you asking)
	*/
	NetResult ConnectTo(NetAddress listeningAddress);

	//Check if this port is allready opened 
	bool IsOpen() const;
};

#endif