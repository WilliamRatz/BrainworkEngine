
#include "BWMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"


Vector3::Vector3()
{
	m_vec3[0] = NULL;
	m_vec3[1] = NULL;
	m_vec3[2] = NULL;
}
Vector3::Vector3(float p_x, float p_y, float p_z)
{
	m_vec3[0] = p_x;
	m_vec3[1] = p_y;
	m_vec3[2] = p_z;
}
Vector3::Vector3(const Vector3& p_vec3)
{
	m_vec3 = p_vec3.m_vec3;
}

#pragma region Methods
void Vector3::normalize()
{
	*this = Vector3(this->x() / Vector3::length(*this), this->y() / Vector3::length(*this), this->z() / Vector3::length(*this));
}
unsigned int Vector3::getHashCode() 
{
	return (((static_cast<unsigned int>(m_vec3[0]) * 397) ^ static_cast<unsigned int>(m_vec3[1])) * 397) ^ static_cast<unsigned int>(m_vec3[2]);
}

float Vector3::length(const Vector3& p_vec3)
{
	return static_cast<float>(BWMath::sqrt(BWMath::pow(Vector3::x(p_vec3), 2) + BWMath::pow(Vector3::y(p_vec3), 2) + BWMath::pow(Vector3::z(p_vec3), 2)));
}
float Vector3::dot(const Vector3& p_vec3_1, const Vector3& p_vec3_2)
{
	return Vector3::x(p_vec3_1) * Vector3::x(p_vec3_2) + Vector3::y(p_vec3_1) * Vector3::y(p_vec3_2) + Vector3::z(p_vec3_1) * Vector3::z(p_vec3_2);
}
Vector3 Vector3::cross(const Vector3& p_vec3_1, const Vector3& p_vec3_2)
{
	return Vector3((Vector3::y(p_vec3_1) * Vector3::z(p_vec3_2)) - (Vector3::z(p_vec3_1) * Vector3::y(p_vec3_2)),
		(Vector3::z(p_vec3_1) * Vector3::x(p_vec3_2)) - (Vector3::x(p_vec3_1) * Vector3::z(p_vec3_2)),
		(Vector3::x(p_vec3_1) * Vector3::y(p_vec3_2)) - (Vector3::y(p_vec3_1) * Vector3::x(p_vec3_2)));
}
Vector3 Vector3::normalized(const Vector3& p_vec3) {

	return Vector3(Vector3::x(p_vec3) / Vector3::length(p_vec3), Vector3::y(p_vec3) / Vector3::length(p_vec3), Vector3::z(p_vec3) / Vector3::length(p_vec3));
}
Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}
Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}
#pragma endregion

#pragma region castOperations
Vector3::operator Vector2()
{
	return Vector2(x(), y());
}
Vector3::operator Vector4()
{
	return Vector4(x(), y(), z(), 0);
}
Vector3::operator Quaternion()
{
	return Quaternion(x(), y(), z(), 0);
}
Vector3::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> mat;
	mat[0][3] = x();
	mat[1][3] = y();
	mat[2][3] = z();
	return mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Vector3::operator=(const Vector3& p_vec3) {

	m_vec3[0] = p_vec3.m_vec3[0];
	m_vec3[1] = p_vec3.m_vec3[1];
	m_vec3[2] = p_vec3.m_vec3[2];
}
Vector3 Vector3::operator-()
{
	m_vec3[0] = -m_vec3[0];
	m_vec3[1] = -m_vec3[1];
	m_vec3[2] = -m_vec3[2];

	return *this;
}
Vector3& Vector3::operator+=(const Vector3& p_vec3) {
	m_vec3[0] = m_vec3[0] + p_vec3.m_vec3[0];
	m_vec3[1] = m_vec3[1] + p_vec3.m_vec3[1];
	m_vec3[2] = m_vec3[2] + p_vec3.m_vec3[2];

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& p_vec3) {
	m_vec3[0] = m_vec3[0] - p_vec3.m_vec3[0];
	m_vec3[1] = m_vec3[1] - p_vec3.m_vec3[1];
	m_vec3[2] = m_vec3[2] - p_vec3.m_vec3[2];

	return *this;
}
Vector3& Vector3::operator/=(const Vector3& p_vec3) {
	m_vec3[0] = m_vec3[0] / p_vec3.m_vec3[0];
	m_vec3[1] = m_vec3[1] / p_vec3.m_vec3[1];
	m_vec3[2] = m_vec3[2] / p_vec3.m_vec3[2];

	return *this;
}
Vector3 Vector3::operator+(const Vector3& p_vec3) {

	Vector3 temp(*this);
	return temp += p_vec3;
}
Vector3 Vector3::operator-(const Vector3& p_vec3) {

	Vector3 temp(*this);
	return temp -= p_vec3;
}
Vector3 Vector3::operator/(const Vector3& p_vec3) {

	Vector3 temp(*this);
	return temp /= p_vec3;
}

