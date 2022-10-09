#pragma once

#include <Engine/Export.hpp>
#include <memory>
#include <SDL.h>

class SDLppRenderer;
class SDLppTexture;
class Transform;

class ENGINE_API Sprite // Une portion d'une texture
{
	public:
		Sprite(std::shared_ptr<const SDLppTexture> texture);
		Sprite(std::shared_ptr<const SDLppTexture> texture, const SDL_Rect& rect);
		Sprite(const Sprite&) = default;
		Sprite(Sprite&&) = default;
		~Sprite() = default;

		void Draw(SDLppRenderer& renderer, const Transform& transform);

		int GetHeight() const;
		int GetWidth() const;

		void Resize(int width, int height);

		void SetRect(SDL_Rect rect);

		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&&) = default;

	private:
		std::shared_ptr<const SDLppTexture> m_texture;
		SDL_Rect m_rect;
		int m_width;
		int m_height;
};