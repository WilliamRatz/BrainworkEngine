//
//  Vector4.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector4_H
#define Vector4_H
#include "Vector.h"

class Vector2;
class Vector3;
class Quaternion;
template<typename T, std::size_t R, std::size_t C>
class Matrix;

class Vector4 {

private:
	Vector<float, 4> m_vec4;

public:

	static float x(Vector4 p_vec4) { return p_vec4.m_vec4[0]; } const
	static float y(Vector4 p_vec4) { return p_vec4.m_vec4[1]; } const
	static float z(Vector4 p_vec4) { return p_vec4.m_vec4[2]; } const
	static float w(Vector4 p_vec4) { return p_vec4.m_vec4[3]; } const

	float x() { return m_vec4[0]; }
	float y() { return m_vec4[1]; }
	float z() { return m_vec4[2]; }
	float w() { return m_vec4[3]; }

	void x(float p_x) { m_vec4[0] = p_x; }
	void y(float p_y) { m_vec4[1] = p_y; }
	void z(float p_z) { m_vec4[2] = p_z; }
	void w(float p_w) { m_vec4[3] = p_w; }

	Vector4();
	Vector4(float p_x, float p_y, float p_z, float p_w);
	Vector4(const Vector4&);

#pragma region Methods
	Vector4 normalize();
	unsigned int getHashCode();

	static Vector4 normalized(const Vector4&);
	static float length(const Vector4&);
	static float dot(const Vector4&, const Vector4&);

	static Vector4 One();
	static Vector4 Zero();
#pragma endregion

#pragma region castOperations
	operator Vector2();
	operator Vector3();
	operator Quaternion();
	operator Matrix<float, 4, 4>();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector4&);
	Vector4 operator-();

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
Vector4 operator*(Matrix<T, R, C>& p_mat, Vector4& p_vec4) {

	float a1 = p_mat[0][0] * (T)p_vec4.x() + p_mat[0][1] * (T)p_vec4.y() + p_mat[0][2] * (T)p_vec4.z() + p_mat[0][3] * (T)1;
	float a2 = p_mat[1][0] * (T)p_vec4.x() + p_mat[1][1] * (T)p_vec4.y() + p_mat[1][2] * (T)p_vec4.z() + p_mat[1][3] * (T)1;
	float a3 = p_mat[2][0] * (T)p_vec4.x() + p_mat[2][1] * (T)p_vec4.y() + p_mat[2][2] * (T)p_vec4.z() + p_mat[2][3] * (T)1;

	Vector4 a(a1, a2, a3);
	
	return a;
}

std::ostream& operator<<(std::ostream&, Vector4&);
std::ostream& operator<<(std::ostream&, Vector4);


#endif /* Vector4_h */