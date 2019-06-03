#include "BWMath.h"
#include <cmath>
#include <stdexcept>


const double BWMath::PI = 3.14159265358979323;
const double BWMath::TAU = 6.28318530717958647;
const double BWMath::EULER = 2.71828182845904523;
const double BWMath::toDeg = BWMath::PI / 180;
const double BWMath::toRad = 180 / BWMath::PI;

double BWMath::exp(const double& p_value)
{
	double result = 0;
	unsigned int max = static_cast<unsigned int>(BWMath::ceil(p_value, 0) * 2.0) + 5;
	for (unsigned int i = 0; i <= max; ++i)
	{
		result += BWMath::pow(p_value, i) / static_cast<double>(BWMath::faculty(i));
	}

	return result;
}

double BWMath::log(const double& p_value)
{
	if (p_value < 0)
		throw std::logic_error("log of negative value is undefined");

	double copieValue = p_value;
	double result = 0;

	for (double a = 1; a < 1000000.0; a *= 10)
	{
		double count = 0;
		while (copieValue >= BWMath::pow(10, count))
		{
			++count;
		}
		result += ((count == 0) ? count : --count / a);

		copieValue /= BWMath::pow(10, count);
		copieValue = BWMath::pow(copieValue, 10);
	}

	return result;
}
double BWMath::ln(const double& p_value)
{
	if (p_value < 0)
		throw std::logic_error("ln of negative value is undefined");

	return BWMath::log(p_value) / BWMath::log(BWMath::EULER);
}

double BWMath::sin(const double& p_angle)
{
	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = result - (BWMath::pow(result, 3.0) / 6.0)
		+ (BWMath::pow(result, 5.0) / 120.0)
		- (BWMath::pow(result, 7.0) / 5040.0)
		+ (BWMath::pow(result, 9.0) / 362880.0)
		- (BWMath::pow(result, 11.0) / 39916800.0);
	/*result^13 / 13!*/


//works wenn p_angle was multiplied with toDeg
	if (std::fmod(p_angle * toRad, 360) > 180) {
		result *= -1;
	}

	return BWMath::floor(result, 7);
}
double BWMath::cos(const double& p_angle)
{
	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = 1.0 - (BWMath::pow(result, 2.0) / 2.0)
		+ (BWMath::pow(result, 4.0) / 24.0)
		- (BWMath::pow(result, 6.0) / 720.0)
		+ (BWMath::pow(result, 8.0) / 40320.0)
		- (BWMath::pow(result, 10.0) / 3628800.0);
	/*result^12 / 12!*/

	if (std::fmod(p_angle * toRad, 360) > 90 && std::fmod(p_angle * toRad, 360) < 270)
	{
		if (BWMath::sign((float)result) != -1)
		{
			result *= -1;
		}
	}

	return BWMath::floor(result, 7);
}
double BWMath::tan(const double& p_angle)
{
	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = result + (BWMath::pow(result, 3.0) * (1.0 / 3.0))
		+ (BWMath::pow(result, 5.0) * (2.0 / 15.0))
		+ (BWMath::pow(result, 7.0) * (17.0 / 315.0))
		+ (BWMath::pow(result, 9.0) * (62.0 / 2835.0))
		+ (BWMath::pow(result, 11.0) * (1382.0 / 155925.0))
		+ (BWMath::pow(result, 13.0) * (21844.0 / 6081075.0));
	/*taylor series for n = 8 */

	return BWMath::floor(result, 7);
}
double BWMath::cot(const double& p_angle)
{
	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = (1 / result)
		- (result * (1.0 / 3.0))
		- (BWMath::pow(result, 3.0) * (1.0 / 45.0))
		- (BWMath::pow(result, 5.0) * (2.0 / 945.0))
		- (BWMath::pow(result, 7.0) * (1.0 / 4725.0))
		- (BWMath::pow(result, 9.0) * (2.0 / 93555.0));
	/*taylor series for n = 6 is to inaccurate with double */

	return BWMath::floor(result, 7);
}

