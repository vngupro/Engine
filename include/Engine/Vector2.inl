#include "Vector2.hpp"
// le #pragma once n'est pas n�cessaire ici, un seul fichier va nous inclure directement et il est d�j� prot�g�

template<typename T>
Vector2<T>::Vector2(T V) :
x(V),
y(V)
{
}

template<typename T>
Vector2<T>::Vector2(T X, T Y) :
x(X),
y(Y)
{
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& vec) const
{
	return Vector2{ x + vec.x, y + vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& vec) const
{
	return Vector2{ x - vec.x, y - vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& vec) const
{
	return Vector2{ x * vec.x, y * vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T value) const
{
	return Vector2{ x * value, y * value };
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2& vec) const
{
	return Vector2{ x / vec.x, y / vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T value) const
{
	return Vector2{ x / value, y / value };
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(T value)
{
	x *= value;
	y *= value;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const Vector2& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(T value)
{
	x /= value;
	y /= value;

	return *this;
}

template<typename T>
Vector2<T> operator*(T value, const Vector2<T>& vec)
{
	return Vector2{ vec.x * value, vec.y * value };
}

template<typename T>
Vector2<T> operator/(T value, const Vector2<T>& vec)
{
	return Vector2{ vec.x / value, vec.y / value };
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
{
	return os << "Vector2(" << vec.x << ", " << vec.y << ")";
}
