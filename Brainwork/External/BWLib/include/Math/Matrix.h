//
//  Matrix.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//

#ifndef Matrix_H
#define Matrix_H
#include "Vector3.h"

#define typeMatrix template<typename T, std::size_t R, std::size_t C>

//N = rows
//M = columns

typeMatrix
class Matrix {
private:
	Vector<T, C> columns[R];

public:
	Matrix		();
	Matrix		(const Matrix&);
	~Matrix		() {};

	Vector<T, C>& operator[](const std::size_t index) {
		if (index >= R) {
			throw std::out_of_range("Indexüberschreitung!");
		}
		return columns[index];
	}

#pragma region Methods

	Vector3			Forward					();
	Vector3			Backwards				();
	Vector3			Left					();
	Vector3			Right					();
	Vector3			Up						();
	Vector3			Down					();

	std::size_t		getHashCode				();
	std::size_t		countRows				();
	std::size_t		countColumns			();
	
	Vector3			getTransform			();
	Matrix&			identity				();
	Matrix&			inverse					();
	Matrix<T, C, R>	transpose				();

	Matrix&			translate2D				(float x, float y);
	Matrix&			scale2D					(float width, float height);
	Matrix&			rotation2D				(float angle);

	Matrix&			translate3D				(float x, float y, float z);
	Matrix&			translate3D				(Vector3 vec3);
	Matrix&			scale3D					(float width, float height, float depth);
	Matrix&			rotation3DAroundX		(float angle);
	Matrix&			rotation3DAroundY		(float angle);
	Matrix&			rotation3DAroundZ		(float angle);

	Matrix&			rotation3DAroundXlocal	(float angle);
	Matrix&			rotation3DAroundYlocal	(float angle);
	Matrix&			rotation3DAroundZlocal	(float angle);

	Matrix&			rotation3DAroundArbitararyAxis	(float angle, Vector3 axis);

	Matrix&			perspectivProjection	(float windowWidth, float windowHeight, float nearPlane, float farPlane);
	Matrix&			orthogonalProjection	(float windowWidth, float windowHeight, float nearPlane, float farPlane);

#pragma endregion
#pragma region arithmeticOperator
	void		operator=			(const Matrix&);
	Matrix		operator+			(const Matrix&);
	Matrix		operator-			(const Matrix&);
	Matrix		operator*			(const Matrix&);
	Matrix&		operator+=			(const Matrix&);
	Matrix&		operator-=			(const Matrix&);
	Matrix&		operator*=			(const Matrix&);
#pragma endregion
#pragma region comparisonOperator
	bool		operator==			(Matrix&);
	bool		operator!=			(Matrix&);
#pragma endregion

};

#pragma region Constructor

typeMatrix inline Matrix<T, R, C>::Matrix()
{
	this->identity();
}
typeMatrix inline Matrix<T, R, C>::Matrix(const Matrix& mat)
{
	*this = mat;
}

#pragma endregion
#pragma region Methods

typeMatrix inline Vector3 Matrix<T, R, C>::Forward()
{
	return Vector3(columns[0][2], columns[1][2], columns[2][2]);
}

typeMatrix inline Vector3 Matrix<T, R, C>::Backwards()
{
	return Vector3(-columns[0][2], -columns[1][2], -columns[2][2]);
}

typeMatrix inline Vector3 Matrix<T, R, C>::Left()
{
	return Vector3(-columns[0][0], -columns[1][0], -columns[2][0]);
}

typeMatrix inline Vector3 Matrix<T, R, C>::Right()
{
	return Vector3(columns[0][0], columns[1][0], columns[2][0]);
}

typeMatrix inline Vector3 Matrix<T, R, C>::Up()
{
	return Vector3(columns[0][1], columns[1][1], columns[2][1]);
}

typeMatrix inline Vector3 Matrix<T, R, C>::Down()
{
	return Vector3(-columns[0][1], -columns[1][1], -columns[2][1]);
}

typeMatrix inline std::size_t Matrix<T, R, C>::getHashCode()
{
	std::size_t hash = 17;

	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < C; ++ii) {
			hash *= static_cast<std::size_t>(23 + std::hash<T>()(columns[i][ii]));
		}
	}

	return hash;
}
typeMatrix inline std::size_t Matrix<T, R, C>::countColumns()
{
	return C;
}
typeMatrix inline std::size_t Matrix<T, R, C>::countRows()
{
	return R;
}