double BWMath::arcSin(const double& p_angle)
{
	//if p_angle is bigger than 0.9 the calculation isn't exact

	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = result + (0.5 * (BWMath::pow(result, 3.0) / 3.0))
		+ ((3.0 / 8.0) * (BWMath::pow(result, 5.0) / 5.0))
		+ ((5.0 / 16.0) * (BWMath::pow(result, 7.0) / 7.0))
		+ ((35.0 / 128.0) * (BWMath::pow(result, 9.0) / 9.0))
		+ ((63.0 / 256.0) * (BWMath::pow(result, 11.0) / 11.0))
		+ ((231.0 / 1024.0) * (BWMath::pow(result, 13.0) / 13.0))
		+ ((429.0 / 2048.0) * (BWMath::pow(result, 15.0) / 15.0))
		+ ((6435.0 / 32768.0) * (BWMath::pow(result, 17.0) / 17.0));
	/*taylor series for n = 8 = 1*3*5*7*9*11*13*15*17 / 2*4*6*8*10*12*14*16*18 * x^15 / 15 */

	return BWMath::floor(result, 7);
}
double BWMath::arcCos(const double& p_angle)
{
	return BWMath::floor((BWMath::PI / 2) - BWMath::arcSin(p_angle), 7);
}
double BWMath::arcTan(const double& p_angle)
{
	double result = std::fmod(p_angle * toRad, 180);
	result *= toDeg;
	result = result - ((1.0 / 3.0) * (BWMath::pow(result, 3.0)))
		+ ((1.0 / 5.0) * (BWMath::pow(result, 5.0)))
		- ((1.0 / 7.0) * (BWMath::pow(result, 7.0)))
		+ ((1.0 / 9.0) * (BWMath::pow(result, 9.0)))
		- ((1.0 / 11.0) * (BWMath::pow(result, 11.0)))
		+ ((1.0 / 13.0) * (BWMath::pow(result, 13.0)));
	/*taylor series for n = 8 = 1*3*5*7*9*11*13 / 2*4*6*8*10*12*14 * x^15 / 15 */

/*if (std::fmod(p_angle * toRad, 360) > 90 && std::fmod(p_angle * toRad, 360) < 270)
{
	if (BWMath::sign((float)result) != -1)
	{
		result *= -1;
	}
}*/

	return BWMath::floor(result, 7);
}
double BWMath::arcCot(const double& p_angle)
{
	return BWMath::floor((BWMath::PI / 2) - BWMath::arcTan(p_angle), 7);
}

double BWMath::sqrt(const double& p_value)
{
	double result;
	result = (p_value + 1) / 2;
	for (int i = 0; i < 5; ++i) {
		result = 0.5*(result + p_value / result);
	}
	return result;
}
double BWMath::sqrt(const double& p_value, const double& p_n)
{
	return BWMath::pow(p_value , 1/p_n);
}

double BWMath::pow(const double& p_base, const double& p_exponent)
{

	if (static_cast<long long int>(p_exponent) == p_exponent)
	{
		//exponent has a hole number
		double result = 1.0;
		for (int i = 0; i < p_exponent; ++i)
		{
			result *= p_base;
		}
		return result;
	}
	else
	{
		//exponent has a decimal number
		return BWMath::exp(p_exponent * BWMath::ln(p_base));
	}
}
double BWMath::faculty(const unsigned int& p_value)
{
	if (p_value < 0) {
		throw std::out_of_range("no negativ faculty");
	}
	double result = 1.0;

	for (unsigned int i = 2; i <= p_value; ++i)
	{
		result *= i;
	}

	return result;
}
double BWMath::abs(const double & p_value)
{
	if (p_value >= 0)
		return p_value;

	return p_value - (2 * p_value);
}
double BWMath::fract(const double& p_value)
{
	if (p_value < 18446744073709551615.0)
	{
		return p_value - (long long int)p_value;
	}
	else
	{
		return 0;
	}
}

double BWMath::round(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10.0, static_cast<double>(p_position) + 1.0);
	temp = static_cast<int>(temp);
	temp -= static_cast<int>(p_value * BWMath::pow(static_cast<double>(10), static_cast<double>(p_position))) * 10.0;

	if (temp > 4.0)
	{
		return BWMath::ceil(p_value, p_position);
	}
	else
	{
		return BWMath::floor(p_value, p_position);
	}
}
double BWMath::floor(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10.0, p_position);
	temp = static_cast<int>(temp);
	temp *= 10.0;
	temp /= BWMath::pow(10.0, static_cast<double>(p_position) + 1.0);

	return temp;
}
double BWMath::ceil(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10.0, static_cast<double>(p_position));
	temp = static_cast<int>(temp);
	temp *= 10.0;
	temp += 10.0;
	temp /= BWMath::pow(10.0, static_cast<double>(p_position) + 1.0);

	return temp;
}

unsigned int BWMath::crossSum(const unsigned int& p_value)
{
	if (p_value == NULL)
		return 0;

	unsigned int tempValue = p_value;
	unsigned int result = 0;

	while (tempValue > 0) {
		result += tempValue % 10;
		tempValue /= 10;
	}
	return result;
}
unsigned int BWMath::countDigits(const unsigned int & p_value)
{
	if (p_value == NULL)
		return 0;

	unsigned int tempValue = p_value;
	int result = 0;

	while (tempValue > 9) {
		tempValue /= 10;
		++result;
	}
	++result;

	return result;
}

int BWMath::sign(const float& p_value)
{
	//return (p_value > 0) - (p_value < 0);
	return (p_value > 0) ? 1 : ((p_value < 0) ? -1 : 0);
}
int BWMath::sign(const int& p_value)
{
	return (p_value > 0) ? 1 : ((p_value < 0) ? -1 : 0);
}
