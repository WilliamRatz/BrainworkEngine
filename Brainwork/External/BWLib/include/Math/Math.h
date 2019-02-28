//
//  Math.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Math_H
#define Math_H
#include <iostream>

class MathLib {
public:

	virtual ~MathLib() = 0;

	static double Sqrt(const double& value);
	static double Sin(const double& angle);
	static double Cos(const double& angle);
	static double Tan(const double& angle);

	static double ArcSin(const double& angle);
	static double ArcCos(const double& angle);
	static double ArcTan(const double& angle);

	static double pow(const double& base, const double& exponent);
	static std::size_t faculty(const std::size_t& value);

	static double fract(const double& value);
	static double round(const double& value, const int& position);
	static double floor(const double& value, const int& position);
	static double ceil(const double& value, const int& position);
	
	static int sign(const float& value);

	static double PI_Calc();
	static double E_Calc();

	static const double PI;
	static const double TAU;
	static const double EULER;

	static const double toDeg;
	static const double toRad;
};



#endif /* Math_hpp */
