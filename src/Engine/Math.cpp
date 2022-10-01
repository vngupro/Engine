#include "Math.hpp"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

template<typename T>
Vector2<T>::Vector2(const T& x, const T& y) :
	x(x),
	y(y)
{
}