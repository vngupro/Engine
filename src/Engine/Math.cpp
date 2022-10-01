#include "Math.hpp"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

template<typename T>
Vector2<T>::Vector2(const T& x, const T& y) :
	x(x),
	y(y)
{
}

template<typename T>
Vector2<T>::Vector2()
{
}

Transform::Transform(){}

void Transform::SetPosition(const Vector2<float>& position)
{

}

void Transform::SetRotation(const float& rotation)
{

}

void Transform::SetScale(const Vector2<float>& scale)
{

}

void Transform::SetParent(Transform parent)
{

}

void Transform::TransformPoint(const Vector2<float>& point)
{

}