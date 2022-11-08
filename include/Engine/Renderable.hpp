#pragma once

#include <Engine/Export.hpp>

class SDLppRenderer;
class SDLppTexture;
class Transform;

class ENGINE_API Renderable // interface
{
	public:
		// Il est important pour une classe virtuelle de base d'avoir un destructeur virtuel
		virtual ~Renderable() = default;

		virtual void Draw(SDLppRenderer& renderer, const Transform& cameraTransform, const Transform& transform) = 0;
};
