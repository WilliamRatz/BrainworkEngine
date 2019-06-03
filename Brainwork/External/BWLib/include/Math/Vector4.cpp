
#include "BWMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

Vector4::Vector4()
{
	m_vec4[0] = NULL;
	m_vec4[1] = NULL;
	m_vec4[2] = NULL;
}
Vector4::Vector4(float p_x, float p_y, float p_z, float p_w)
{
	m_vec4[0] = p_x;
	m_vec4[1] = p_y;
	m_vec4[2] = p_z;
	m_vec4[3] = p_w;
}
Vector4::Vector4(const Vector4& p_vec4)
{
	m_vec4 = p_vec4.m_vec4;
}

#pragma region Methods
Vector4 Vector4::normalize()
{
	m_vec4[0] /= Vector4::length(*this);
	m_vec4[1] /= Vector4::length(*this);
	m_vec4[2] /= Vector4::length(*this);

	return *this;
}
unsigned int Vector4::getHashCode() {
	
	return ((((((static_cast<unsigned int>(m_vec4[0])) * 397) ^ static_cast<unsigned int>(m_vec4[1])) * 397) ^ static_cast<unsigned int>(m_vec4[2])) * 397) ^ static_cast<unsigned int>(m_vec4[3]);
}

float Vector4::length(const Vector4& p_vec4)
{
	return static_cast<float>(BWMath::sqrt(BWMath::pow(Vector4::x(p_vec4), 2) + BWMath::pow(Vector4::y(p_vec4), 2) + BWMath::pow(Vector4::z(p_vec4), 2)));
}
float  Vector4::dot(const Vector4& p_vec4_1, const Vector4& p_vec4_2)
{
	return Vector4::x(p_vec4_1) * Vector4::x(p_vec4_2) + Vector4::y(p_vec4_1) * Vector4::y(p_vec4_2) + Vector4::z(p_vec4_1) * Vector4::z(p_vec4_2);
}
Vector4 Vector4::normalized(const Vector4& p_vec4) {

	return Vector4(Vector4::x(p_vec4) / Vector4::length(p_vec4), Vector4::y(p_vec4) / Vector4::length(p_vec4), Vector4::z(p_vec4) / Vector4::length(p_vec4), Vector4::w(p_vec4) / Vector4::length(p_vec4));
}
Vector4  Vector4::One()
{
	return Vector4(1, 1, 1, 1);
}
Vector4  Vector4::Zero()
{
	return Vector4(0, 0, 0, 0);
}
#pragma endregion

#pragma region castOperations
Vector4::operator Vector2()
{
	return Vector2(x(), y());
}
Vector4::operator Vector3()
{
	return Vector3(x(), y(), z());
}
Vector4::operator Quaternion()
{
	return Quaternion(x(), y(), z(), w());
}
Vector4::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> mat;
	mat[0][3] = x();
	mat[1][3] = y();
	mat[2][3] = z();
	mat[3][3] = w();
	return mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Vector4::operator=(const Vector4& p_vec4) {

	m_vec4[0] = p_vec4.m_vec4[0];
	m_vec4[1] = p_vec4.m_vec4[1];
	m_vec4[2] = p_vec4.m_vec4[2];
	m_vec4[3] = p_vec4.m_vec4[3];
}
Vector4 Vector4::operator-()
{
	m_vec4[0] = -m_vec4[0];
	m_vec4[1] = -m_vec4[1];
	m_vec4[2] = -m_vec4[2];
	m_vec4[3] = -m_vec4[3];

	return *this;
}
Vector4& Vector4::operator+=(const Vector4& p_vec4) {
	m_vec4[0] = m_vec4[0] + p_vec4.m_vec4[0];
	m_vec4[1] = m_vec4[1] + p_vec4.m_vec4[1];
	m_vec4[2] = m_vec4[2] + p_vec4.m_vec4[2];
	m_vec4[3] = m_vec4[3] + p_vec4.m_vec4[3];

	return *this;
}
Vector4& Vector4::operator-=(const Vector4& p_vec4) {
	m_vec4[0] = m_vec4[0] - p_vec4.m_vec4[0];
	m_vec4[1] = m_vec4[1] - p_vec4.m_vec4[1];
	m_vec4[2] = m_vec4[2] - p_vec4.m_vec4[2];
	m_vec4[3] = m_vec4[3] - p_vec4.m_vec4[3];

	return *this;
}
Vector4& Vector4::operator/=(const Vector4& p_vec4) {
	m_vec4[0] = m_vec4[0] / p_vec4.m_vec4[0];
	m_vec4[1] = m_vec4[1] / p_vec4.m_vec4[1];
	m_vec4[2] = m_vec4[2] / p_vec4.m_vec4[2];
	m_vec4[3] = m_vec4[3] / p_vec4.m_vec4[3];

	return *this;
}
Vector4 Vector4::operator+(const Vector4& p_vec4) {

	Vector4 temp(*this);
	return temp += p_vec4;
}
Vector4 Vector4::operator-(const Vector4& p_vec4) {

	Vector4 temp(*this);
	return temp -= p_vec4;
}
Vector4 Vector4::operator/(const Vector4& p_vec4) {

	Vector4 temp(*this);
	return temp /= p_vec4;
}