typeMatrix inline Matrix<T, R, C>&  Matrix<T, R, C>::translate2D(float x, float y)
{
	if (R < 3 && C < 2) {
		throw std::out_of_range("Your Matrix don't fit for 2D translation check your dimensions");
	}

	Matrix<T, R, C> trans2D;

	trans2D[0][2] = (T)x;
	trans2D[1][2] = (T)y;

	*this *= trans2D;

	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::scale2D(float width, float height)
{
	if (R < 2 && C < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D scaleing check your dimensions");
	}

	Matrix<T, R, C> scal2D;

	scal2D[0][2] = (T)width;
	scal2D[1][2] = (T)height;

	*this *= scal2D;

	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation2D(float angle)
{
	if (R < 2 && C < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D rotation check your dimensions");
	}

	Matrix<T, R, C> rotat2D;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat2D[0][0] = (T)std::cos(degress);
	rotat2D[0][1] = (T)std::sin(degress);
	rotat2D[1][0] = (T)-std::sin(degress);
	rotat2D[1][1] = (T)std::cos(degress);

	*this *= rotat2D;
	return *this;
}

typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::translate3D(float x, float y, float z)
{
	if (R < 4 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D translation check your dimensions");
	}

	Matrix<T, R, C> trans3D;

	trans3D[0][3] = (T)x;
	trans3D[1][3] = (T)y;
	trans3D[2][3] = (T)z;

	*this *= trans3D;
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::translate3D(Vector3 vec3)
{
	if (R < 4 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D translation check your dimensions");
	}

	Matrix<T, R, C> trans3D;

	trans3D[0][3] = (T)vec3.x();
	trans3D[1][3] = (T)vec3.y();
	trans3D[2][3] = (T)vec3.z();

	*this *= trans3D;
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::scale3D(float width, float height, float depth)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D scaleing check your dimensions");
	}

	Matrix<T, R, C> scal3D;

	scal3D[0][0] = (T)width;
	scal3D[1][1] = (T)height;
	scal3D[2][2] = (T)depth;

	*this *= scal3D;
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundX(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\" check your dimensions");
	}

	Matrix<T, R, C> rotat3DX;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DX[1][1] = (T)std::cos(degress);
	rotat3DX[1][2] = (T)-std::sin(degress);
	rotat3DX[2][1] = (T)std::sin(degress);
	rotat3DX[2][2] = (T)std::cos(degress);

	this->operator*=(rotat3DX);
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundY(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\" check your dimensions");
	}

	Matrix<T, R, C> rotat3DY;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DY[0][0] = (T)std::cos(degress);
	rotat3DY[0][2] = (T)std::sin(degress);
	rotat3DY[2][0] = (T)-std::sin(degress);
	rotat3DY[2][2] = (T)std::cos(degress);

	this->operator*=(rotat3DY);
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundZ(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\" check your dimensions");
	}

	Matrix<T, R, C> rotat3DZ;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DZ[0][0] = (T)std::cos(degress);
	rotat3DZ[0][1] = (T)std::sin(degress);
	rotat3DZ[1][0] = (T)-std::sin(degress);
	rotat3DZ[1][1] = (T)std::cos(degress);

	this->operator*=(rotat3DZ);
	return *this;
}

typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundXlocal(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\" check your dimensions");
	}
	Vector3 transformation(columns[0][3], columns[1][3], columns[2][3]);

	this->columns[0][3] = 0;
	this->columns[1][3] = 0;
	this->columns[2][3] = 0;

	this->rotation3DAroundX(angle);

	this->columns[0][3] = transformation.x();
	this->columns[1][3] = transformation.y();
	this->columns[2][3] = transformation.z();

	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundYlocal(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\" check your dimensions");
	}

	Vector3 transformation(columns[0][3], columns[1][3], columns[2][3]);

	this->columns[0][3] = 0;
	this->columns[1][3] = 0;
	this->columns[2][3] = 0;

	this->rotation3DAroundY(angle);

	this->columns[0][3] = transformation.x();
	this->columns[1][3] = transformation.y();
	this->columns[2][3] = transformation.z();

	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundZlocal(float angle)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\" check your dimensions");
	}

	Vector3 transformation(columns[0][3], columns[1][3], columns[2][3]);

	this->columns[0][3] = 0;
	this->columns[1][3] = 0;
	this->columns[2][3] = 0;

	this->rotation3DAroundZ(angle);

	this->columns[0][3] = transformation.x();
	this->columns[1][3] = transformation.y();
	this->columns[2][3] = transformation.z();

	return *this;

}
			
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::rotation3DAroundArbitararyAxis(float angle, Vector3 axis)
{
	if (R < 3 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\" check your dimensions");
	}

	Matrix<T, R, C> rotat3DArbiAxis;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DArbiAxis[0][0] = (std::cos(angle) + MathLib::pow(axis.x(), 2)) * (1 - std::cos(angle));
	rotat3DArbiAxis[0][1] = (axis.x() * axis.y()) * (1 - std::cos(angle)) - (axis.z()*std::sin(angle));
	rotat3DArbiAxis[0][2] = (axis.x() * axis.z()) * (1 - std::cos(angle)) + (axis.y()*std::sin(angle));
	rotat3DArbiAxis[1][0] = (axis.y() * axis.x()) * (1 - std::cos(angle)) + (axis.z()*std::sin(angle));
	rotat3DArbiAxis[1][1] = (std::cos(angle) + MathLib::pow(axis.y(), 2)) * (1 - std::cos(angle));
	rotat3DArbiAxis[1][2] = (axis.y() * axis.z()) * (1 - std::cos(angle)) - (axis.x()*std::sin(angle));
	rotat3DArbiAxis[2][0] = (axis.z() * axis.x()) * (1 - std::cos(angle)) - (axis.y()*std::sin(angle));
	rotat3DArbiAxis[2][1] = (axis.z() * axis.y()) * (1 - std::cos(angle)) + (axis.x()*std::sin(angle));
	rotat3DArbiAxis[2][2] = std::cos(angle) + MathLib::pow(axis.z(), 2) * (1 - std::cos(angle));

	*this *= rotat3DArbiAxis;
	return *this;
}

typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::perspectivProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
{
	if (R < 4 && C < 4) {
		throw std::out_of_range("Your Matrix dont fit for perspectiv projection check your dimensions");
	}

	Matrix<T, R, C> perProj;

	perProj[0][0] = (T) ((2 * nearPlane) / windowWidth);
	perProj[1][1] = (T) ((2 * nearPlane) / windowHeight);
	perProj[2][2] = (T) (farPlane / (farPlane - nearPlane));
	perProj[2][3] = (T) 1;
	perProj[3][2] = (T) ((-farPlane * nearPlane) / (farPlane - nearPlane));
	perProj[3][3] = 0;
	*this = perProj;
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::orthogonalProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
{
	if (R < 4 && C < 3) {
		throw std::out_of_range("Your Matrix dont fit for orthogonal projection check your dimensions");
	}

	Matrix<T, R, C> perProj;

	perProj[0][0] = (T) (2 / windowWidth);
	perProj[1][1] = (T) (2 / windowHeight);
	perProj[2][2] = (T) (1 / (farPlane - nearPlane));
	perProj[3][3] = (T) (-nearPlane / (farPlane - nearPlane));

	if (C > 3)
	{
		perProj[3][3] = (T) 1;
	}

	*this = perProj;
	return *this;
}
						

typeMatrix inline Vector3 Matrix<T, R, C>::getTransform()
{
	return Vector3(columns[0][3], columns[1][3], columns[2][3]);
}

typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::identity() {

	for (std::size_t i = 0; i < C; ++i) {
		for (std::size_t ii = 0; ii < R; ++ii) {
			columns[ii][i] = (i == ii) ? T(1) : T(0);
		}
	}
	return *this;

}
typeMatrix inline Matrix<T, C, R> Matrix<T, R, C>::transpose()
{
	Matrix<T, C, R> temp;

	for (std::size_t i = 0; i < C; ++i) {
		for (std::size_t ii = 0; ii < R; ++ii) {
			temp[i][ii] = columns[ii][i];
		}
	}

	return temp;
}

#pragma endregion
#pragma region arithmeticOperator

typeMatrix void Matrix<T, R, C>::operator=(const Matrix& mat)
{
	for (std::size_t i = 0; i < C; ++i) {
		for (std::size_t ii = 0; ii < R; ++ii) {
			columns[ii][i] = mat.columns[ii][i];
		}
	}
}

typeMatrix inline Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix& mat) {

	Matrix<T, R, C> temp(*this);
	return temp += mat;
}
typeMatrix inline Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix& mat) {

	Matrix<T, R, C> temp(*this);
	return temp -= mat;
}
typeMatrix inline Matrix<T, R, C> Matrix<T, R, C>::operator*(const Matrix& mat) {

	Matrix<T, R, C> temp(*this);
	return temp *= mat;
}
						
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::operator+=(const Matrix& mat)
{
	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < C; ++ii) {
			columns[i][ii] = columns[i][ii] + mat.columns[i][ii];
		}
	}
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::operator-=(const Matrix& mat)
{
	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < C; ++ii) {
			columns[i][ii] = columns[i][ii] - mat.columns[i][ii];
		}
	}
	return *this;
}
typeMatrix inline Matrix<T, R, C>& Matrix<T, R, C>::operator*=(const Matrix& mat)
{
	T tempValue = (T)0;
	Matrix<T, R, R> tempMat;

	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < R; ++ii) {
			for (std::size_t iii = 0; iii < C; ++iii) {
				tempValue += columns[i][iii] * mat.columns[iii][ii];
			}
			tempMat[i][ii] = tempValue;
			tempValue = (T)0;
		}
	}
	*this = tempMat;
	return *this;
}
#pragma endregion
#pragma region comparisonOperator
typeMatrix inline bool Matrix<T, R, C>::operator==(Matrix& mat)
{
	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < C; ++ii) {
			if (columns[i][ii] != mat[i][ii])
				return false;
		}
	}
	return true;
}
typeMatrix inline bool Matrix<T, R, C>::operator!=(Matrix& mat)
{
	for (std::size_t i = 0; i < R; ++i) {
		for (std::size_t ii = 0; ii < C; ++ii) {
			if (columns[i][ii] != mat[i][ii])
				return true;
		}
	}
	return false;
}

#pragma endregion	

typeMatrix inline std::ostream& operator<<(std::ostream& os, Matrix<T, R, C>& mat) {
	for (std::size_t i = 0; i < R; ++i) {
		os << '|';
		for (std::size_t ii = 0; ii < C; ++ii) {

			os << mat[i][ii];
			if (ii < C - 1)
				os << ' ';
		}
		os << '|' << std::endl;
	}
	return os;
}

#endif /* Matrix_h */
