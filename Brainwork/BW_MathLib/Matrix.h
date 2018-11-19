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

	int getHashCode();

	Matrix& translate2D(T, T);
	Matrix& scale2D(T, T);
	Matrix& rotation2D(T);

	Matrix& translate3D(T, T, T);
	Matrix& scale3D(T, T, T);
	Matrix& rotation3DAroundX(T);
	Matrix& rotation3DAroundY(T);
	Matrix& rotation3DAroundZ(T);
	
	Matrix& identity();
	Matrix& transpose();
	Matrix& inverse();
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
	bool operator==(Matrix&);
	bool operator!=(Matrix&);
#pragma endregion

};

#pragma region Constructor

typeMatrix Matrix<T, M, N>::Matrix()
{
}
typeMatrix Matrix<T, M, N>::Matrix(const Matrix& mat)
{
	*this = mat;
}

#pragma endregion

#pragma region Methods

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::translate2D(T x, T y)
{

	if (M < 3 && N < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D translation check your dimensions");
	}

	Matrix<T, M,N> trans2D;
	trans2D.identity();
	trans2D[0][2] = x;
	trans2D[1][2] = y;

	*this *= trans2D;

	return *this;
}
typeMatrix Matrix<T, M, N>&  Matrix<T, M, N>::scale2D(T width, T height)
{
	if (M < 2 && N < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D scaleing check your dimensions");
	}

	Matrix<T, M, N> scal2D;
	scal2D.identity();
	scal2D[0][2] = width;
	scal2D[1][2] = height;

	*this *= scal2D;

	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation2D(T angle)
{
	if (M < 2 && N < 2) {
		throw std::out_of_range("Your Matrix dont fit for 2D rotation check your dimensions");
	}

	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	Matrix<T, M, N> rotat2D;
	rotat2D.identity();
	rotat2D[0][0] = std::cos(degress);
	rotat2D[0][1] = std::sin(degress);
	rotat2D[1][0] = -std::sin(degress);
	rotat2D[1][1] = std::cos(degress);

	*this *= rotat2D;
	return *this;
}

typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::translate3D(T x, T y, T z)
{
	if (M < 4 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D translation check your dimensions");
	}
	
	Matrix<T, M, N> trans3D;
	trans3D.identity(); 
	trans3D[0][3] = x;
	trans3D[1][3] = y;
	trans3D[2][3] = z;
	
	*this *= trans3D;
	return *this;
}
typeMatrix Matrix<T, M, N>&  Matrix<T, M, N>::scale3D(T width, T height, T depth)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D scaleing check your dimensions");
	}

	Matrix<T, M, N> scal3D;
	scal3D.identity();
	scal3D[0][0] = width;
	scal3D[1][1] = height;
	scal3D[2][2] = depth;

	*this *= scal3D;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundX(T angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"X\" check your dimensions");
	}

	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	Matrix<T, M, N> rotat3DX;
	rotat3DX.identity();
	rotat3DX[1][1] = std::cos(degress);
	rotat3DX[1][2] = -std::sin(degress);
	rotat3DX[2][1] = std::sin(degress);
	rotat3DX[2][2] = std::cos(degress);

	*this *= rotat3DX;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundY(T angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Y\" check your dimensions");
	}

	double degress = (double)angle * MathLib::PI / 180; // change from Rad to degrees

	Matrix<T, M, N> rotat3DY;
	rotat3DY.identity();
	rotat3DY[0][0] = std::cos(degress);
	rotat3DY[0][2] = std::sin(degress);
	rotat3DY[2][0] = -std::sin(degress);
	rotat3DY[2][2] = std::cos(degress);

	*this *= rotat3DY;
	return *this;
}
typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::rotation3DAroundZ(T angle)
{
	if (M < 3 && N < 3) {
		throw std::out_of_range("Your Matrix dont fit for 3D rotation around \"Z\" check your dimensions");
	}

	double degress = (double) angle * MathLib::PI / 180; // change from Rad to degrees

	Matrix<T, M, N> rotat3DZ;
	rotat3DZ.identity();
	rotat3DZ[0][0] = std::cos(degress);
	rotat3DZ[0][1] = std::sin(degress);
	rotat3DZ[1][0] = -std::sin(degress);
	rotat3DZ[1][1] = std::cos(degress);

	*this *= rotat3DZ;
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
//typeMatrix Matrix<T, M, N>& Matrix<T, M, N>::transpose() 
//{
//	
//	return throw "transpose is not implemented yet.";
//}
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
	int x = 0;

	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t ii = 0; ii < M; ++ii) {
			for (std::size_t iii = 0; iii < N; ++iii) {
				tempValue += columns[iii][i] * mat.columns[iii][ii];
			}
			tempMat[i][ii] = tempValue;
			tempValue = (T)0;
		}
	}
	*this = tempMat;
	return *this;
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