Vector4& Vector4::operator*=(const int& p_value)
{
	m_vec4[0] = m_vec4[0] * static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] * static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] * static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] * static_cast<float>(p_value);

	return *this;
}
Vector4& Vector4::operator/=(const int& p_value)
{
	m_vec4[0] = m_vec4[0] / static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] / static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] / static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] / static_cast<float>(p_value);

	return *this;
}
Vector4 Vector4::operator*(const int& p_value)
{
	Vector4 temp(*this);
	return temp *= p_value;
}
Vector4 Vector4::operator/(const int& p_value)
{
	Vector4 temp(*this);
	return temp /= p_value;
}

Vector4& Vector4::operator*=(const float& p_value)
{
	m_vec4[0] = m_vec4[0] * static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] * static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] * static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] * static_cast<float>(p_value);

	return *this;
}
Vector4& Vector4::operator/=(const float& p_value)
{
	m_vec4[0] = m_vec4[0] / static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] / static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] / static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] / static_cast<float>(p_value);

	return *this;
}
Vector4 Vector4::operator*(const float& p_value)
{
	Vector4 temp(*this);
	return temp *= p_value;
}
Vector4 Vector4::operator/(const float& p_value)
{
	Vector4 temp(*this);
	return temp /= p_value;
}

Vector4& Vector4::operator*=(const double& p_value)
{
	m_vec4[0] = m_vec4[0] * static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] * static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] * static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] * static_cast<float>(p_value);

	return *this;
}
Vector4& Vector4::operator/=(const double& p_value)
{
	m_vec4[0] = m_vec4[0] / static_cast<float>(p_value);
	m_vec4[1] = m_vec4[1] / static_cast<float>(p_value);
	m_vec4[2] = m_vec4[2] / static_cast<float>(p_value);
	m_vec4[3] = m_vec4[3] / static_cast<float>(p_value);

	return *this;
}
Vector4 Vector4::operator*(const double& p_value)
{
	Vector4 temp(*this);
	return temp *= p_value;
}
Vector4 Vector4::operator/(const double& p_value)
{
	Vector4 temp(*this);
	return temp /= p_value;
}
#pragma endregion

#pragma region comparisonOperator
bool Vector4::operator==(Vector4& p_vec4) {

	if (m_vec4[0] == p_vec4.m_vec4[0] &&
		m_vec4[1] == p_vec4.m_vec4[1] &&
		m_vec4[2] == p_vec4.m_vec4[2] &&
		m_vec4[3] == p_vec4.m_vec4[3]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector4::operator!=(Vector4& p_vec4) {

	if (m_vec4[0] != p_vec4.m_vec4[0] ||
		m_vec4[1] != p_vec4.m_vec4[1] ||
		m_vec4[2] != p_vec4.m_vec4[2] ||
		m_vec4[3] != p_vec4.m_vec4[3]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& p_output, Vector4& vec4)
{
	p_output << '(' << vec4.x() << '/' << vec4.y() << '/' << vec4.z() << '/' << vec4.w() << ')';
	return p_output;
}

std::ostream & operator<<(std::ostream& p_output, Vector4 vec4)
{
	p_output << '(' << vec4.x() << '/' << vec4.y() << '/' << vec4.z() << '/' << vec4.w() << ')';
	return p_output;
}

