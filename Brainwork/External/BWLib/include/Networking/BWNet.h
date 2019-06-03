//
//  BWNet.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef BWNET_H
#define BWNET_H
#include <string>
#include "NetDefine.h"

class BWNet
{
public:
	BWNet();
	~BWNet();

	static NetResult InitializeSocketLayer();
	static void ShutdownSockets();
	
	std::string ErrorDecoder(short errorCode);
};

#endif