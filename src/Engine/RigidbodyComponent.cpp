#include <Engine/RigidbodyComponent.hpp>
#include <Engine/Math.hpp>
#include <Engine/Shape.hpp>
//#include <Engine/PhysicsSystem.hpp>
//RigidbodyComponent::RigidbodyComponent(RigidbodyType bodyType, cpFloat mass /*= 100.f*/, cpFloat moment /*= cpMomentForBox(100.f, 256, 256)*/)
//{
//	switch (bodyType)
//	{
//	case RigidbodyComponent::Dynamic:
//		m_body = cpBodyNew(mass, moment);
//		break;
//	case RigidbodyComponent::Kinematic:
//		m_body = cpBodyNewKinematic();
//		break;
//	case RigidbodyComponent::Static:
//		m_body = cpBodyNewStatic();
//		break;
//	default:
//		break;
//	}
//}

RigidbodyComponent::RigidbodyComponent()
{
}

RigidbodyComponent::RigidbodyComponent(float mass)
{
	m_body = cpBodyNew(mass, 0);
}

RigidbodyComponent::~RigidbodyComponent()
{
	for (std::shared_ptr<Shape> m_shape : m_shapes)
	{
		RemoveShape(m_shape);
	}
	
	if (m_body)
	{
		cpBodyFree(m_body);
	}
}

cpBody* RigidbodyComponent::GetHandle()
{
	return m_body;
}

void RigidbodyComponent::SetPosition(Vector2f pos)
{
	cpBodySetPosition(m_body, cpv(pos.x, pos.y));
}

void RigidbodyComponent::SetRotation(float angle)
{
	cpBodySetAngle(m_body, angle * Rad2Deg);
}

cpVect RigidbodyComponent::GetPosition()
{
	return cpBodyGetPosition(m_body);
}

cpFloat RigidbodyComponent::GetAngle()
{
	return cpBodyGetAngle(m_body) * Rad2Deg;
}

void RigidbodyComponent::AddShape(std::shared_ptr<Shape> shape)
{
	m_shapes.emplace_back(shape);
	//PhysicsSystem::AddToSpace(shape);
}

void RigidbodyComponent::RemoveShape(std::shared_ptr<Shape> shape)
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		if (*it == shape)
		{	
			//cpShapeFree(shape->GetHandle());
			it = m_shapes.erase(it);
			
			break;
		}
	}
}
