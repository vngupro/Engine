#pragma once
#include<Engine/Export.hpp>
#include<chipmunk/chipmunk.h>
#include<Engine/Vector2.hpp>
#include<vector>

class Shape;

class ENGINE_API RigidbodyComponent
{
public:
	
	RigidbodyComponent();
	RigidbodyComponent(float mass);
	~RigidbodyComponent();

	void SetPosition(Vector2f pos);
	void SetRotation(float angle);
	cpVect GetPosition();
	cpFloat GetAngle();
	
	cpBody* GetHandle();
	void AddShape(std::shared_ptr<Shape> shape);
	void RemoveShape(std::shared_ptr<Shape> shape);

private:
	cpBody* m_body;
	std::vector<std::shared_ptr<Shape>> m_shapes;
};