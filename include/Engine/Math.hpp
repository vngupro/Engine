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


class ENGINE_API Vector2
{
public:
	// Variables
	float x;
	float y;

	// Constructor
	Vector2();
	Vector2(float x, float y);

	// Operators Overloading
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator+=(const Vector2& v);
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator-=(const Vector2& v);
	Vector2 operator*(const float& f) const;
	Vector2 operator*=(const float& f);
	Vector2 operator/(const float& f) const;
	Vector2 operator/=(const float& f);

	// Functions
	Vector2 Add(const Vector2& v) const;
	Vector2 Substract(const Vector2& v) const;
	Vector2 Multiply(const float& f) const;
	Vector2 Divide(const float& f) const;
 };

class ENGINE_API Transform
{
public:
	// Variables
	Vector2 position;
	float rotation;
	Vector2 scale;
	Transform* parent;

	// Constructor
	Transform();
	Transform(const Vector2& position, const float& rotation = 0.f, const Vector2& scale = Vector2(1.f, 1.f));

	// Functions
	void SetPosition(const Vector2& _position);
	void SetRotation(const float& _rotation);
	void SetScale(const Vector2& _scale);
	void Translate(const Vector2& _position);
	void Rotate(const float& _rotation);
	void Scale(const Vector2& _scale);
	Vector2 TransformPoint(const Vector2& position);
	void SetParent(Transform* parent);
};

std::ostream& operator<<(std::ostream& stream, const Vector2& v)
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
#pragma region Test
//template<typename T>
//class ENGINE_API Vector2
//{
//
//public:
//	T x;
//	T y;
//
//	Vector2(const T& x, const T& y);
//	Vector2();
//
//	Vector2<T> operator+(const Vector2<T>& v) const;
//	Vector2<T> operator+=(const Vector2<T>& v) const;
//	Vector2<T> operator-(const Vector2<T>& v) const;
//	Vector2<T> operator-=(const Vector2<T>& v) const;
//	//Vector2 operator*(const Vector2& v) const;
//	//Vector2 operator*=(const Vector2& v) const;
//	//Vector2 operator/(const Vector2& v) const;
//	//Vector2 operator/=(const Vector2& v) const;
//	Vector2<T> operator*(const T& f) const;
//	Vector2<T> operator*=(const T& f) const;
//	Vector2<T> operator/(const T& f) const;
//	Vector2<T> operator/=(const T& f) const;
//
//	Vector2<T> Add(const Vector2<T>& v) const;
//	Vector2<T> Substract(const Vector2<T>& v) const;
//	//Vector2 Multiply(const Vector2& v) const;
//	Vector2<T> Multiply(const T& f) const;
//	//Vector2 Divide(const Vector2& v) const;
//	Vector2<T> Divide(const T& f) const;
//	//static Vector2 down();
//	//static Vector2 left();
//	//static Vector2 right();
//	//static Vector2 up();
//	//static Vector2 zero();
//	//static Vector2 one();
//};

//class ENGINE_API Transform
//{
//public:
//	Transform();
//
//	Vector2<float> position;
//	float rotation = 0.f;		// en deg
//	Vector2<float> scale;
//
//	void SetPosition(const Vector2<float>& position);
//	void SetRotation(const float& rotation);
//	void SetScale(const Vector2<float>& scale);
//	//void Translate(const Vector2<float>& position);
//	//void Rotate(const Vector2<float>& rotation);
//	//void Scale(const Vector2<float>& scale);
//	void SetParent(const Transform& parent);
//	void TransformPoint(const Vector2<float>& point);
//};


//class ENGINE_API Matrix3
//{
//
//};
#pragma endregion // Test