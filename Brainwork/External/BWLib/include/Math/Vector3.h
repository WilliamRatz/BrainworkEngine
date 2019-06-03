//
//  Vector3.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector3_H
#define Vector3_H
#include "Vector.h"

class Vector2;
class Vector4;
class Quaternion;
template<typename T, std::size_t R, std::size_t C> 
class Matrix;

class Vector3 {

private:
	Vector<float, 3> m_vec3;

public:

	static float x(Vector3 m_vec3) { return m_vec3.m_vec3[0]; } const
	static float y(Vector3 m_vec3) { return m_vec3.m_vec3[1]; } const
	static float z(Vector3 m_vec3) { return m_vec3.m_vec3[2]; } const

	float x() { return m_vec3[0]; }
	float y() { return m_vec3[1]; }
	float z() { return m_vec3[2]; }

	void x(float p_x) { m_vec3[0] = p_x; }
	void y(float p_y) { m_vec3[1] = p_y; }
	void z(float p_z) { m_vec3[2] = p_z; }

	Vector3();
	Vector3(float p_x, float p_y, float p_z);
	Vector3(const Vector3&);

#pragma region Methods
	
	void normalize();
	unsigned int getHashCode();

	static Vector3 normalized(const Vector3&);
	static float length(const Vector3&);
	static float dot(const Vector3&, const Vector3&);
	static Vector3 cross(const Vector3&, const Vector3&);

	static Vector3 One();
	static Vector3 Zero();
	
#pragma endregion

#pragma region castOperations
	operator Vector2();
	operator Vector4();
	operator Quaternion();
	operator Matrix<float, 4, 4>();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector3&);
	Vector3 operator-();

	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator/=(const Vector3&);
	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3 operator/(const Vector3&);
	
	Vector3& operator*=(const int&);
	Vector3& operator/=(const int&);
	Vector3 operator*(const int&);
	Vector3 operator/(const int&);
	
	Vector3& operator*=(const float&);
	Vector3& operator/=(const float&);
	Vector3 operator*(const float&);
	Vector3 operator/(const float&);
	
	Vector3& operator*=(const double&);
	Vector3& operator/=(const double&);
	Vector3 operator*(const double&);
	Vector3 operator/(const double&);

#pragma endregion

#pragma region comparisonOperator
	bool operator==(Vector3&);
	bool operator!=(Vector3&);
#pragma endregion

};

template<typename T, std::size_t M, std::size_t N>
Vector3 operator*(Matrix<T, M, N>& p_mat, Vector3& p_vec3) {

	float a1 = p_mat[0][0] * (T)p_vec3.x() + p_mat[0][1] * (T)p_vec3.y() + p_mat[0][2] * (T)p_vec3.z() + p_mat[0][3] * (T)1;
	float a2 = p_mat[1][0] * (T)p_vec3.x() + p_mat[1][1] * (T)p_vec3.y() + p_mat[1][2] * (T)p_vec3.z() + p_mat[1][3] * (T)1;
	float a3 = p_mat[2][0] * (T)p_vec3.x() + p_mat[2][1] * (T)p_vec3.y() + p_mat[2][2] * (T)p_vec3.z() + p_mat[2][3] * (T)1;
	
	Vector3 a(a1, a2, a3);

	return a;
}

std::ostream& operator<<(std::ostream&, Vector3&);
std::ostream& operator<<(std::ostream&, Vector3);


#endif /* Vector3_h */