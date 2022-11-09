#include <Engine/Shape.hpp>
#include <Engine/PhysicsSystem.hpp>

Shape::Shape() : 
	m_shape(nullptr)
{
}

Shape::~Shape()
{
	if (m_shape)
	{
		cpShapeFree(m_shape);
		//PhysicsSystem::Instance().RemoveShape(m_shape);
	}
}

void Shape::CreateShape(cpBody* body)
{	
}

float Shape::GetAngularMoment(float mass)
{
	return 0.f;
}

cpShape* Shape::GetHandle()
{
	return m_shape;
}

BoxShape::BoxShape(float width, float height, float radius /*= 1.0f*/) :
	m_width(width),
	m_height(height),
	m_radius(radius)
{
	
}

BoxShape::~BoxShape()
{

}

void BoxShape::CreateShape(cpBody* boxBody)
{
	m_shape = cpBoxShapeNew(boxBody, m_width, m_height, m_radius);
	PhysicsSystem::Instance().AddShape(m_shape);
}

float BoxShape::GetAngularMoment(float mass)
{
	return cpMomentForBox(mass, m_width, m_height);
}

CircleShape::CircleShape(float radius, Vector2f offset /*= Vector2f(0.f, 0.f)*/) :
	m_radius(radius),
	m_offset(offset)
{
}

CircleShape::~CircleShape()
{

}

void CircleShape::CreateShape(cpBody* body)
{
	m_shape = cpCircleShapeNew(body, m_radius, cpv(m_offset.x, m_offset.y));
	PhysicsSystem::Instance().AddShape(m_shape);
}

float CircleShape::GetAngularMoment(float mass)
{
	return cpMomentForCircle(mass, cpFloat(m_radius) * 2.f, cpFloat(m_radius) * 2.f, cpv(m_offset.x, m_offset.y));
}

SegmentShape::SegmentShape(Vector2f a, Vector2f b, float radius) :
	m_a(a),
	m_b(b),
	m_radius(radius)
{
}

SegmentShape::~SegmentShape()
{
}

void SegmentShape::CreateShape(cpBody* body)
{
	m_shape = cpBoxShapeNew(body, 256, 256, 0.f);
	PhysicsSystem::Instance().AddShape(m_shape);
}

float SegmentShape::GetAngularMoment(float mass)
{
	return cpMomentForSegment(mass, cpv(m_a.x, m_a.y), cpv(m_b.x, m_b.y), m_radius);
}

