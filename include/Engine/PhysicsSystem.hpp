#pragma once
#include <Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>

class Shape;
//class cpSpace;
//class cpVect;
//class cpFloat;

class ENGINE_API PhysicsSystem
{
public:
	PhysicsSystem(entt::registry& registry);
	~PhysicsSystem();

	cpSpace* GetHandle();
	cpVect GetGravity();
	cpFloat GetDamping();
	void SetGravity(const cpVect& gravity);
	void SetDamping(cpFloat damping);
	void AddBody(cpBody* body);
	void AddShape(cpShape* shape);
	void RemoveBody(cpBody* body);
	void RemoveShape(cpShape* shape);
	void Update(float deltaTime);
	static PhysicsSystem& Instance();
	//static void AddToSpace(std::shared_ptr<Shape> shape);

private:
	entt::registry& m_registry;
	cpSpace* m_space;
	float m_physicsTimestep = 1.f / 50.f;
	float m_physicsAccumulator = 0.f;

	//void AddToSpace_Impl(std::shared_ptr<Shape> shape);
	static PhysicsSystem* s_instance;
};