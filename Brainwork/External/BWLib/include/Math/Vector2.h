//
//  Vector2.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector2_H
#define Vector2_H
#include "Vector.h"

class Vector3;
class Vector4;
class Quaternion;
template<typename T, std::size_t R, std::size_t C>
class Matrix;

class Vector2 {
private:
	Vector<float, 2> m_vec2;

public:

	static float x(Vector2 p_vec2) { return p_vec2.m_vec2[0]; } const
	static float y(Vector2 p_vec2) { return p_vec2.m_vec2[1]; } const

	float x() { return m_vec2[0]; }
	float y() { return m_vec2[1]; }

	void x(float p_x) { m_vec2[0] = p_x; }
	void y(float p_y) { m_vec2[1] = p_y; }

	Vector2();
	Vector2(float p_x, float p_y);
	Vector2(const Vector2&);

#pragma region Methods
	void normalize();
	unsigned int getHashCode();

	static Vector2 normalized(const Vector2&);
	static float length(const Vector2&);
	static float dot(const Vector2&, const Vector2&);

	static Vector2 One();
	static Vector2 Zero();
#pragma endregion

#pragma region castOperations
	operator Vector3();
	operator Vector4();
	operator Quaternion();
	operator Matrix<float, 4, 4>();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector2&);
	Vector2 operator-();

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
Vector2 operator*(Matrix<T, M, N>& p_mat, Vector2& p_vec2) {

	float a1 = p_mat[0][0] * (T)p_vec2.x() + p_mat[0][1] * (T)p_vec2.y() + p_mat[0][2] * (T)1;
	float a2 = p_mat[1][0] * (T)p_vec2.x() + p_mat[1][1] * (T)p_vec2.y() + p_mat[1][2] * (T)1;
		
	Vector2 a(a1, a2);												   

	return a;
}

std::ostream& operator<<(std::ostream&, Vector2&);
std::ostream& operator<<(std::ostream&, Vector2);


#endif /* Vector2_h */