Vector3& Vector3::operator*=(const int& p_value)
{
	m_vec3[0] = m_vec3[0] * static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] * static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] * static_cast<float>(p_value);

	return *this;
}
Vector3& Vector3::operator/=(const int& p_value) 
{
	m_vec3[0] = m_vec3[0] / static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] / static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] / static_cast<float>(p_value);

	return *this;
}
Vector3 Vector3::operator*(const int& p_value) 
{
	Vector3 temp(*this);
	return temp *= p_value;
}
Vector3 Vector3::operator/(const int& p_value) 
{
	Vector3 temp(*this);
	return temp /= p_value;
}

Vector3& Vector3::operator*=(const float& p_value) 
{
	m_vec3[0] = m_vec3[0] * static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] * static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] * static_cast<float>(p_value);

	return *this;
}
Vector3& Vector3::operator/=(const float& p_value) 
{
	m_vec3[0] = m_vec3[0] / static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] / static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] / static_cast<float>(p_value);

	return *this;
}
Vector3 Vector3::operator*(const float& p_value) 
{
	Vector3 temp(*this);
	return temp *= p_value;
}
Vector3 Vector3::operator/(const float& p_value) 
{
	Vector3 temp(*this);
	return temp /= p_value;
}

Vector3& Vector3::operator*=(const double& p_value) 
{
	m_vec3[0] = m_vec3[0] * static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] * static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] * static_cast<float>(p_value);

	return *this;
}
Vector3& Vector3::operator/=(const double& p_value) 
{
	m_vec3[0] = m_vec3[0] / static_cast<float>(p_value);
	m_vec3[1] = m_vec3[1] / static_cast<float>(p_value);
	m_vec3[2] = m_vec3[2] / static_cast<float>(p_value);

	return *this;
}
Vector3 Vector3::operator*(const double& p_value) 
{
	Vector3 temp(*this);
	return temp *= p_value;
}
Vector3 Vector3::operator/(const double& p_value) 
{
	Vector3 temp(*this);
	return temp /= p_value;
}
#pragma endregion

#pragma region comparisonOperator
bool Vector3::operator==(Vector3& p_vec3) {

	if (m_vec3[0] == p_vec3.m_vec3[0] &&
		m_vec3[1] == p_vec3.m_vec3[1] &&
		m_vec3[2] == p_vec3.m_vec3[2]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector3::operator!=(Vector3& p_vec3) {

	if (m_vec3[0] != p_vec3.m_vec3[0] ||
		m_vec3[1] != p_vec3.m_vec3[1] ||
		m_vec3[2] != p_vec3.m_vec3[2]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& p_output, Vector3& p_vec3)
{
	p_output << '(' << p_vec3.x() << '/' << p_vec3.y() << '/' << p_vec3.z() << ')';
	return p_output;
}

std::ostream& operator<<(std::ostream& p_output, Vector3 p_vec3)
{
	p_output << '(' << p_vec3.x() << '/' << p_vec3.y() << '/' << p_vec3.z() << ')';
	return p_output;
}

