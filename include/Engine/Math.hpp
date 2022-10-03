#pragma once
#include "DLLDefine.hpp"
#include <iostream>
class ENGINE_API Math
{
public:
	Math(const Math&) = delete;
	Math& operator=(const Math&) = delete;
	Math(Math&&) = delete;
	Math& operator=(Math&&) = delete;

	static Math& Get()
	{
		static Math instance;
		return instance;
	}

	static float Deg2Rad(const float& angleDeg);
	static float Rad2Deg(const float& angleRad);
private:
	Math(){}
	static float Deg2Rad_Impl(const float& angleDeg);
	static float Rad2Deg_Impl(const float& angleRad);
};

template <typename T>
class Vector2
{
public:
	// Variables
	T x;
	T y;

	// Constructor
	Vector2();
	Vector2(T x, T y);

	// Operators Overloading
	Vector2<T> operator+(const Vector2<T>& v) const;
	Vector2<T> operator+=(const Vector2<T>& v);
	Vector2<T> operator-(const Vector2<T>& v) const;
	Vector2<T> operator-=(const Vector2<T>& v);
	Vector2<T> operator*(const float& f) const;
	Vector2<T> operator*=(const float& f);
	Vector2<T> operator/(const float& f) const;
	Vector2<T> operator/=(const float& f);
	Vector2<T> operator*(const int& f) const;
	Vector2<T> operator*=(const int& f);
	Vector2<T> operator/(const int& f) const;
	Vector2<T> operator/=(const int& f);

	// Functions
	Vector2<T> Add(const Vector2<T>& v) const;
	Vector2<T> Substract(const Vector2<T>& v) const;
	Vector2<T> Multiply(const T& f) const;
	Vector2<T> Divide(const T& f) const;
 };

class ENGINE_API Transform
{
public:
	// Variables
	Vector2<float> position;
	float rotation;
	Vector2<float> scale;
	Transform* parent;

	// Constructor
	Transform();
	Transform(const Vector2<float>& position, const float& rotation = 0.f, const Vector2<float>& scale = Vector2<float>(1.f, 1.f));

	// Functions
	void SetPosition(const Vector2<float>& _position);
	void SetRotation(const float& _rotation);
	void SetScale(const Vector2<float>& _scale);
	void Translate(const Vector2<float>& _position);
	void Rotate(const float& _rotation);
	void Scale(const Vector2<float>& _scale);
	Vector2<float> TransformPoint(const Vector2<float>& position);
	void SetParent(Transform* parent);
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v)
{
	stream << v.x << ", " << v.y;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Transform& t)
{
	stream << "position : " << t.position.x << ", " << t.position.y << std::endl;
	stream << "rotation : " << t.rotation << std::endl;
	stream << "scale : " << t.scale.x << ", " << t.scale.y;
	return stream;
}


template <typename T>
Vector2<T>::Vector2()
{
	x = 0.f;
	y = 0.f;
}

template <typename T>
Vector2<T>::Vector2(T x, T y) :
	x(x),
	y(y)
{
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const
{
	return Add(v);
}

template <typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2<T>& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const
{
	return Substract(v);
}

template <typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2<T>& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const float& f) const
{
	return Multiply(f);
}

template <typename T>
Vector2<T> Vector2<T>::operator*=(const float& f)
{
	x *= f;
	y *= f;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const float& f) const
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2<float>(0.f, 0.f);
	}
	return Divide(f);
}

template <typename T>
Vector2<T> Vector2<T>::operator/=(const float& f)
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2<float>(0.f, 0.f);
	}
	x /= f;
	y /= f;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const int& f) const
{
	return Multiply(f);
}

template <typename T>
Vector2<T> Vector2<T>::operator*=(const int& f)
{
	x *= f;
	y *= f;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const int& f) const
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2<float>(0.f, 0.f);
	}
	return Divide(f);
}

template <typename T>
Vector2<T> Vector2<T>::operator/=(const int& f)
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2<float>(0.f, 0.f);
	}
	x /= f;
	y /= f;
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::Add(const Vector2<T>& v) const
{
	return Vector2<T>(x + v.x, y + v.y);
}

template <typename T>
Vector2<T> Vector2<T>::Substract(const Vector2<T>& v) const
{
	return Vector2<T>(x - v.x, y - v.y);
}

template <typename T>
Vector2<T> Vector2<T>::Multiply(const T& f) const
{
	return Vector2<T>(x * f, y * f);
}

template <typename T>
Vector2<T> Vector2<T>::Divide(const T& f) const
{
	if (f == 0.f)
	{
		std::cerr << "Division by 0" << std::endl;
		return Vector2<float>(0.f, 0.f);
	}

	return Vector2<T>(x / f, y / f);
}