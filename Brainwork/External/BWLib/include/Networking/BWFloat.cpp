#include "BWFloat.h"
#include "../Math/BWMath.h"
#include <bitset>

struct SplittetInt
{
	int m_value;
	int m_valueLength;
};


unsigned int BWFloat::getSign(const BWFloat& p_BWFloat)
{
	//false = + = 0
	//true  = - = 1
	return (p_BWFloat.m_value >> 31) << 31;
}
unsigned int BWFloat::getExponent(const BWFloat& p_BWFloat)
{
	return ((p_BWFloat.m_value << 1) >> 24);
}
unsigned int BWFloat::getMantissa(const BWFloat& p_BWFloat)
{
	return ((p_BWFloat.m_value << 9) >> 9);
}

BWFloat::BWFloat() {}
BWFloat::BWFloat(const unsigned int& p_value)
{
	m_value = p_value;
}
BWFloat::BWFloat(std::string p_floatString)
{
	int sign = 0;
	int exponent = 127;
	int mantissa = 0;

	//pre prozess
	std::string overNull = "";
	std::string underNull = "";

	for (int i = 0; i < p_floatString.length(); ++i)
	{
		if (p_floatString[i] == '.')
		{
			++i;
			while (i < p_floatString.length())
			{
				underNull += p_floatString[i];
				++i;
			}
			break;
		}
		overNull += p_floatString[i];
	}

	//sign calculation
	if (overNull[0] == '-')
	{
		sign = 1 << 31;
		overNull.erase(0, 1);
	}

	//mantissa calculation pre kommata
	int maxBitsForComata = 0;
	if (p_floatString != "" && p_floatString != "0") {
		std::bitset<129> mantisseBitSet;
		const unsigned int preCommaLength = (static_cast<unsigned int>(overNull.length()) % 8 == 0) ? static_cast<unsigned int>(overNull.length()) / 8 : static_cast<unsigned int>(overNull.length()) / 8 + 1;
		SplittetInt* preCommaArray = new SplittetInt[preCommaLength];

		for (unsigned int i = 0; i < preCommaLength; ++i)
		{
			preCommaArray[i].m_value = std::stoi(overNull.substr(i * 8, 8));
			preCommaArray[i].m_valueLength = BWMath::countDigits(preCommaArray[i].m_value);
		}

		while (maxBitsForComata < 129)
		{
			bool oldplus5 = false;
			bool newplus5 = false;

			for (unsigned int i = 0; i < preCommaLength; ++i)
			{
				if (i == preCommaLength - 1)
				{
					if (preCommaArray[i].m_value % 2 == 1)
					{
						mantisseBitSet[maxBitsForComata] = 1;
					}
					preCommaArray[i].m_value = (preCommaArray[i].m_value / 2) + ((5 * static_cast<int>(BWMath::pow(10, preCommaArray[i].m_valueLength - 1)) * oldplus5));
					newplus5 = false;
				}
				else
				{
					if (preCommaArray[i].m_value % 2 == 1)
					{
						newplus5 = true;
					}
					preCommaArray[i].m_value = (preCommaArray[i].m_value / 2) + ((5 * static_cast<int>(BWMath::pow(10, preCommaArray[i].m_valueLength - 1)) * oldplus5));
				}
				oldplus5 = newplus5;
				newplus5 = false;
			}

			++maxBitsForComata;
			bool doBreake = true;
			for (unsigned  int i = 0; i < preCommaLength; ++i)
			{
				if (preCommaArray[i].m_value != 0)
				{
					doBreake = false;
					break;
				}
			}
			if (doBreake)
			{
				break;
			}
		}

		--maxBitsForComata;//because array starting at 0
		std::bitset<24> mantisseBitSetFinal;
		int forLoopLenght = (maxBitsForComata > 23) ? 23 : maxBitsForComata;
		for (int i = 0; i < forLoopLenght + 1; ++i)//to get the leading 24
		{
			mantisseBitSetFinal[23 - i] = mantisseBitSet[maxBitsForComata - i];
		}
		mantisseBitSetFinal[23] = 0;//to reset the leading 1
		mantissa |= (int)(mantisseBitSetFinal.to_ulong());
		exponent += maxBitsForComata;
	}
	else
	{
		return;
	}

	//mantissa calculation post kommata
	if (underNull != "") {

		const unsigned int postCommaLength = (static_cast<unsigned int>(underNull.length()) % 8 == 0) ? static_cast<unsigned int>(underNull.length()) / 8 : static_cast<unsigned int>(underNull.length()) / 8 + 1;
		int* postCommaArray = new int[postCommaLength];


		for (unsigned  int i = 0; i < postCommaLength; ++i)
		{
			postCommaArray[i] = std::stoi(underNull.substr(i * 8, 8));
			if (i == postCommaLength - 1)
			{
				postCommaArray[i] *= static_cast<int>(BWMath::pow(10, 8 - BWMath::countDigits(postCommaArray[i])));
			}
		}

		if (overNull == "0")
		{
			bool oneTime = false;
			while (maxBitsForComata > -129)
			{
				for (int i = postCommaLength - 1; i > -1; --i)
				{
					postCommaArray[i] += postCommaArray[i];
					if (BWMath::countDigits(postCommaArray[i]) == 9)
					{
						postCommaArray[i] -= 100000000;
						if (i == 0)
						{
							if (!oneTime)
							{
								oneTime = true;
								exponent += maxBitsForComata - 1;
								maxBitsForComata = 23;
							}
							else
							{
								int tempint = 1 << maxBitsForComata;
								mantissa |= tempint;
							}
						}
						else
						{
							++postCommaArray[i - 1];
						}
					}
				}
				--maxBitsForComata;

				if (oneTime == true && maxBitsForComata == 0)
				{
					break;
				}
				bool doBreake = true;
				for (unsigned int i = 0; i < postCommaLength; ++i)
				{
					if (postCommaArray[i] != 0)
					{
						doBreake = false;
						break;
					}
				}
				if (doBreake)
				{
					break;
				}

			}
		}
		else
		{

			maxBitsForComata = 23 - (exponent - 127);

			while (maxBitsForComata > 0)
			{
				for (int i = postCommaLength - 1; i > -1; --i)
				{
					postCommaArray[i] += postCommaArray[i];
					if (BWMath::countDigits(postCommaArray[i]) == 9)
					{
						postCommaArray[i] -= 100000000;
						if (i == 0)
						{
							int tempint = 1 << (maxBitsForComata - 1);
							mantissa |= tempint;
						}
						else
						{
							++postCommaArray[i - 1];
						}
					}
				}
				--maxBitsForComata;
				bool doBreake = true;
				for (unsigned int i = 0; i < postCommaLength; ++i)
				{
					if (postCommaArray[i] != 0)
					{
						doBreake = false;
						break;
					}
				}
				if (doBreake)
				{
					break;
				}

			}
		}
	}

	exponent = exponent << 23;

	m_value |= sign;
	m_value |= exponent;
	m_value |= mantissa;

	std::bitset<32> y((m_value));
	std::cout << y << std::endl;
}
BWFloat::BWFloat(const BWFloat& p_bwFloat)
{
	this->m_value = p_bwFloat.m_value;
}
BWFloat::~BWFloat()
{
}

