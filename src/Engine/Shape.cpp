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
		//PhysicsSystem::RemoveShape();
	}
}

void Shape::CreateShape(cpBody* body)
{
	PhysicsSystem::Instance()->AddShape(m_shape);
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
}



