//
//  Vector2.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Vector2_H
#define Vector2_H
#include "Vector.h"
#include "Matrix.h"

class Vector2 {
private:
	Vector<float, 2> vec2;

public:

	static float x(Vector2 vec) { return vec.vec2[0]; } const
	static float y(Vector2 vec) { return vec.vec2[1]; } const

	float x() { return vec2[0]; }
	float y() { return vec2[1]; }

	void x(float p_x) { vec2[0] = p_x; }
	void y(float p_y) { vec2[1] = p_y; }

	Vector2();
	Vector2(float p_x, float p_y);
	Vector2(const Vector2&);

#pragma region Methods

	void normalize();
	std::size_t getHashCode();

	static Vector2 normalized(const Vector2&);
	static float length(const Vector2&);
	static float dot(const Vector2&, const Vector2&);

	static Vector2 One();
	static Vector2 Zero();

#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector2&);
	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator/=(const Vector2&);
	Vector2 operator+(const Vector2&);
	Vector2 operator-(const Vector2&);
	Vector2 operator/(const Vector2&);
	
	Vector2& operator*=(const int&);
	Vector2& operator/=(const int&);
	Vector2 operator*(const int&);
	Vector2 operator/(const int&);
	
	Vector2& operator*=(const float&);
	Vector2& operator/=(const float&);
	Vector2 operator*(const float&);
	Vector2 operator/(const float&);
	
	Vector2& operator*=(const double&);
	Vector2& operator/=(const double&);
	Vector2 operator*(const double&);
	Vector2 operator/(const double&);
#pragma endregion

#pragma region comparisonOperator
	bool operator==(Vector2&);
	bool operator!=(Vector2&);
#pragma endregion
};

template<typename T, std::size_t M, std::size_t N>
Vector2 operator*(Matrix<T, M, N>& mat, Vector2& vec) {

	float a1 = mat[0][0] * (T)vec.x() + mat[0][1] * (T)vec.y() + mat[0][2] * (T)1;
	float a2 = mat[1][0] * (T)vec.x() + mat[1][1] * (T)vec.y() + mat[1][2] * (T)1;
		
	Vector2 a(a1, a2);												   

	return a;
}

std::ostream& operator<<(std::ostream&, Vector2&);


#endif /* Vector2_h */
