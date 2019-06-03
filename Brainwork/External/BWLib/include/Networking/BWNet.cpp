#include "BWNet.h"

BWNet::BWNet()
{
}


BWNet::~BWNet()
{
}

NetResult BWNet::InitializeSocketLayer()
{
#if PLATFORM == BWLIB_PLATFORM_WINDOWS
	WSADATA WsaData;
	if(WSAStartup(MAKEWORD(2, 2),&WsaData) == NO_ERROR)
	{
		return NetResult(0);
	}
	else
	{
		return NetResult(1);
	}
#else
	return true;
#endif
}

void BWNet::ShutdownSockets()
{
#if PLATFORM == BWLIB_PLATFORM_WINDOWS
	WSACleanup();
#endif
}

std::string BWNet::ErrorDecoder(short errorCode)
{
	switch (errorCode)
	{
		case 0:
			return "No Error occurred"; 
			break;
		case 1:
			return "Failed to initialize the sockets layer";
			break;
		case 2:
			return "Failed to open the socket, did you initialized the sockets layer (BWNet::InitializeSocketLayer())";
			break;
		case 3:
			return "Failed to open the socket on your port number, please use an unused port between 1025 and 49999. Or use 0 to get an random free port";
			break;
		case 4:
			return "Failed to enable NonBlocking on your socket. Check if you initialized the sockets layer (BWNet::InitializeSocketLayer()) and if you opened the socket or did you shutdown (BWNet::ShutdownSockets()) all sockets allready";
			break;
		case 5:
			return "Failed to disable NonBlocking on your socket. Check if you allready initialized the sockets layer (BWNet::InitializeSocketLayer()) and if you opened the socket or did you ShutdownSockets (BWNet::ShutdownSockets()) all sockets allready";
			break;
		case 6:
			return "Sending failed check your socket if you setup everything correctly";
			break;
		case 7:
			return "Closing of socket failed is the socket allready created?";
			break;
		case 8:
			return "No connection established, did you initialized the sockets layer (BWNet::InitializeSocketLayer()) and is your socket allready open?";
			break;
		case 9:
			return "No connection could be established, are you initialized the sockets layer (BWNet::InitializeSocketLayer()) allready";
			break;
		case 10:
			return "The Socket couldn't be set to listen mode, are you initialized the sockets layer (BWNet::InitializeSocketLayer()) allready or do you have over 65335 connections ?";
			break;
		case 11:
			return "Sending wasen't possible is the Socket allready connected with the receiver? Did you initialized the sockets layer (BWNet::InitializeSocketLayer())? ";
			break;
		case 12:
			return "No data received is the Socket allready connected with the transmitter? Did you initialized the sockets layer (BWNet::InitializeSocketLayer())? ";
			break;


		
		
		default:
			return "Error code unknown";
			break;

	}
	return std::string();
}
