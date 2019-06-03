//
//  NetDefine.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef NETDEFINE_H
#define NETDEFINE_H

// platform detection
#define BWLIB_PLATFORM_WINDOWS  1
#define BWLIB_PLATFORM_MAC      2
#define BWLIB_PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM BWLIB_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif
#if PLATFORM == BWLIB_PLATFORM_WINDOWS

#include <winsock2.h>
#pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == BWLIB_PLATFORM_MAC || PLATFORM == BWLIB_PLATFORM_UNIX

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#endif

/*
	errorCode < 0 its working but ...
	errorCode == 0 everything is fine
	errorCode > 0 its isen't working ...
*/
struct NetResult
{
	short m_errorCode = 0;

	NetResult(short p_errorCode)
	{
		m_errorCode = p_errorCode;
	}
};

#endif