#pragma once

#include <Engine/Export.hpp>
#include <entt/fwd.hpp> //< header sp�cial qui fait des d�clarations anticip�es des classes de la lib

class SDLppRenderer;

class ENGINE_API RenderSystem
{
	public:
		RenderSystem(SDLppRenderer& renderer, entt::registry& registry);

		void Update(float deltaTime);

	private:
		SDLppRenderer& m_renderer;
		entt::registry& m_registry;
};