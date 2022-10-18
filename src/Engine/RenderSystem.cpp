#include <Engine/RenderSystem.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Transform.hpp>
#include <Engine/VelocityComponent.h>
#include <Engine/Structure.hpp>
#include <Engine/SDLppRenderer.hpp>
#include <Engine/CameraComponent.hpp>
#include <iostream>

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

		// compare to camera how sprite should move ???
		// frutrum calculation ?? (it's for 3D so no)
		// orthographic size ?? 
		// camH * 2 = viewport H
		// camW * 2 = viewport W
		// from point in local space camera
		// where is the Sprite ??
		// once you got pos of sprite depending of camera position
		// if camera move in an axe
		// sprite go inverse of that axe movement
		// should camera be 0, 0 ????
		// value are so weird
		//
		// std::cout << "Cam pos g : " << camera.m_transform.GetGlobalPosition() << std::endl;
		//std::cout << "Cam pos : " << camera.m_transform.GetPosition() << std::endl;
		//std::cout << "Entt pos : " << entityTransform.GetPosition() << std::endl;
		//std::cout << "Entt pos g : " << entityTransform.GetGlobalPosition() << std::endl;

		//std::cout << "entity compare to camera : " << entityTransform.TransformPoint(camera.m_transform.GetGlobalPosition()) << std::endl;
		
		float viewportW = camera.m_width;
		float viewportH = camera.m_height;
		float viewport_min_x = camera.m_transform.GetGlobalPosition().x - camera.m_width / 2;
		float viewport_max_x = camera.m_transform.GetGlobalPosition().x + camera.m_width / 2;
		float viewport_min_y = camera.m_transform.GetGlobalPosition().y - camera.m_height / 2;
		float viewport_max_y = camera.m_transform.GetGlobalPosition().y + camera.m_height / 2;

		//std::cout << "viewport W : " << viewportW << std::endl;
		//std::cout << "viewport H : " << viewportH << std::endl;
		//std::cout << "viewport_min_x : " << viewport_min_x << std::endl;
		//std::cout << "viewport_max_x : " << viewport_max_x << std::endl;
		//std::cout << "viewport_min_y : " << viewport_min_y << std::endl;
		//std::cout << "viewport_max_y : " << viewport_max_y << std::endl;

		//Vector2f pos(entityTransform.GetGlobalPosition().x - viewport_min_x, entityTransform.GetGlobalPosition().y -viewport_min_y);
		Transform transform = entityTransform; // you want a copy to not change the transform
		
		float rot = camera.m_transform.GetRotation();
		transform.SetRotation(entityTransform.GetRotation() - rot);

		Vector2f pos (
			entityTransform.GetPosition().x - viewport_min_x, 
			entityTransform.GetPosition().y -viewport_min_y);
		transform.SetPosition(pos);

		Vector2f sca(
			entityTransform.GetScale().x * 1 / camera.m_transform.GetScale().x, 
			entityTransform.GetScale().y * 1 / camera.m_transform.GetScale().y);
		transform.SetScale(sca);

		entitySprite.Draw(renderer, transform);
	}
}