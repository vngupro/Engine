#include <Engine/PhysicsSystem.hpp>
#include <stdexcept>
#include<Engine/Shape.hpp>
#include<Engine/RigidbodyComponent.hpp>
#include<Engine/Transform.hpp>
//#include <chipmunk/chipmunk.h>

PhysicsSystem* PhysicsSystem::s_instance = nullptr;

PhysicsSystem::PhysicsSystem(entt::registry& registry) :
	m_registry(registry)
{

	if (s_instance != nullptr)
		throw std::runtime_error("only one Physics system can be created");

	s_instance = this;

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

	s_instance = nullptr;
}

PhysicsSystem& PhysicsSystem::Instance()
{
	if (!s_instance)
		throw std::runtime_error("InputManager hasn't been instantied");

	return *s_instance;
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
	if(m_space && body)
		cpSpaceAddBody(m_space, body);
}

void PhysicsSystem::AddShape(cpShape* shape)
{
	if(m_space && shape)
		cpSpaceAddShape(m_space, shape);
}

void PhysicsSystem::RemoveBody(cpBody* body)
{
	if(m_space && body)
		cpSpaceRemoveBody(m_space, body);
}

void PhysicsSystem::RemoveShape(cpShape* shape)
{
	if(m_space && shape)
		cpSpaceRemoveShape(m_space, shape);
}


void PhysicsSystem::Update(float deltaTime)
{
	m_physicsAccumulator += deltaTime;
	while (m_physicsAccumulator >= m_physicsTimestep)
	{
		cpSpaceStep(m_space, m_physicsTimestep);
		m_physicsAccumulator -= m_physicsTimestep;
	}

	auto view = m_registry.view<RigidbodyComponent, Transform>();

	for (auto& entity : view)
	{
		auto& entityRigidBody = view.get<RigidbodyComponent>(entity);
		auto& entityTransform = view.get<Transform>(entity);

		cpVect pos = entityRigidBody.GetPosition();
		float rot = entityRigidBody.GetAngle() * Rad2Deg;

		entityTransform.SetPosition(Vector2f(pos.x, pos.y));
		entityTransform.SetRotation(rot);
	}
}