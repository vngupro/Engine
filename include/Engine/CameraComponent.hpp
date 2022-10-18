#pragma once
#include <entt/entt.hpp>
#include <Engine/Transform.hpp>

//class Transform; // why incomplete type not authorized error ???

class CameraComponent
{
	// you have a camera if move right entity move left
	// if rotate -> entity has a circular motion
public:
	CameraComponent();
	CameraComponent(const Transform& transform, int width, int height);

public:
	Transform m_transform;
	int m_width;
	int m_height;
};