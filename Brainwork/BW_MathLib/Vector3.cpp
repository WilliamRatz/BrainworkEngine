//
//  Vector3.cpp
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#include "Vector3.h"
#include "BW_Math.h"



Vector3::Vector3()
{
	vec3[0] = NULL;
	vec3[1] = NULL;
	vec3[2] = NULL;
}

Vector3::Vector3(float p_x, float p_y, float p_z)
{
	vec3[0] = p_x;
	vec3[1] = p_y;
	vec3[2] = p_z;
}

Vector3::Vector3(const Vector3& vec)
{
	vec3 = vec.vec3;
}

#pragma region Methods

void Vector3::normalize()
{
	vec3[0] /= Vector3::length(*this);
	vec3[1] /= Vector3::length(*this);
	vec3[2] /= Vector3::length(*this);
}

float Vector3::length(const Vector3& vec)
{
	return static_cast<float>(MathLib::Sqrt(MathLib::pow(Vector3::x(vec), 2) + MathLib::pow(Vector3::y(vec), 2) + MathLib::pow(Vector3::z(vec), 2)));
}
float  Vector3::dot(const Vector3& vec1, const Vector3& vec2)
{
	return Vector3::x(vec1) * Vector3::x(vec2) + Vector3::y(vec1) * Vector3::y(vec2) + Vector3::z(vec1) * Vector3::z(vec2);
}
Vector3  Vector3::cross(const Vector3& vec1, const Vector3& vec2)
{

	return Vector3((Vector3::y(vec1) * Vector3::z(vec2)) - (Vector3::z(vec1) * Vector3::y(vec2)),
		(Vector3::z(vec1) * Vector3::x(vec2)) - (Vector3::x(vec1) * Vector3::z(vec2)),
		(Vector3::x(vec1) * Vector3::y(vec2)) - (Vector3::y(vec1) * Vector3::x(vec2)));
}
Vector3 Vector3::normalized(const Vector3& vec) {

	return Vector3(Vector3::x(vec) / Vector3::length(vec), Vector3::y(vec) / Vector3::length(vec), Vector3::z(vec) / Vector3::length(vec));
}

Vector3  Vector3::One()
{
	return Vector3(1, 1, 1);
}
Vector3  Vector3::Zero()
{
	return Vector3(0, 0, 0);
}
Vector3  Vector3::Up()
{
	return Vector3(0, 1, 0);
}
Vector3  Vector3::Down()
{
	return Vector3(0, -1, 0);
}
Vector3  Vector3::Left()
{
	return Vector3(-1, 0, 0);
}
Vector3  Vector3::Right()
{
	return Vector3(1, 0, 0);
}

#pragma endregion


#pragma region arithmeticOperator

void Vector3::operator=(const Vector3& vec) {

	vec3[0] = vec.vec3[0];
	vec3[1] = vec.vec3[1];
	vec3[2] = vec.vec3[2];
}
inline Vector3& Vector3::operator+=(const Vector3& vec) {
	vec3[0] = vec3[0] + vec.vec3[0];
	vec3[1] = vec3[1] + vec.vec3[1];
	vec3[2] = vec3[2] + vec.vec3[2];

	return *this;
}
inline Vector3& Vector3::operator-=(const Vector3& vec) {
	vec3[0] = vec3[0] - vec.vec3[0];
	vec3[1] = vec3[1] - vec.vec3[1];
	vec3[2] = vec3[2] - vec.vec3[2];

	return *this;
}
inline Vector3& Vector3::operator/=(const Vector3& vec) {
	vec3[0] = vec3[0] / vec.vec3[0];
	vec3[1] = vec3[1] / vec.vec3[1];
	vec3[2] = vec3[2] / vec.vec3[2];

	return *this;
}
inline Vector3 Vector3::operator+(const Vector3& vec) {

	Vector3 temp(*this);
	return temp += vec;
}
inline Vector3 Vector3::operator-(const Vector3& vec) {

	Vector3 temp(*this);
	return temp -= vec;
}
inline Vector3 Vector3::operator/(const Vector3& vec) {

	Vector3 temp(*this);
	return temp /= vec;
}

Vector3& Vector3::operator*=(const int& value)
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const int& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const int& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const int& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}

Vector3& Vector3::operator*=(const float& value) 
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const float& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const float& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const float& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}

Vector3& Vector3::operator*=(const double& value) 
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const double& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const double& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const double& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}

#pragma endregion

#pragma region comparisonOperator

bool Vector3::operator==(Vector3& vec) {

	if (vec3[0] == vec.vec3[0] &&
		vec3[1] == vec.vec3[1] &&
		vec3[2] == vec.vec3[2]) {

		return true;
	}
	else {

		return false;
	}

}

bool Vector3::operator!=(Vector3& vec) {

	if (vec3[0] != vec.vec3[0] ||
		vec3[1] != vec.vec3[1] ||
		vec3[2] != vec.vec3[2]) {

		return true;
	}
	else {

		return false;
	}
}

#pragma endregion

std::ostream& operator<<(std::ostream& ausgabe, Vector3& a)
{
	ausgabe << '(' << a.x() << '/' << a.y() << '/' << a.z() << ')';
	return ausgabe;
}