BWFloat BWFloat::maxValue()
{
	return BWFloat(2139095040);//01111111100000000000000000000000
}
BWFloat BWFloat::minValue()
{
	return BWFloat(4286578688);//11111111100000000000000000000000
}
BWFloat BWFloat::zero()
{
	return BWFloat(0);
}

bool BWFloat::equalZero(const BWFloat& p_BWFloat)
{
	return (p_BWFloat.m_value == 0 || p_BWFloat.m_value == 2147483648) ? true : false; // 2147483648 == -0
}

#pragma region castOperations
BWFloat::operator BWDouble()
{
	return BWDouble();
}
BWFloat::operator int()
{
	if (BWFloat::getExponent(*this) - 127 > 30)
	{
		return ((BWFloat::getSign(*this) == 0) ? 1 : -1) * 2147483647;// max int number
	}
	else if (BWFloat::getExponent(*this) - 127 < 0)
	{
		return 0;
	}

	return ((BWFloat::getSign(*this) == 0) ? 1 : -1) * ((int)(BWFloat::getExponent(*this) - 127 > 23 ) ? (BWFloat::getMantissa(*this) | 1 << 23) << ((BWFloat::getExponent(*this) - 127) - 23) : (BWFloat::getMantissa(*this) | 1 << 23) >> (23 - (BWFloat::getExponent(*this) - 127)));
}
BWFloat::operator unsigned int()
{
	if (BWFloat::getExponent(*this) - 127 > 31)
	{
		return 4294967295;// max int number
	}
	else if (BWFloat::getExponent(*this) - 127 < 0)
	{
		return 0;
	}
	return (int)(BWFloat::getExponent(*this) - 127 > 23) ? (BWFloat::getMantissa(*this) | 1 << 23) << ((BWFloat::getExponent(*this) - 127) - 23) : (BWFloat::getMantissa(*this) | 1 << 23) >> (23 - (BWFloat::getExponent(*this) - 127));
}
#pragma endregion

