//
//  Quaternion.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Quaternion_H
#define Quaternion_H
#include "Vector.h"
#include "Matrix.h"


class Quaternion {
private:
	Vector<float, 4> quad4;

public:
	static float x(Quaternion quad) { return quad.quad4[0]; }
	static float y(Quaternion quad) { return quad.quad4[1]; }
	static float z(Quaternion quad) { return quad.quad4[2]; }
	static float w(Quaternion quad) { return quad.quad4[3]; }

	float x() { return quad4[0]; }
	float y() { return quad4[1]; }
	float z() { return quad4[2]; }
	float w() { return quad4[3]; }

	void x(float p_x) { quad4[0] = p_x; }
	void y(float p_y) { quad4[1] = p_y; }
	void z(float p_z) { quad4[2] = p_z; }
	void w(float p_w) { quad4[3] = p_w; }

	Quaternion();
	Quaternion(float p_x, float p_y, float p_z, float p_w);
	Quaternion(const Quaternion&);

#pragma region Math
	
	int getHashCode();

	float length();

#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Quaternion&);
	inline Quaternion operator+(const Quaternion&);
	inline Quaternion operator-(const Quaternion&);
	inline Quaternion operator*(const Quaternion&);
	inline Quaternion& operator+=(const Quaternion&);
	inline Quaternion& operator-=(const Quaternion&);
	inline Quaternion& operator*=(const Quaternion&);
	
#pragma endregion

#pragma region comparisonOperator
	bool operator==(Quaternion&);
	bool operator!=(Quaternion&);
#pragma endregion

};

template<typename T, std::size_t M, std::size_t N>
Quaternion operator*(Matrix<T, M, N>& mat, Quaternion& quad) {

	T a1 = mat[0][0] * (T)quad.x() + mat[0][1] * (T)quad.y() + mat[0][2] * (T)quad.z() + mat[0][3] * (T)quad.w();
	T a2 = mat[1][0] * (T)quad.x() + mat[1][1] * (T)quad.y() + mat[1][2] * (T)quad.z() + mat[1][3] * (T)quad.w();
	T a3 = mat[2][0] * (T)quad.x() + mat[2][1] * (T)quad.y() + mat[2][2] * (T)quad.z() + mat[2][3] * (T)quad.w();
	T a4 = mat[3][0] * (T)quad.x() + mat[3][1] * (T)quad.y() + mat[3][2] * (T)quad.z() + mat[3][3] * (T)quad.w();

	Quaternion result((float)a1, (float)a2, (float)a3, (float)a4);

	return result;
}

std::ostream& operator<<(std::ostream&, Quaternion&);

#endif /* Quaternion.h */
