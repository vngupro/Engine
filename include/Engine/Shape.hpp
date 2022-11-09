#pragma once
#include <Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <Engine/Vector2.hpp>

class ENGINE_API Shape
{
public:
	Shape();
	~Shape();

	virtual void CreateShape(cpBody* body);
	cpShape* GetHandle();

protected:
	cpShape* m_shape;
};

class ENGINE_API BoxShape : public Shape
{
public:
	BoxShape(float width, float height, float radius = 1.0f);
	~BoxShape();

	 void CreateShape(cpBody* body) override;
private:
	float m_width;
	float m_height;
	float m_radius;
};

class ENGINE_API CircleShape : public Shape
{
public:
	CircleShape(float radius, Vector2f offset = Vector2f(0.f, 0.f));
	~CircleShape();

	void CreateShape(cpBody* body) override;
private:
	float m_radius;
	Vector2f m_offset;
};

class ENGINE_API SegmentShape : public Shape
{
public:
	SegmentShape(Vector2f a, Vector2f b, float radius);
	~SegmentShape();

	void CreateShape(cpBody* body) override;
;private:
	Vector2f m_a;
	Vector2f m_b;
	float m_radius;
};