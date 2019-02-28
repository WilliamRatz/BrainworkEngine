 //
//  Vector3.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//

#ifndef Vector3_H
#define Vector3_H
#include "Vector.h"

template<typename T, std::size_t R, std::size_t C> class Matrix;

class Vector3 {

private:
	Vector<float, 3> vec3;

public:

	static float x(Vector3 vec) { return vec.vec3[0]; } const
	static float y(Vector3 vec) { return vec.vec3[1]; } const
	static float z(Vector3 vec) { return vec.vec3[2]; } const

	float x() { return vec3[0]; }
	float y() { return vec3[1]; }
	float z() { return vec3[2]; }

	void x(float p_x) { vec3[0] = p_x; }
	void y(float p_y) { vec3[1] = p_y; }
	void z(float p_z) { vec3[2] = p_z; }

	Vector3();
	Vector3(float p_x, float p_y, float p_z);
	Vector3(const Vector3&);

#pragma region Methods
	
	Vector3 normalize();
	std::size_t getHashCode();

	static Vector3 normalized(const Vector3&);
	static float length(const Vector3&);
	static float dot(const Vector3&, const Vector3&);
	static Vector3 cross(const Vector3&, const Vector3&);

	static Vector3 One();
	static Vector3 Zero();
	
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector3&);
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
Vector3 operator*(Matrix<T, M, N>& mat, Vector3& vec) {

	float a1 = mat[0][0] * (T)vec.x() + mat[0][1] * (T)vec.y() + mat[0][2] * (T)vec.z() + mat[0][3] * (T)1;
	float a2 = mat[1][0] * (T)vec.x() + mat[1][1] * (T)vec.y() + mat[1][2] * (T)vec.z() + mat[1][3] * (T)1;
	float a3 = mat[2][0] * (T)vec.x() + mat[2][1] * (T)vec.y() + mat[2][2] * (T)vec.z() + mat[2][3] * (T)1;
	
	Vector3 a(a1, a2, a3);

	return a;
}

std::ostream& operator<<(std::ostream&, Vector3&);


#endif /* Vector3_h */
