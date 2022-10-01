#pragma once
#include "DLLDefine.hpp"

template<typename T>
class ENGINE_API Vector2
{

public:
	T x;
	T y;

	Vector2(const T& x, const T& y);
	Vector2();

	void down();
	void left();
	void right();
	void up();
	void zero();
	void one();
	void negativeInfinity();
	void positiveInfinity();

private:
	Vector2 operator+(const Vector2& v);
	Vector2 operator+=(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator-=(const Vector2& v);
	Vector2 operator*(const T&f);
	Vector2 operator*=(const T& f);
	Vector2 operator/(const T& f);
	Vector2 operator/=(const T& f);
};

class ENGINE_API Transform
{
public:
	Transform(){}

	//Vector2<float> position;
	//float rotation;		// en deg
	//Vector2<float> scale;

	void SetPosition(const Vector2<float>& position);
	void SetRotation(const float& rotation);
	void SetScale(const Vector2<float>& scale);
	void SetParent(Transform parent);
	void TransformPoint(const Vector2<float>& point);
};



class ENGINE_API Matrix3
{

};