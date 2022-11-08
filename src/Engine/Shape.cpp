#include <Engine/Shape.hpp>

Shape::Shape()
{

}

Shape::~Shape()
{
	cpShapeFree(m_shape);
}

cpShape* Shape::GetHandle()
{
	return m_shape;
}

BoxShape::BoxShape()
{
	
}

CircleShape::CircleShape(float radius)
{

}

CircleShape::~CircleShape()
{

}

SegmentShape::SegmentShape()
{

}

