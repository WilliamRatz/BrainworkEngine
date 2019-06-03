//
//  BWFloat.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef BWFLOAT_H
#define BWFLOAT_H

#include "BWDouble.h"
#include <iostream>
#include <string>

class BWFloat
{
private:
	unsigned int m_value = 0;

	static unsigned int getSign(const BWFloat&);
	static unsigned int getExponent(const BWFloat&);
	static unsigned int getMantissa(const BWFloat&);

	BWFloat();
	BWFloat(const unsigned int& p_value);
public:
	BWFloat(std::string floatString);
	BWFloat(const BWFloat&);
	~BWFloat();

#pragma region Methods
	static BWFloat		maxValue		();
	static BWFloat		minValue		();
	static BWFloat		zero			();

	
	static bool			equalZero		(const BWFloat&);
#pragma endregion

#pragma region castOperations
	operator BWDouble();
	operator int();
	operator unsigned int();
#pragma endregion

#pragma region arithmeticOperations
	void operator=(const BWFloat&);
	BWFloat operator-();

	BWFloat& operator+=(const BWFloat&);
	BWFloat& operator-=(const BWFloat&);
	BWFloat& operator*=(const BWFloat&);
	BWFloat& operator/=(const BWFloat&);
	BWFloat operator+(const BWFloat&);
	BWFloat operator-(const BWFloat&);
	BWFloat operator*(const BWFloat&);
	BWFloat operator/(const BWFloat&);
	
	BWDouble operator+(const BWDouble&);
	BWDouble operator-(const BWDouble&);
	BWDouble operator*(const BWDouble&);
	BWDouble operator/(const BWDouble&);

	BWFloat& operator+=(const int&);
	BWFloat& operator-=(const int&);
	BWFloat& operator*=(const int&);
	BWFloat& operator/=(const int&);
	BWFloat operator+(const int&);
	BWFloat operator-(const int&);
	BWFloat operator*(const int&);
	BWFloat operator/(const int&);

	BWFloat& operator+=(const float&);
	BWFloat& operator-=(const float&);
	BWFloat& operator*=(const float&);
	BWFloat& operator/=(const float&);
	BWFloat operator+(const float&);
	BWFloat operator-(const float&);
	BWFloat operator*(const float&);
	BWFloat operator/(const float&);

	BWFloat& operator+=(const double&);
	BWFloat& operator-=(const double&);
	BWFloat& operator*=(const double&);
	BWFloat& operator/=(const double&);
	BWFloat operator+(const double&);
	BWFloat operator-(const double&);
	BWFloat operator*(const double&);
	BWFloat operator/(const double&);
#pragma endregion

#pragma region comparisonOperations
	bool operator==(const BWFloat&);
	bool operator!=(const BWFloat&);
	bool operator>(const BWFloat&);
	bool operator>=(const BWFloat&);
	bool operator<(const BWFloat&);
	bool operator<=(const BWFloat&);

#pragma endregion
};

std::ostream& operator<<(std::ostream&, BWFloat&);
std::ostream& operator<<(std::ostream&, BWFloat);

#endif