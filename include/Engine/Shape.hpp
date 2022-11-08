#pragma once
#include <Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <Engine/Vector2.hpp>

class ENGINE_API Shape
{
public:
	Shape();
	~Shape();

	//virtual void CreateShape();
	cpShape* GetHandle();

protected:
	cpShape* m_shape;
};

class ENGINE_API BoxShape : public Shape
{
public:
	BoxShape();
	~BoxShape();

	 //void CreateShape() override;
private:
	float m_width;
	float m_height;
};

class ENGINE_API CircleShape : public Shape
{
public:
	CircleShape(float radius);
	~CircleShape();

	//void CreateShape() override;
private:
	float m_radius;
	Vector2f offset;
};

class ENGINE_API SegmentShape : public Shape
{
public:
	SegmentShape();
	~SegmentShape();

	//void CreateShape() override;
;private:
	Vector2f a;
	Vector2f b;
	float radius;
};