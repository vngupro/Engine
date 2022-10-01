#pragma once

#include"DLLDefine.hpp"
#include <SDL.h>
#include <string>

class ENGINE_API SDLppSurface
{
	public:
		SDLppSurface(const SDLppSurface&) = delete; // constructeur par copie
		SDLppSurface(SDLppSurface&& surface) noexcept; // constructeur par mouvement
		~SDLppSurface();

		SDL_Surface* GetHandle() const;

		SDLppSurface& operator=(const SDLppSurface&) = delete; // op�rateur d'assignation par copie
		SDLppSurface& operator=(SDLppSurface&&) noexcept; // op�rateur d'assignation par mouvement

		static SDLppSurface LoadFromFile(const std::string& filepath);

	private:
		SDLppSurface(SDL_Surface* surface);

		SDL_Surface* m_surface;
};