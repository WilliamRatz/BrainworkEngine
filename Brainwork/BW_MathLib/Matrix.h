//
//  Matrix.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//

#ifndef Matrix_H
#define Matrix_H

#define typeMatrix template<typename T, std::size_t M, std::size_t N>

//M = rows
//N = columns

typeMatrix
class Matrix {
private:
	Vector<T, M> columns[N];

public:
	Matrix();
	Matrix(const Matrix&);
	~Matrix() {	}

	Vector<T, M>& operator[](const std::size_t index) {
		if (index > N) {
			throw std::out_of_range("Indexüberschreitung!");
		}
		return columns[index];
	}

#pragma region Methods

	std::size_t getHashCode();

	Matrix& translate2D(float x, float y);
	Matrix& scale2D(float width, float height);
	Matrix& rotation2D(float angle);

	Matrix& translate3D(float x, float y, float z);
	Matrix& scale3D(float width, float height, float depth);
	Matrix& rotation3DAroundX(float angle);
	Matrix& rotation3DAroundY(float angle);
	Matrix& rotation3DAroundZ(float angle);

	Matrix& perspectivProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane);
	Matrix& orthogonalProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane);

	Matrix& identity();
	Matrix& inverse();
	Matrix<T, N, M>& transpose();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
#pragma endregion

#pragma region comparisonOperator
	bool operator==(const Matrix&);
	bool operator!=(const Matrix&);
#pragma endregion

};

#pragma region Constructor

typeMatrix Matrix<T, M, N>::Matrix()
{
	(*this).identity();
}
typeMatrix Matrix<T, M, N>::Matrix(const Matrix& mat)
{
	*this = mat;
}

#pragma endregion

#pragma region Methods

typeMatrix std::size_t Matrix<T, M, N>::getHashCode()
{
	std::size_t hash = 17;

	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			hash *= static_cast<std::size_t>(23 + std::hash<T>()(columns[i][ii]));
		}
	}

	return hash;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::translate2D(float x, float y)
{
	if (M < 3 && N < 2) {
		throw std::out_of_range("Your Matrix don't fit for 2D translation check your dimensions");
	}

	Matrix<T, M, N> trans2D;

	trans2D[0][2] = (T)x;
	trans2D[1][2] = (T)y;

	*this *= trans2D;

	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::scale2D(float width, float height)
{
	if (M < 2 && N < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D scaleing check your dimensions");
	}

	Matrix<T, M, N> scal2D;

	scal2D[0][2] = (T)width;
	scal2D[1][2] = (T)height;

	*this *= scal2D;

	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation2D(float angle)
{
	if (M < 2 && N < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D rotation check your dimensions");
	}

	Matrix<T, M, N> rotat2D;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat2D[0][0] = (T)std::cos(degress);
	rotat2D[0][1] = (T)std::sin(degress);
	rotat2D[1][0] = (T)-std::sin(degress);
	rotat2D[1][1] = (T)std::cos(degress);

	*this *= rotat2D;
	return *this;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::translate3D(float x, float y, float z)
{
	if (M < 4 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D translation check your dimensions");
	}

	Matrix<T, M, N> trans3D;

	trans3D[0][3] = (T)x;
	trans3D[1][3] = (T)y;
	trans3D[2][3] = (T)z;

	*this *= trans3D;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::scale3D(float width, float height, float depth)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D scaleing check your dimensions");
	}

	Matrix<T, M, N> scal3D;

	scal3D[0][0] = (T)width;
	scal3D[1][1] = (T)height;
	scal3D[2][2] = (T)depth;

	*this *= scal3D;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundX(float angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\" check your dimensions");
	}

	Matrix<T, M, N> rotat3DX;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DX[1][1] = (T)std::cos(degress);
	rotat3DX[1][2] = (T)-std::sin(degress);
	rotat3DX[2][1] = (T)std::sin(degress);
	rotat3DX[2][2] = (T)std::cos(degress);

	this->operator*=(rotat3DX);
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundY(float angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\" check your dimensions");
	}

	Matrix<T, M, N> rotat3DY;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DY[0][0] = (T)std::cos(degress);
	rotat3DY[0][2] = (T)std::sin(degress);
	rotat3DY[2][0] = (T)-std::sin(degress);
	rotat3DY[2][2] = (T)std::cos(degress);

	this->operator*=(rotat3DY);
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundZ(float angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\" check your dimensions");
	}

	Matrix<T, M, N> rotat3DZ;
	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	rotat3DZ[0][0] = (T)std::cos(degress);
	rotat3DZ[0][1] = (T)std::sin(degress);
	rotat3DZ[1][0] = (T)-std::sin(degress);
	rotat3DZ[1][1] = (T)std::cos(degress);

	this->operator*=(rotat3DZ);
	return *this;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::perspectivProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
{
	if (M < 4 && N < 4) {
		throw std::out_of_range("Your Matrix dont fit for perspectiv projection check your dimensions");
	}

	Matrix<T, M, N> perProj;

	perProj[0][0] = (T) ((2 * nearPlane) / windowWidth);
	perProj[1][1] = (T) ((2 * nearPlane) / windowHeight);
	perProj[2][2] = (T) (farPlane / (farPlane - nearPlane));
	perProj[2][3] = (T) 1;
	perProj[3][2] = (T) ((-farPlane * nearPlane) / (farPlane - nearPlane));
	perProj[3][3] = 0;
	*this = perProj;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::orthogonalProjection(float windowWidth, float windowHeight, float nearPlane, float farPlane)
{
	if (M < 4 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for orthogonal projection check your dimensions");
	}

	Matrix<T, M, N> perProj;

	perProj[0][0] = (T) (2 / windowWidth);
	perProj[1][1] = (T) (2 / windowHeight);
	perProj[2][2] = (T) (1 / (farPlane - nearPlane));
	perProj[3][3] = (T) (-nearPlane / (farPlane - nearPlane));

	if (N > 3)
	{
		perProj[3][3] = (T) 1;
	}

	this->operator*=(perProj);
	return *this;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::identity() {

	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			columns[i][ii] = (i == ii) ? T(1) : T(0);

		}
	}
	return *this;

}
typeMatrix Matrix<T, N, M>& Matrix<T, M, N>::transpose()
{
	Matrix<T, N, M> temp;

	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			temp[i][ii] = columns[ii][i];
		}
	}
	return temp;
}
#pragma endregion

