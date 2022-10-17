#pragma once
#include <Engine/Export.hpp>
#include <entt/entt.hpp>

class ENGINE_API VelocitySystem
{
public:
	VelocitySystem();
	void Update(entt::registry& registry);
};