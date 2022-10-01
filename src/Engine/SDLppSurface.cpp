#include "SDLppSurface.hpp"
#include <SDL_image.h>
#include <iostream>

SDLppSurface::SDLppSurface(SDLppSurface&& surface) noexcept
{
	m_surface = surface.m_surface;
	surface.m_surface = nullptr;
}

SDLppSurface::~SDLppSurface()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

SDL_Surface* SDLppSurface::GetHandle() const
{
	return m_surface;
}

SDLppSurface& SDLppSurface::operator=(SDLppSurface&& Surface) noexcept
{
	// On possède déjà potentiellement une Surface
	// On la donne à Surface (qui va être détruit de toute façon)
	// tout en volant son pointeur : on échange donc les pointeurs
	// => std::swap
	std::swap(m_surface, Surface.m_surface);
	return *this;
}

SDLppSurface SDLppSurface::LoadFromFile(const std::string& filepath)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (!surface)
		std::cerr << IMG_GetError() << std::endl;

	return SDLppSurface(surface);
}

SDLppSurface::SDLppSurface(SDL_Surface* surface) :
m_surface(surface)
{
}
