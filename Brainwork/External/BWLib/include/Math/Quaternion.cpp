
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

Quaternion::Quaternion()
{
	m_quad[0] = NULL;
	m_quad[1] = NULL;
	m_quad[2] = NULL;
	m_quad[3] = NULL;
}
Quaternion::Quaternion(float p_x, float p_y, float p_z, float p_w)
{
	m_quad[0] = p_x;
	m_quad[1] = p_y;
	m_quad[2] = p_z;
	m_quad[3] = p_w;
}
Quaternion::Quaternion(const Quaternion& p_quad)
{
	m_quad = p_quad.m_quad;
}

#pragma region Methods
unsigned int Quaternion::getHashCode()
{
	return ((((((static_cast<unsigned int>(m_quad[0])) * 397) ^ static_cast<unsigned int>(m_quad[1])) * 397) ^ static_cast<unsigned int>(m_quad[2])) * 397) ^ static_cast<unsigned int>(m_quad[3]);
}
#pragma endregion

#pragma region castOperations
Quaternion::operator Vector2()
{
	return Vector2(x(), y());
}
Quaternion::operator Vector3()
{
	return Vector3(x(), y(), z());
}
Quaternion::operator Vector4()
{
	return Vector4(x(), y(), z(), w());
}
Quaternion::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> p_mat;
	p_mat[0][3] = x();
	p_mat[1][3] = y();
	p_mat[2][3] = z();
	p_mat[3][3] = w();
	return p_mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Quaternion::operator=(const Quaternion& p_quad) {

	m_quad[0] = p_quad.m_quad[0];
	m_quad[1] = p_quad.m_quad[1];
	m_quad[2] = p_quad.m_quad[2];
	m_quad[3] = p_quad.m_quad[3];
}
Quaternion Quaternion::operator-()
{
	m_quad[0] = -m_quad[0];
	m_quad[1] = -m_quad[1];
	m_quad[2] = -m_quad[2];
	m_quad[3] = -m_quad[3];

	return *this;
}
Quaternion Quaternion::operator+(const Quaternion& p_quad) {

	Quaternion temp(*this);
	return temp += p_quad;
}
Quaternion Quaternion::operator-(const Quaternion& p_quad) {

	Quaternion temp(*this);
	return temp -= p_quad;
}
Quaternion Quaternion::operator*(const Quaternion& p_quad) {

	Quaternion temp(*this);
	return temp *= p_quad;
}
Quaternion& Quaternion::operator+=(const Quaternion& p_quad) {
	m_quad[0] = m_quad[0] + p_quad.m_quad[0];
	m_quad[1] = m_quad[1] + p_quad.m_quad[1];
	m_quad[2] = m_quad[2] + p_quad.m_quad[2];
	m_quad[3] = m_quad[3] + p_quad.m_quad[3];

	return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& p_quad) {
	m_quad[0] = m_quad[0] - p_quad.m_quad[0];
	m_quad[1] = m_quad[1] - p_quad.m_quad[1];
	m_quad[2] = m_quad[2] - p_quad.m_quad[2];
	m_quad[3] = m_quad[3] - p_quad.m_quad[3];

	return *this;
}
Quaternion& Quaternion::operator*=(const Quaternion& p_quad) {
	m_quad[0] = (m_quad[0] * p_quad.m_quad[0]) - (m_quad[1] * p_quad.m_quad[1]) - (m_quad[2] * p_quad.m_quad[2]) - (m_quad[3] * p_quad.m_quad[3]);
	m_quad[1] = (m_quad[0] * p_quad.m_quad[1]) + (m_quad[1] * p_quad.m_quad[0]) + (m_quad[2] * p_quad.m_quad[3]) - (m_quad[3] * p_quad.m_quad[2]);
	m_quad[2] = (m_quad[0] * p_quad.m_quad[2]) - (m_quad[1] * p_quad.m_quad[3]) + (m_quad[2] * p_quad.m_quad[0]) + (m_quad[3] * p_quad.m_quad[1]);
	m_quad[3] = (m_quad[0] * p_quad.m_quad[3]) + (m_quad[1] * p_quad.m_quad[2]) - (m_quad[2] * p_quad.m_quad[1]) - (m_quad[3] * p_quad.m_quad[0]);

	return *this;
}
#pragma endregion

#pragma region comparisonOperator
bool Quaternion::operator==(Quaternion& p_quad) {

	if (m_quad[0] == p_quad.m_quad[0] &&
		m_quad[1] == p_quad.m_quad[1] &&
		m_quad[2] == p_quad.m_quad[2] &&
		m_quad[3] == p_quad.m_quad[3]) {

		return true;
	}
	else {

		return false;
	}

}
bool Quaternion::operator!=(Quaternion& p_quad) {

	if (m_quad[0] != p_quad.m_quad[0] ||
		m_quad[1] != p_quad.m_quad[1] ||
		m_quad[2] != p_quad.m_quad[2] ||
		m_quad[3] != p_quad.m_quad[3]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& p_output, Quaternion& p_quad)
{
	p_output << '(' << p_quad.x() << '/' << p_quad.y() << '/' << p_quad.z() << '/' << p_quad.w() << ')';
	return p_output;
}

std::ostream & operator<<(std::ostream& p_output, Quaternion p_quad)
{
	p_output << '(' << p_quad.x() << '/' << p_quad.y() << '/' << p_quad.z() << '/' << p_quad.w() << ')';
	return p_output;
}
