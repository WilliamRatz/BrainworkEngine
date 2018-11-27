//
//  Vector2.cpp
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#include "Vector2.h"
#include "BW_Math.h"


Vector2::Vector2()
{
	vec2[0] = NULL;
	vec2[1] = NULL;
}

Vector2::Vector2(float p_x, float p_y)
{
	vec2[0] = p_x;
	vec2[1] = p_y;
}

Vector2::Vector2(const Vector2& vec)
{
	vec2 = vec.vec2;
}

#pragma region Methods

void Vector2::normalize()
{
	vec2[0] /= Vector2::length(*this);
	vec2[1] /= Vector2::length(*this);
	vec2[2] /= Vector2::length(*this);
}

int Vector2::getHashCode() {
	int hash = 17;

	hash *= (23 + std::hash<float>()(vec2[0]));
	hash *= (23 + std::hash<float>()(vec2[1]));

	return hash;
}

Vector2 Vector2::normalized(const Vector2& vec) {

	return Vector2(Vector2::x(vec) / Vector2::length(vec), Vector2::y(vec) / Vector2::length(vec));
}
float Vector2::length(const Vector2& vec)
{
	return static_cast<float>(MathLib::Sqrt(MathLib::pow(Vector2::x(vec), 2) + MathLib::pow(Vector2::y(vec), 2)));
}
float  Vector2::dot(const Vector2& vec1, const Vector2& vec2)
{
	return Vector2::x(vec1) * Vector2::x(vec2) + Vector2::y(vec1) * Vector2::y(vec2);
}

Vector2 Vector2::One()
{
	return Vector2(1, 1);
}
Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}
Vector2 Vector2::Up()
{
	return Vector2(0, 1);
}
Vector2 Vector2::Down()
{
	return Vector2(0, -1);
}
Vector2 Vector2::Left()
{
	return Vector2(-1, 0);
}
Vector2 Vector2::Right()
{
	return Vector2(1, 0);
}

#pragma endregion

#pragma region arithmeticOperator

void Vector2::operator=(const Vector2& vec) {

	vec2[0] = vec.vec2[0];
	vec2[1] = vec.vec2[1];
}
Vector2 Vector2::operator+(const Vector2& vec) {

	Vector2 temp(*this);
	return temp -= vec;
}
Vector2 Vector2::operator-(const Vector2& vec) {

	Vector2 temp(*this);
	return temp -= vec;
}
Vector2 Vector2::operator/(const Vector2& vec) {

	Vector2 temp(*this);
	return temp -= vec;
}
Vector2& Vector2::operator+=(const Vector2& vec) {
	vec2[0] = vec2[0] + vec.vec2[0];
	vec2[1] = vec2[1] + vec.vec2[1];

	return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec) {
	vec2[0] = vec2[0] - vec.vec2[0];
	vec2[1] = vec2[1] - vec.vec2[1];

	return *this;
}
Vector2& Vector2::operator/=(const Vector2& vec) {
	vec2[0] = vec2[0] / vec.vec2[0];
	vec2[1] = vec2[1] / vec.vec2[1];

	return *this;
}

Vector2& Vector2::operator*=(const int& value)
{
	vec2[0] = vec2[0] * static_cast<float>(value);
	vec2[1] = vec2[1] * static_cast<float>(value);

	return *this;
}
Vector2& Vector2::operator/=(const int& value)
{
	vec2[0] = vec2[0] / static_cast<float>(value);
	vec2[1] = vec2[1] / static_cast<float>(value);

	return *this;
}
Vector2 Vector2::operator*(const int& value)
{
	Vector2 temp(*this);
	return temp *= value;
}
Vector2 Vector2::operator/(const int& value)
{
	Vector2 temp(*this);
	return temp /= value;
}

Vector2& Vector2::operator*=(const float& value)
{
	vec2[0] = vec2[0] * static_cast<float>(value);
	vec2[1] = vec2[1] * static_cast<float>(value);

	return *this;
}
Vector2& Vector2::operator/=(const float& value)
{
	vec2[0] = vec2[0] / static_cast<float>(value);
	vec2[1] = vec2[1] / static_cast<float>(value);

	return *this;
}
Vector2 Vector2::operator*(const float& value)
{
	Vector2 temp(*this);
	return temp *= value;
}
Vector2 Vector2::operator/(const float& value)
{
	Vector2 temp(*this);
	return temp /= value;
}

Vector2& Vector2::operator*=(const double& value)
{
	vec2[0] = vec2[0] * static_cast<float>(value);
	vec2[1] = vec2[1] * static_cast<float>(value);

	return *this;
}
Vector2& Vector2::operator/=(const double& value)
{
	vec2[0] = vec2[0] / static_cast<float>(value);
	vec2[1] = vec2[1] / static_cast<float>(value);

	return *this;
}
Vector2 Vector2::operator*(const double& value)
{
	Vector2 temp(*this);
	return temp *= value;
}
Vector2 Vector2::operator/(const double& value)
{
	Vector2 temp(*this);
	return temp /= value;
}

#pragma endregion

#pragma region comparisonOperator

bool Vector2::operator==(Vector2& vec) {

	if (vec2[0] == vec.vec2[0] &&
		vec2[1] == vec.vec2[1]) {

		return true;
	}
	else {

		return false;
	}

}

bool Vector2::operator!=(Vector2& vec) {

	if (vec2[0] != vec.vec2[0] ||
		vec2[1] != vec.vec2[1]) {

		return true;
	}
	else {

		return false;
	}
}

#pragma endregion

std::ostream& operator<<(std::ostream& ausgabe, Vector2& a)
{
	ausgabe << '(' << a.x() << '/' << a.y() << ')';
	return ausgabe;
}
