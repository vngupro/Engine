#pragma once
#include <string>

struct Position
{
	Position(float X, float Y) :
		x(X),
		y(Y)
	{
	}

	float x, y;
};

struct Velocity
{
	Velocity(float X, float Y) :
		x(X),
		y(Y)
	{
	}

	float x, y;
};

struct Name
{
	Name(std::string Name) :
		name(std::move(Name))
	{
	}

	std::string name;
};

//class VelocityComponent
//{
//	Velocity velocity;
//};