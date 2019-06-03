
#include "BWMath.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"


Vector2::Vector2()
{
	m_vec2[0] = NULL;
	m_vec2[1] = NULL;
}
Vector2::Vector2(float p_x, float p_y)
{
	m_vec2[0] = p_x;
	m_vec2[1] = p_y;
}
Vector2::Vector2(const Vector2& p_vec2)
{
	m_vec2 = p_vec2.m_vec2;
}

#pragma region Methods
void Vector2::normalize()
{
	*this = Vector2(this->x() / Vector2::length(*this), this->y() / Vector2::length(*this));
}
unsigned int Vector2::getHashCode() {

	return (static_cast<unsigned int>(m_vec2[0]) * 397) ^ static_cast<unsigned int>(m_vec2[1]);
}

Vector2 Vector2::normalized(const Vector2& p_vec2) {

	return Vector2(Vector2::x(p_vec2) / Vector2::length(p_vec2), Vector2::y(p_vec2) / Vector2::length(p_vec2));
}
float Vector2::length(const Vector2& p_vec2)
{
	return static_cast<float>(BWMath::sqrt(BWMath::pow(Vector2::x(p_vec2), 2) + BWMath::pow(Vector2::y(p_vec2), 2)));
}
float  Vector2::dot(const Vector2& p_vec2_1, const Vector2& p_vec2_2)
{
	return Vector2::x(p_vec2_1) * Vector2::x(p_vec2_2) + Vector2::y(p_vec2_1) * Vector2::y(p_vec2_2);
}
Vector2 Vector2::One()
{
	return Vector2(1, 1);
}
Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}
#pragma endregion

#pragma region castOperations
Vector2::operator Vector3()
{
	return Vector3(x(), y(), 0);
}
Vector2::operator Vector4()
{
	return Vector4(x(), y(), 0, 0);
}
Vector2::operator Quaternion()
{
	return Quaternion(x(), y(), 0, 0);
}
Vector2::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> p_mat;
	p_mat[0][3] = x();
	p_mat[1][3] = y();
	
	return p_mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Vector2::operator=(const Vector2& p_vec2) {

	m_vec2[0] = p_vec2.m_vec2[0];
	m_vec2[1] = p_vec2.m_vec2[1];
}
Vector2 Vector2::operator-()
{
	m_vec2[0] = -m_vec2[0];
	m_vec2[1] = -m_vec2[1];

	return *this;
}
Vector2 Vector2::operator+(const Vector2& p_vec2) {

	Vector2 temp(*this);
	return temp -= p_vec2;
}
Vector2 Vector2::operator-(const Vector2& p_vec2) {

	Vector2 temp(*this);
	return temp -= p_vec2;
}
Vector2 Vector2::operator/(const Vector2& p_vec2) {

	Vector2 temp(*this);
	return temp -= p_vec2;
}
Vector2& Vector2::operator+=(const Vector2& p_vec2) {
	m_vec2[0] = m_vec2[0] + p_vec2.m_vec2[0];
	m_vec2[1] = m_vec2[1] + p_vec2.m_vec2[1];

	return *this;
}
Vector2& Vector2::operator-=(const Vector2& p_vec2) {
	m_vec2[0] = m_vec2[0] - p_vec2.m_vec2[0];
	m_vec2[1] = m_vec2[1] - p_vec2.m_vec2[1];

	return *this;
}
Vector2& Vector2::operator/=(const Vector2& p_vec2) {
	m_vec2[0] = m_vec2[0] / p_vec2.m_vec2[0];
	m_vec2[1] = m_vec2[1] / p_vec2.m_vec2[1];

	return *this;
}

Vector2& Vector2::operator*=(const int& p_value)
{
	m_vec2[0] = m_vec2[0] * static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] * static_cast<float>(p_value);

	return *this;
}
Vector2& Vector2::operator/=(const int& p_value)
{
	m_vec2[0] = m_vec2[0] / static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] / static_cast<float>(p_value);

	return *this;
}
Vector2 Vector2::operator*(const int& p_value)
{
	Vector2 temp(*this);
	return temp *= p_value;
}
Vector2 Vector2::operator/(const int& p_value)
{
	Vector2 temp(*this);
	return temp /= p_value;
}

Vector2& Vector2::operator*=(const float& p_value)
{
	m_vec2[0] = m_vec2[0] * static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] * static_cast<float>(p_value);

	return *this;
}
Vector2& Vector2::operator/=(const float& p_value)
{
	m_vec2[0] = m_vec2[0] / static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] / static_cast<float>(p_value);

	return *this;
}
Vector2 Vector2::operator*(const float& p_value)
{
	Vector2 temp(*this);
	return temp *= p_value;
}
Vector2 Vector2::operator/(const float& p_value)
{
	Vector2 temp(*this);
	return temp /= p_value;
}

Vector2& Vector2::operator*=(const double& p_value)
{
	m_vec2[0] = m_vec2[0] * static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] * static_cast<float>(p_value);

	return *this;
}
Vector2& Vector2::operator/=(const double& p_value)
{
	m_vec2[0] = m_vec2[0] / static_cast<float>(p_value);
	m_vec2[1] = m_vec2[1] / static_cast<float>(p_value);

	return *this;
}
Vector2 Vector2::operator*(const double& p_value)
{
	Vector2 temp(*this);
	return temp *= p_value;
}
Vector2 Vector2::operator/(const double& p_value)
{
	Vector2 temp(*this);
	return temp /= p_value;
}
#pragma endregion

#pragma region comparisonOperator
bool Vector2::operator==(Vector2& p_vec) {

	if (m_vec2[0] == p_vec.m_vec2[0] &&
		m_vec2[1] == p_vec.m_vec2[1]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector2::operator!=(Vector2& p_vec) {

	if (m_vec2[0] != p_vec.m_vec2[0] ||
		m_vec2[1] != p_vec.m_vec2[1]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& p_output, Vector2& p_vec2)
{
	p_output << '(' << p_vec2.x() << '/' << p_vec2.y() << ')';
	return p_output;
}

std::ostream & operator<<(std::ostream& p_output, Vector2 p_vec2)
{
	p_output << '(' << p_vec2.x() << '/' << p_vec2.y() << ')';
	return p_output;
}
