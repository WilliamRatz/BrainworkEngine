//
//  Inc_BWSmartMacros.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef INC_SMARTMACROS_H
#define INC_SMARTMACROS_H
#include <iostream>
#include <chrono>


#define PrintArray(pointer, length) for(unsigned int len = 0; len < length; ++len) { if(len != length-1){ std::cout << pointer[len] << " : " }else{ std::cout << pointer[len] } }
#define PrintArrayln(pointer, length) for(unsigned int len = 0; len < length; ++len) { if(len != length-1){ std::cout << pointer[len] << std::endl } else{ std::cout << pointer[len] } }

#define Print(output) std::cout << (output);
#define Println(output) std::cout << (output) << std::endl;

#define TimeCheck();

#endif