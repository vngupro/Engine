#include <Engine/RenderSystem.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Transform.hpp>
#include <Engine/VelocityComponent.h>
#include <Engine/Structure.hpp>
#include <Engine/SDLppRenderer.hpp>
#include <Engine/CameraComponent.hpp>

RenderSystem::RenderSystem()
{
}

void RenderSystem::Update(entt::registry& registry, SDLppRenderer& renderer)
{
	auto view = registry.view<Transform, Sprite>();
	for (entt::entity entity : view)
	{
		auto& entityTransform = view.get<Transform>(entity);
		auto& entitySprite = view.get<Sprite>(entity);

		entitySprite.Draw(renderer, entityTransform);
	}
}

void RenderSystem::Update(entt::registry& registry, SDLppRenderer& renderer, CameraComponent& camera)
{
	auto view = registry.view<Transform, Sprite>();
	for (entt::entity entity : view)
	{
		auto& entityTransform = view.get<Transform>(entity);
		auto& entitySprite = view.get<Sprite>(entity);

		camera.m_transform.GetGlobalPosition();
		entityTransform.GetGlobalPosition();
		 
		entitySprite.Draw(renderer, entityTransform);
	}
}