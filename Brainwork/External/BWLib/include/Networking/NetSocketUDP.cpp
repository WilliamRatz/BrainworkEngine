#include "NetSocketUDP.h"
//NetDefine allready included by NetAddress
#include "../Inc_SmartMacros.h"


NetSocketUDP::NetSocketUDP()
{


}
NetSocketUDP::NetSocketUDP(const NetSocketUDP& p_NetSocketUDP)
{
	m_handle = p_NetSocketUDP.m_handle;
}
NetSocketUDP::~NetSocketUDP()
{
}

NetResult NetSocketUDP::OpenSocket(unsigned short p_port)
{
	m_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_handle == INVALID_SOCKET)
	{
		return NetResult(2);
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.S_un.S_addr = INADDR_ANY;
	address.sin_port = htons(p_port);

	if (bind(m_handle, (const sockaddr*)& address, sizeof(address)) < 0)
	{
		return NetResult(3);
	}

	return NetResult(0);
}
NetResult NetSocketUDP::CloseSocket()
{
#if PLATFORM == BWLIB_PLATFORM_MAC || PLATFORM == BWLIB_PLATFORM_UNIX
	if (close(m_handle) != 0)
	{
		return NetResult(7);
	}
#elif PLATFORM == BWLIB_PLATFORM_WINDOWS
	if (closesocket(m_handle) != 0)
	{
		return NetResult(7);
	}
#endif
	return NetResult(0);
}

NetResult NetSocketUDP::Send(NetAddress netAddress, char* dataArray, int dataArrayLength)
{
	if (sendto(m_handle, (const char*)dataArray, dataArrayLength, 0, (sockaddr*)& netAddress.GetTransportAddress(), sizeof(sockaddr_in)) != dataArrayLength)
	{
		return NetResult(6);
	}

	return NetResult(0);
}
NetAddress NetSocketUDP::Receive(char* p_dataArray, int p_dataArrayLength)
{
#if PLATFORM == BWLIB_PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	if (recvfrom(m_handle,
		(char*)p_dataArray,
		p_dataArrayLength,
		0,
		(sockaddr*)& from,
		&fromLength)
		<= 0)
	{
		return NetAddress(NULL, NULL);
	}
	return NetAddress(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
}

NetResult NetSocketUDP::EnableNonBlocking()
{
#if PLATFORM == BWLIB_PLATFORM_MAC || PLATFORM == BWLIB_PLATFORM_UNIX
	int nonBlocking = 1;
	if (fcntl(m_handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		return NetResult(4);
	}

#elif PLATFORM == BWLIB_PLATFORM_WINDOWS

	DWORD nonBlocking = 1;
	if (ioctlsocket(m_handle,
		FIONBIO,
		&nonBlocking) != 0)
	{
		return NetResult(4);
	}

#endif
	return NetResult(0);
}
NetResult NetSocketUDP::DisableNonBlocking()
{
#if PLATFORM == BWLIB_PLATFORM_MAC || PLATFORM == BWLIB_PLATFORM_UNIX
	int nonBlocking = 0;
	if (fcntl(m_handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		return NetResult(5);
	}

#elif PLATFORM == BWLIB_PLATFORM_WINDOWS

	DWORD nonBlocking = 0;
	if (ioctlsocket(m_handle,
		FIONBIO,
		&nonBlocking) != 0)
	{
		return NetResult(5);
	}

#endif

	return NetResult(0);
}
bool NetSocketUDP::IsOpen() const
{
	if (m_handle == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}