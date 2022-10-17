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
	//auto view = registry.view<Position, Drawable>();
	//for (entt::entity entity : view)
	//{
	//	auto& entityPos = view.get<Position>(entity);
	//	auto& entityDrawable = view.get<Drawable>(entity);

	//	SDL_Rect rect;
	//	rect.x = static_cast<int>(entityPos.x);
	//	rect.y = static_cast<int>(entityPos.y);
	//	rect.w = entityDrawable.width;
	//	rect.h = entityDrawable.height;

	//	renderer.RenderCopy(*entityDrawable.texture, rect);
	//}

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

		camera.m_transform.GetPosition();
		entitySprite.Draw(renderer, entityTransform);
	}
}