#pragma region arithmeticOperations
void BWFloat::operator=(const BWFloat& p_BWFloat)
{
	m_value = p_BWFloat.m_value;
}
BWFloat BWFloat::operator-()
{
	return BWFloat(m_value ^ (1 << 31));
}

BWFloat& BWFloat::operator+=(const BWFloat& p_BWFloat)
{
	*this = *this + p_BWFloat;
	return *this;
}
BWFloat& BWFloat::operator-=(const BWFloat& p_BWFloat)
{
	*this = *this - p_BWFloat;
	return *this;
}
BWFloat& BWFloat::operator*=(const BWFloat& p_BWFloat)
{
	*this = *this * p_BWFloat;
	return *this;
}
BWFloat& BWFloat::operator/=(const BWFloat& p_BWFloat)
{
	*this = *this / p_BWFloat;
	return *this;
}
BWFloat BWFloat::operator+(const BWFloat& p_BWFloat)
{
	bool endSign = 0;
	if (BWFloat::getSign(p_BWFloat) != 0)
	{
		if (BWFloat::getSign(*this) != 0)
		{
			endSign = 1;
		}
		else
		{
			return BWFloat::operator-(p_BWFloat);
		}
	}
	else if (BWFloat::getSign(*this) != 0)
	{
		return BWFloat(p_BWFloat).operator-(*this);
	}

	std::bitset<32> result;
	if (BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat))
	{
		result = (BWFloat::getMantissa(*this) | 1 << 23) + ((BWFloat::getMantissa(p_BWFloat) | 1 << 23) >> static_cast<unsigned int>(BWMath::abs(static_cast<int>(BWFloat::getExponent(*this))) - static_cast<int>(BWFloat::getExponent(p_BWFloat))));
	}
	else
	{
		result = ((BWFloat::getMantissa(*this) | 1 << 23) >> static_cast<unsigned int>(BWMath::abs(static_cast<int>(BWFloat::getExponent(*this))) - static_cast<int>(BWFloat::getExponent(p_BWFloat)))) + (BWFloat::getMantissa(p_BWFloat) | 1 << 23);
	}

	if (result[24] == 1) {
		result = result >> 1;
		result[23] = 0;
		result |= (BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat)) ? (BWFloat::getExponent(*this) + 1) << 23 : (BWFloat::getExponent(p_BWFloat) + 1) << 23;
	}
	else {
		result[23] = 0;
		result |= (BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat)) ? BWFloat::getExponent(*this) << 23 : BWFloat::getExponent(p_BWFloat) << 23;
	}
	result |= endSign << 31;

	return BWFloat(m_value = static_cast<int>(result.to_ulong()));
}
BWFloat BWFloat::operator-(const BWFloat& p_BWFloat)
{
	if (BWFloat::getSign(*this) != 0)
	{
		if (BWFloat::getSign(p_BWFloat) != 0)
		{
			if (*this > p_BWFloat)//both under zero(e.g. (-x)-(-y), (-4)-(-8))
			{
				return (-BWFloat(p_BWFloat)).operator-(-BWFloat(*this)); //(y) - (x), (8)-(4)
			}
			else
			{
				return (-BWFloat(*this)).operator-(-BWFloat(p_BWFloat)); //(x) - (y)
			}
		}
		else
		{
			return this->operator+(-BWFloat(p_BWFloat));
		}
	}
	else
	{
		if (BWFloat::getSign(p_BWFloat) != 0)
		{
			return this->operator+(-BWFloat(p_BWFloat));
		}
		else
		{
			if (*this > p_BWFloat || this->m_value == p_BWFloat.m_value)
			{

			}
			else
			{
				if (BWFloat::equalZero(*this) && BWFloat::equalZero(p_BWFloat))
				{
					return p_BWFloat;
				}
				return -(BWFloat(p_BWFloat).operator-(*this));
			}
		}
	}

	std::bitset<32> result;
	if (BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat))
	{
		result = (BWFloat::getMantissa(*this) | 1 << 23) - ((BWFloat::getMantissa(p_BWFloat) | 1 << 23) >> static_cast<unsigned int>(BWMath::abs(static_cast<int>(BWFloat::getExponent(*this))) - static_cast<int>(BWFloat::getExponent(p_BWFloat))));
	}
	else
	{
		result = ((BWFloat::getMantissa(*this) | 1 << 23) >> static_cast<unsigned int>(BWMath::abs(static_cast<int>(BWFloat::getExponent(*this))) - static_cast<int>(BWFloat::getExponent(p_BWFloat)))) - (BWFloat::getMantissa(p_BWFloat) | 1 << 23);
	}

	int counter = 0;
	while (result[23] == 0)
	{
		result = result << 1;
		++counter;
		if (counter == 23)
		{
			return BWFloat(0);
		}
	}
	result[23] = 0;
	result |= (BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat)) ? (BWFloat::getExponent(*this) - counter) << 23 : (BWFloat::getExponent(p_BWFloat) - counter) << 23;

	return BWFloat(m_value = static_cast<int>(result.to_ulong()));
}
BWFloat BWFloat::operator*(const BWFloat& p_BWFloat)
{
	//zero check
	if (BWFloat::equalZero(*this) || BWFloat::equalZero(p_BWFloat))
	{
		return BWFloat::zero();
	}

	//sign
	unsigned int endSign = 0;
	if (BWFloat::getSign(*this) != 0 && BWFloat::getSign(p_BWFloat) != 0)
	{
	}
	else if (BWFloat::getSign(*this) != 0 || BWFloat::getSign(p_BWFloat) != 0)
	{
		std::cout << "sign1 " << std::endl;
		endSign = 1;
	}
	unsigned int tempValue = (endSign << 31);
	std::cout << "sign " << std::bitset<32>(tempValue) << std::endl;


	//exponent
	if (std::bitset<32>(((int)BWFloat::getExponent(*this) + (int)BWFloat::getExponent(p_BWFloat)) - 127)[8] == 1)
	{
		return BWFloat::maxValue();
	}
	tempValue |= (((int)BWFloat::getExponent(*this) + (int)BWFloat::getExponent(p_BWFloat)) - 127) << 23;
	std::cout << "exponent " << std::bitset<32>(tempValue) << std::endl;


	//mantissa
	unsigned int tempMantissa1 = BWFloat::getMantissa(*this) | (1 << 23);
	unsigned int tempMantissa2 = BWFloat::getMantissa(p_BWFloat) | (1 << 23);


	unsigned long long int tempMantissa = static_cast<unsigned long long int>(tempMantissa1) * static_cast<unsigned long long int>(tempMantissa2);
	for (int i = 0; i < 24; ++i)//until first bit of exponent
	{
		if (std::bitset<64>(tempMantissa)[47 - i] == 1)
		{
			tempMantissa = tempMantissa >> 1;
		}
	}
	std::bitset<32>tempBitset(tempMantissa);
	tempBitset[23] = 0;

	tempValue |= tempBitset.to_ulong();

	std::cout << "all" << std::bitset<32>(tempValue) << std::endl;
	return BWFloat(tempValue);

}
BWFloat BWFloat::operator/(const BWFloat& p_BWFloat)
{
	unsigned int tempValue = 0;

	//zero check
	if (BWFloat::equalZero(*this))
	{
		return BWFloat::zero();
	}
	else if (BWFloat::equalZero(p_BWFloat))
	{
		throw std::logic_error("You try to dividing by zero !");
	}

	//sign
	if (BWFloat::getSign(*this) != 0 && BWFloat::getSign(p_BWFloat) != 0)
	{
	}
	else if (BWFloat::getSign(*this) != 0 || BWFloat::getSign(p_BWFloat) != 0)
	{
		tempValue = (1 << 31);
	}

	//exponent
	if ((((int)BWFloat::getExponent(*this) - (int)BWFloat::getExponent(p_BWFloat)) + 127) >= 255)
	{
		if (tempValue == 0)
		{
			return BWFloat::maxValue();
		}
		else
		{
			return BWFloat::minValue();
		}
	}
	else
	{
		tempValue |= (((int)BWFloat::getExponent(*this) - (int)BWFloat::getExponent(p_BWFloat)) + 127) << 23;
	}

	//mantissa
	unsigned long long tempMantissa1 = BWFloat::getMantissa(*this) | (1 << 23);
	unsigned long long tempMantissa2 = BWFloat::getMantissa(p_BWFloat) | (1 << 23);

	while (std::bitset<24>(tempMantissa1 / tempMantissa2)[23] != 1)
	{
		tempMantissa1 = tempMantissa1 << 1;
	}

	tempValue |= ((unsigned int)((tempMantissa1 / tempMantissa2) << 9)) >> 9;

	return BWFloat(tempValue);
}

