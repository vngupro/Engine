#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Matrix3.hpp>
#include <A4Engine/Vector2.hpp>
#include <vector>

class ChipmunkBody;
class ChipmunkShape;
class Model;

struct A4ENGINE_API CollisionShape
{
	virtual ~CollisionShape();

	virtual ChipmunkShape Build(ChipmunkBody& body, const Vector2f& offset = Vector2f(0.f, 0.f)) const = 0;
	virtual float ComputeMoment(float mass, const Vector2f& offset = Vector2f(0.f, 0.f)) const = 0;

	float friction = 0.9f;
};

struct A4ENGINE_API BoxShape : CollisionShape //< pour une struct, l'h�ritage est public par d�faut
{
	BoxShape(float width, float height, float radius = 0.f);
	BoxShape(float x, float y, float width, float height, float radius = 0.f);

	ChipmunkShape Build(ChipmunkBody& body, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;
	float ComputeMoment(float mass, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;

	float x, y, width, height;
	float radius;
};

struct A4ENGINE_API CircleShape : CollisionShape //< pour une struct, l'h�ritage est public par d�faut
{
	CircleShape(float radius);

	ChipmunkShape Build(ChipmunkBody& body, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;
	float ComputeMoment(float mass, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;

	float radius;
};

struct A4ENGINE_API ConvexShape : CollisionShape //< pour une struct, l'h�ritage est public par d�faut
{
	ConvexShape(std::vector<Vector2f> pos, float radius = 0.f);
	ConvexShape(const Model& model, Matrix3f transformation = Matrix3f::Identity(), float radius = 0.f);

	ChipmunkShape Build(ChipmunkBody& body, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;
	float ComputeMoment(float mass, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;

	std::vector<Vector2f> positions;
	float radius;
};

struct A4ENGINE_API SegmentShape : CollisionShape //< pour une struct, l'h�ritage est public par d�faut
{
	SegmentShape(const Vector2f& from, const Vector2f& to, float radius = 0.f);

	ChipmunkShape Build(ChipmunkBody& body, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;
	float ComputeMoment(float mass, const Vector2f& offset = Vector2f(0.f, 0.f)) const override;

	Vector2f from;
	Vector2f to;
	float radius;
};