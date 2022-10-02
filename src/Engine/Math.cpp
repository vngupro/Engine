#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "Math.hpp"
#include <iostream>

float Math::Deg2Rad(const float& angleDeg)
{
	return Get().Deg2Rad_Impl(angleDeg);
}

float Math::Rad2Deg(const float& angleRad)
{
	return Get().Rad2Deg_Impl(angleRad);
}

float Math::Deg2Rad_Impl(const float& angleDeg)
{
	return angleDeg * (M_PI / 180);
}

float Math::Rad2Deg_Impl(const float& angleRad)
{
	return angleRad * (180 / M_PI);
}

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Add(v);
}

Vector2 Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Substract(v);
}

Vector2 Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator*(const float& f) const
{
	return Multiply(f);
}

Vector2 Vector2::operator*=(const float& f)
{
	x *= f;
	y *= f;
	return *this;
}

Vector2 Vector2::operator/(const float& f) const
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2(0.f, 0.f);
	}
	return Divide(f);
}

Vector2 Vector2::operator/=(const float& f)
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2(0.f, 0.f);
	}
	x /= f;
	y /= f;
	return *this;
}

Vector2 Vector2::Add(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::Substract(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::Multiply(const float& f) const
{
	return Vector2(x * f, y * f);
}

Vector2 Vector2::Divide(const float& f) const
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2(0.f, 0.f);
	}

	return Vector2(x / f, y / f);
}

Transform::Transform() :
	position(Vector2(0.f, 0.f)),
	rotation(0.f),
	scale(Vector2(1.f, 1.f)),
	parent(nullptr)
{
}

Transform::Transform(const Vector2& position, const float& rotation, const Vector2& scale) :
	position(position),
	rotation(rotation),
	scale(scale),
	parent(nullptr)
{
}

void Transform::SetPosition(const Vector2& _position)
{
	position = _position;
}

void Transform::SetRotation(const float& _rotation)
{
	rotation = _rotation;
}

void Transform::SetScale(const Vector2& _scale)
{
	scale = _scale;
}

void Transform::Translate(const Vector2& _position)
{
	position += _position;
}

void Transform::Rotate(const float& _rotation)
{
	
	rotation += _rotation;
}

void Transform::Scale(const Vector2& _scale)
{
	scale += _scale;
}

void Transform::SetParent(Transform* _parent)
{
	parent = _parent;
}

Vector2 Transform::TransformPoint(const Vector2& _position)
{
	Vector2 ret = _position;
	ret.x *= scale.x;
	ret.y *= scale.y;

	float rad = Math::Deg2Rad(rotation);

	float new_x = (ret.x * cos(rad) - ret.y * sin(rad)) + position.x;
	float new_y = (ret.x * sin(rad) + ret.y * cos(rad)) + position.y;
	ret = Vector2(new_x, new_y);
	return ret;
}