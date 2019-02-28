//
//  Vector4.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//

#ifndef Vector4_H
#define Vector4_H
#include "Vector.h"

template<typename T, std::size_t R, std::size_t C> class Matrix;

class Vector4 {

private:
	Vector<float, 4> vec4;

public:

	static float x(Vector4 vec) { return vec.vec4[0]; } const
	static float y(Vector4 vec) { return vec.vec4[1]; } const
	static float z(Vector4 vec) { return vec.vec4[2]; } const
	static float w(Vector4 vec) { return vec.vec4[3]; } const

	float x() { return vec4[0]; }
	float y() { return vec4[1]; }
	float z() { return vec4[2]; }
	float w() { return vec4[3]; }

	void x(float p_x) { vec4[0] = p_x; }
	void y(float p_y) { vec4[1] = p_y; }
	void z(float p_z) { vec4[2] = p_z; }
	void w(float p_w) { vec4[3] = p_w; }

	Vector4();
	Vector4(float p_x, float p_y, float p_z, float p_w);
	Vector4(const Vector4&);

#pragma region Methods

	Vector4 normalize();
	std::size_t getHashCode();

	static Vector4 normalized(const Vector4&);
	static float length(const Vector4&);
	static float dot(const Vector4&, const Vector4&);

	static Vector4 One();
	static Vector4 Zero();

#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector4&);
	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator/=(const Vector4&);
	Vector4	operator+(const Vector4&);
	Vector4	operator-(const Vector4&);
	Vector4	operator/(const Vector4&);
	
	Vector4& operator*=(const int&);
	Vector4& operator/=(const int&);
	Vector4  operator*(const int&);
	Vector4  operator/(const int&);
	
	Vector4& operator*=(const float&);
	Vector4& operator/=(const float&);
	Vector4	operator*(const float&);
	Vector4	operator/(const float&);
	
	Vector4& operator*=(const double&);
	Vector4& operator/=(const double&);
	Vector4  operator*(const double&);
	Vector4  operator/(const double&);

#pragma endregion

#pragma region comparisonOperator
	bool operator==(Vector4&);
	bool operator!=(Vector4&);
#pragma endregion

};

template<typename T, std::size_t R, std::size_t C>
Vector4 operator*(Matrix<T, R, C>& mat, Vector4& vec) {

	float a1 = mat[0][0] * (T)vec.x() + mat[0][1] * (T)vec.y() + mat[0][2] * (T)vec.z() + mat[0][3] * (T)1;
	float a2 = mat[1][0] * (T)vec.x() + mat[1][1] * (T)vec.y() + mat[1][2] * (T)vec.z() + mat[1][3] * (T)1;
	float a3 = mat[2][0] * (T)vec.x() + mat[2][1] * (T)vec.y() + mat[2][2] * (T)vec.z() + mat[2][3] * (T)1;

	Vector4 a(a1, a2, a3);
	
	return a;
}

std::ostream& operator<<(std::ostream&, Vector4&);

#endif /* Vector4_h */