BWDouble BWFloat::operator+(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator-(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator*(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator/(const BWDouble& p_BWDouble)
{
	return BWDouble();
}

BWFloat& BWFloat::operator+=(const int& p_int)
{
	*this = *this + p_int;
	return *this;
}
BWFloat& BWFloat::operator-=(const int& p_int)
{
	*this = *this - p_int;
	return *this;
}
BWFloat& BWFloat::operator*=(const int& p_int)
{
	*this = *this * p_int;
	return *this;
}
BWFloat& BWFloat::operator/=(const int& p_int)
{
	*this = *this / p_int;
	return *this;
}
BWFloat BWFloat::operator+(const int& p_int)
{
	return BWFloat();
}
BWFloat BWFloat::operator-(const int& p_int)
{
	return BWFloat();
}
BWFloat BWFloat::operator*(const int& p_int)
{
	return BWFloat();
}
BWFloat BWFloat::operator/(const int& p_int)
{
	return BWFloat();
}

BWFloat& BWFloat::operator+=(const float& p_float)
{
	*this = *this + p_float;
	return *this;
}
BWFloat& BWFloat::operator-=(const float& p_float)
{
	*this = *this - p_float;
	return *this;
}
BWFloat& BWFloat::operator*=(const float& p_float)
{
	*this = *this * p_float;
	return *this;
}
BWFloat& BWFloat::operator/=(const float& p_float)
{
	*this = *this / p_float;
	return *this;
}
BWFloat BWFloat::operator+(const float& p_float)
{
	return BWFloat();
}
BWFloat BWFloat::operator-(const float& p_float)
{
	return BWFloat();
}
BWFloat BWFloat::operator*(const float& p_float)
{
	return BWFloat();
}
BWFloat BWFloat::operator/(const float& p_float)
{
	return BWFloat();
}

BWFloat& BWFloat::operator+=(const double& p_double)
{
	*this = *this + p_double;
	return *this;
}
BWFloat& BWFloat::operator-=(const double& p_double)
{
	*this = *this - p_double;
	return *this;
}
BWFloat& BWFloat::operator*=(const double& p_double)
{
	*this = *this * p_double;
	return *this;
}
BWFloat& BWFloat::operator/=(const double& p_double)
{
	*this = *this / p_double;
	return *this;
}
BWFloat BWFloat::operator+(const double& p_double)
{
	return BWFloat();
}
BWFloat BWFloat::operator-(const double& p_double)
{
	return BWFloat();
}
BWFloat BWFloat::operator*(const double& p_double)
{
	return BWFloat();
}
BWFloat BWFloat::operator/(const double& p_double)
{
	return BWFloat();
}

#pragma endregion

#pragma region comparisonOperator
bool BWFloat::operator==(const BWFloat&  p_BWFloat)
{
	return (p_BWFloat.m_value == this->m_value) ? true : false;
}
bool BWFloat::operator!=(const BWFloat&  p_BWFloat)
{
	return (p_BWFloat.m_value != this->m_value) ? true : false;
}
bool BWFloat::operator>(const BWFloat&  p_BWFloat)
{
	if (BWFloat::getSign(*this) == BWFloat::getSign(p_BWFloat))
	{
		if (BWFloat::getExponent(*this) == BWFloat::getExponent(p_BWFloat))
		{
			if (BWFloat::getMantissa(*this) == BWFloat::getMantissa(p_BWFloat))
			{
				return false;
			}
			else
			{
				return(BWFloat::getMantissa(*this) > BWFloat::getMantissa(p_BWFloat)) ? true : false;
			}
		}
		else
		{
			return(BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat)) ? true : false;
		}
	}
	else
	{
		return (BWFloat::getExponent(*this) == 0 && BWFloat::getExponent(p_BWFloat) == 0) ? false : (BWFloat::getSign(*this) == 0) ? true : false;
		//if (-0 && 0) = false ,else (leftValue == positiv) = true, else false;
	}
}
bool BWFloat::operator>=(const BWFloat& p_BWFloat)
{
	if (BWFloat::getSign(*this) == BWFloat::getSign(p_BWFloat))
	{
		if (BWFloat::getExponent(*this) == BWFloat::getExponent(p_BWFloat))
		{
			if (BWFloat::getMantissa(*this) == BWFloat::getMantissa(p_BWFloat))
			{
				return true;
			}
			else
			{
				return(BWFloat::getMantissa(*this) > BWFloat::getMantissa(p_BWFloat)) ? true : false;
			}
		}
		else
		{
			return(BWFloat::getExponent(*this) > BWFloat::getExponent(p_BWFloat)) ? true : false;
		}
	}
	else
	{
		return (BWFloat::getExponent(*this) == 0 && BWFloat::getExponent(p_BWFloat) == 0) ? true : (BWFloat::getSign(*this) == 0) ? true : false;
		//if (-0 && 0) = false ,else (leftValue == positiv) = true, else false;
	}
}
bool BWFloat::operator<(const BWFloat&  p_BWFloat)
{
	if (BWFloat::getSign(*this) == BWFloat::getSign(p_BWFloat))
	{
		if (BWFloat::getExponent(*this) == BWFloat::getExponent(p_BWFloat))
		{
			if (BWFloat::getMantissa(*this) == BWFloat::getMantissa(p_BWFloat))
			{
				return false;
			}
			else
			{
				return(BWFloat::getMantissa(*this) < BWFloat::getMantissa(p_BWFloat)) ? true : false;
			}
		}
		else
		{
			return(BWFloat::getExponent(*this) < BWFloat::getExponent(p_BWFloat)) ? true : false;
		}
	}
	else
	{
		return (BWFloat::getExponent(*this) == 0 && BWFloat::getExponent(p_BWFloat) == 0) ? false : (BWFloat::getSign(*this) != 0) ? true : false;
		//if (-0 && 0) = false ,else (leftValue == positiv) = true, else false;
	}
}
bool BWFloat::operator<=(const BWFloat& p_BWFloat)
{
	if (BWFloat::getSign(*this) == BWFloat::getSign(p_BWFloat))
	{
		if (BWFloat::getExponent(*this) == BWFloat::getExponent(p_BWFloat))
		{
			if (BWFloat::getMantissa(*this) == BWFloat::getMantissa(p_BWFloat))
			{
				return true;
			}
			else
			{
				return(BWFloat::getMantissa(*this) < BWFloat::getMantissa(p_BWFloat)) ? true : false;
			}
		}
		else
		{
			return(BWFloat::getExponent(*this) < BWFloat::getExponent(p_BWFloat)) ? true : false;
		}
	}
	else
	{
		return (BWFloat::getExponent(*this) == 0 && BWFloat::getExponent(p_BWFloat) == 0) ? true : (BWFloat::getSign(*this) != 0) ? true : false;
		//if (-0 && 0) = false ,else (leftValue == positiv) = true, else false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& output, BWFloat& p_BWFloat)
{
	output << "Output not finished yet";
	return output;
}

std::ostream& operator<<(std::ostream&  output, BWFloat p_BWFloat)
{
	output << "Output not finished yet";
	return output;
}