#pragma region arithmeticOperator
typeMatrix void Matrix<T, M, N>::operator=(const Matrix& mat)
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			columns[i][ii] = mat.columns[i][ii];
		}
	}
}

typeMatrix Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix& mat) {

	Matrix<T, M, N> temp(*this);
	return temp += mat;
}
typeMatrix Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix& mat) {

	Matrix<T, M, N> temp(*this);
	return temp -= mat;
}
typeMatrix Matrix<T, M, N> Matrix<T, M, N>::operator*(const Matrix& mat) {

	Matrix<T, M, N> temp(*this);
	return temp *= mat;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::operator+=(const Matrix& mat)
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			columns[i][ii] = columns[i][ii] + mat.columns[i][ii];
		}
	}
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::operator-=(const Matrix& mat)
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < N; ++ii) {
			columns[i][ii] = columns[i][ii] - mat.columns[i][ii];
		}
	}
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::operator*=(const Matrix& mat)
{
	T tempValue = (T)0;
	Matrix<T, M, M> tempMat;

	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < M; ++ii) {
			for (std::size_t iii = 0; iii < N; ++iii) {
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
typeMatrix bool Matrix<T, M, N>::operator==(const Matrix& mat)
{
	if (*this->getHashCode() == mat.getHashCode())
	{
		return true;
	}
	else
	{
		return false;
	}
}
typeMatrix bool Matrix<T, M, N>::operator!=(const Matrix& mat)
{
	if (*this->getHashCode() != mat.getHashCode())
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion	

template<typename T, std::size_t M, std::size_t N>
std::ostream& operator<<(std::ostream& os, Matrix<T, N, M>& matrix) {

	for (std::size_t i = 0; i < M; ++i) {
		os << '|';
		for (std::size_t ii = 0; ii < N; ++ii) {

			os << matrix[i][ii];
			if (ii < N - 1)
				os << ' ';
		}
		os << '|' << std::endl;
	}
	return os;
}

#endif /* Matrix_h */
