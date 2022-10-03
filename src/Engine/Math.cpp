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

Transform::Transform() :
	position(Vector2<float>(0.f, 0.f)),
	rotation(0.f),
	scale(Vector2<float>(1.f, 1.f)),
	parent(nullptr)
{
}

Transform::Transform(const Vector2<float>& position, const float& rotation, const Vector2<float>& scale) :
	position(position),
	rotation(rotation),
	scale(scale),
	parent(nullptr)
{
}

Transform::~Transform()
{
	if (parent != nullptr)
	{
		parent = nullptr;
	}
}

void Transform::SetPosition(const Vector2<float>& _position)
{
	position = _position;
}

void Transform::SetRotation(const float& _rotation)
{
	rotation = _rotation;
}

void Transform::SetScale(const Vector2<float>& _scale)
{
	scale = _scale;
}

void Transform::Translate(const Vector2<float>& _position)
{
	position += _position;
}

void Transform::Rotate(const float& _rotation)
{
	
	rotation += _rotation;
}

void Transform::Scale(const Vector2<float>& _scale)
{
	scale += _scale;
}

void Transform::SetParent(Transform* _parent)
{
	parent = _parent;
}

Vector2<float> Transform::TransformPoint(const Vector2<float>& _position)
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