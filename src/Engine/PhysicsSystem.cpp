#include <Engine/PhysicsSystem.hpp>
#include <stdexcept>
#include<Engine/Shape.hpp>
//#include <chipmunk/chipmunk.h>

PhysicsSystem::PhysicsSystem(entt::registry& registry) :
	m_registry(registry)
{

	//if (s_instance != nullptr)
	//	throw std::runtime_error("only one Physics system can be created");

	//s_instance = this;

	m_space = cpSpaceNew();
	cpSpaceSetGravity(m_space, { 0.f, 981.f });
	cpSpaceSetDamping(m_space, 0.5f);
}

PhysicsSystem::~PhysicsSystem()
{
	if (m_space != nullptr)
	{
		cpSpaceFree(m_space);
	}

	//s_instance = nullptr;
}

cpSpace* PhysicsSystem::GetHandle()
{
	return m_space;
}

cpVect PhysicsSystem::GetGravity()
{
	return cpSpaceGetGravity(m_space);
}

cpFloat PhysicsSystem::GetDamping()
{
	return cpSpaceGetDamping(m_space);
}

void PhysicsSystem::SetGravity(const cpVect& gravity)
{
	return cpSpaceSetGravity(m_space, gravity);
}

void PhysicsSystem::SetDamping(cpFloat damping)
{
	return cpSpaceSetDamping(m_space, damping);
}

void PhysicsSystem::AddBody(cpBody* body)
{
	cpSpaceAddBody(m_space, body);
}

void PhysicsSystem::Update(float deltaTime)
{
	m_physicsAccumulator += deltaTime;
	while (m_physicsAccumulator >= m_physicsTimestep)
	{
		cpSpaceStep(m_space, m_physicsTimestep);
		m_physicsAccumulator -= m_physicsTimestep;
	}
}

//void PhysicsSystem::AddToSpace(std::shared_ptr<Shape> shape)
//{
//	s_instance->AddToSpace_Impl(shape);
//}
//
//void PhysicsSystem::AddToSpace_Impl(std::shared_ptr<Shape> shape)
//{
//	cpSpaceAddShape(m_space, shape.get()->GetHandle());
//}