//
//  BWMath.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Math_H
#define Math_H

class BWMath {

public:

	static const double		PI;
	static const double		TAU;
	static const double		EULER;

	static const double		toDeg;
	static const double		toRad;
	
	static double			exp		(const double& value);

	static double			log			(const double& value);
	static double			ln			(const double& value);

	static double			sin			(const double& angle);
	static double			cos			(const double& angle);
	static double			tan			(const double& angle);
	static double			cot			(const double& angle);

	static double			arcSin		(const double& angle);
	static double			arcCos		(const double& angle);
	static double			arcTan		(const double& angle);
	static double			arcCot		(const double& angle);

	static double			sqrt		(const double& value);
	static double			sqrt		(const double& value, const double& n);
	static double			pow			(const double& base, const double& exponent);
	static double			faculty		(const unsigned int& value);
	static double			abs			(const double& value);

	static double			fract		(const double& value);
	static double			round		(const double& value, const int& position);
	static double			floor		(const double& value, const int& position);
	static double			ceil		(const double& value, const int& position);
	static unsigned int		crossSum	(const unsigned int& value);
	static unsigned int		countDigits	(const unsigned int& value);
	
	static int				sign		(const float& value);
	static int				sign		(const int& value);
};



#endif /* Math_hpp */
