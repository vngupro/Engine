#pragma once
#include<Engine/Export.hpp>
#include<SDL.h>
#include <entt/entt.hpp>

class Sprite;
class Transform;
class SDLppRenderer;
class CameraComponent;

class ENGINE_API RenderSystem
{
public:
	RenderSystem();
	void Update(entt::registry& registry, SDLppRenderer& renderer);
	void Update(entt::registry& registry, SDLppRenderer& renderer, CameraComponent& camera);
};