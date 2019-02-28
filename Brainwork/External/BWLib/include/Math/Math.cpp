#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"


const double MathLib::PI = 3.14159265358979323;
const double MathLib::TAU = 6.28318530717958647;
const double MathLib::EULER = 2.71828182845904523;
const double MathLib::toDeg = MathLib::PI / 180;
const double MathLib::toRad = 180 / MathLib::PI;

double MathLib::Sqrt(const double& value) {

	double result;
	result = (value + 1) / 2;
	for (int i = 0; i < 5; ++i) {
		result = 0.5*(result + value / result);
	}
	return result;
}
double MathLib::Sin(const double& angle) {

	double angleRad = angle * toRad;
	short size = (int)angleRad % 180;
	double result = size + MathLib::fract(angleRad);
	result *= toDeg;
	result = result - MathLib::pow(result, 3) / MathLib::faculty(3) + MathLib::pow(result, 5) / MathLib::faculty(5) - MathLib::pow(result, 7) / MathLib::faculty(7) + MathLib::pow(result, 9) / MathLib::faculty(9);
	

	//works wenn angle was multiplied with toDeg
	if ((int)angleRad % 360 > 180) {
		result *= -1;

	}

	return MathLib::floor(result, 4);
}
double MathLib::Cos(const double& angle) {
	
	double angleRad = angle * toRad;
	double result = ((int)angleRad % 180) + MathLib::fract(angleRad);
	result *= toDeg;
	result = (double)1 - (MathLib::pow(result, 2) / MathLib::faculty(2)) + (MathLib::pow(result, 4) / MathLib::faculty(4)) - (MathLib::pow(result, 6) / MathLib::faculty(6)) + (MathLib::pow(result, 8) / MathLib::faculty(8));
	/*if ((int)(angle) % 270 > 90) {
		result = ((result*result)/result)* -1;
	}else
	{
		result = ((result*result)/result);
	}*/



	return MathLib::floor(result, 4);
}
double MathLib::Tan(const double& angle) {

	return MathLib::floor(MathLib::Sin(angle) / MathLib::Cos(angle), 4);
}

double MathLib::ArcSin(const double& angle) {

	return 3.3;
}
double MathLib::ArcCos(const double& angle) {

	return 3.3;
}
double MathLib::ArcTan(const double& angle) {
	//TODO

	short size = (int)angle % 180;
	double result = size + MathLib::fract(angle);
	result *= toDeg;
	result = result - (MathLib::pow(result, 3) * 1 / 3) + (MathLib::pow(result, 5) * 1 / 5) - (MathLib::pow(result, 7) * 1 / 7) + (MathLib::pow(result, 9) * 1 / 9);
	result *= MathLib::sign(size);

	return MathLib::floor(result, 4);
}

double MathLib::pow(const double& base, const double& exponent)
{
	double result = 1;
	for (int i = 0; i < exponent; ++i)
	{
		result *= base;
	}

	return result;
}
std::size_t MathLib::faculty(const std::size_t& value)
{
	if (value < 0) {
		throw std::out_of_range("no negativ faculty");
	}
	std::size_t result = 1;

	for (std::size_t i = 2; i <= value; ++i)
	{
		result *= i;
	}

	return result;
}
double MathLib::fract(const double& value)
{
	return value - (int)value;
}

double MathLib::round(const double& value, const int& position)
{
	double temp = value * MathLib::pow(10, position + 1);
	temp = static_cast<int>(temp);
	temp -= static_cast<int>(value * MathLib::pow(10, position)) * 10;

	if (temp > 4)
	{
		return MathLib::ceil(value, position);
	}
	else
	{
		return MathLib::floor(value, position);
	}
}
double MathLib::floor(const double& value, const int& position)
{
	double temp = value * MathLib::pow(10, position);
	temp = static_cast<int>(temp);
	temp *= 10;
	temp /= MathLib::pow(10, position + 1);

	return temp;
}
double MathLib::ceil(const double& value, const int& position)
{
	double temp = value * MathLib::pow(10, position);
	temp = static_cast<int>(temp);
	temp *= 10;
	temp += 10;
	temp /= MathLib::pow(10, position + 1);

	return temp;
}

int  MathLib::sign(const float& value)
{
	//return (value > 0) - (value < 0);
	return (value > 0) ? 1 : ((value < 0) ? -1 : 0);
}





