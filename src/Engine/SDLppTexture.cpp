#include "SDLppTexture.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppSurface.hpp"
#include <SDL_image.h>

SDLppTexture::SDLppTexture(SDLppTexture&& texture) noexcept
{
	m_texture = texture.m_texture;
	texture.m_texture = nullptr;
}

SDLppTexture::~SDLppTexture()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

SDL_Texture* SDLppTexture::GetHandle() const
{
	return m_texture;
}

SDL_Rect SDLppTexture::GetRect() const
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &rect.w, &rect.h);

	return rect;
}

SDLppTexture& SDLppTexture::operator=(SDLppTexture&& texture) noexcept
{
	// On poss�de d�j� potentiellement une texture
	// On la donne � texture (qui va �tre d�truit de toute fa�on)
	// tout en volant son pointeur : on �change donc les pointeurs
	// => std::swap
	std::swap(m_texture, texture.m_texture);
	return *this;
}

SDLppTexture SDLppTexture::LoadFromFile(SDLppRenderer& renderer, const std::string& filepath)
{
	return LoadFromSurface(renderer, SDLppSurface::LoadFromFile(filepath));
}

SDLppTexture SDLppTexture::LoadFromSurface(SDLppRenderer& renderer, const SDLppSurface& surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.GetHandle(), surface.GetHandle());
	return SDLppTexture(texture);
}

SDLppTexture::SDLppTexture(SDL_Texture* texture) :
m_texture(texture)
{
}
