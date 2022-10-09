#pragma once

#include <Engine/Export.hpp>

union SDL_Event;

class ENGINE_API SDLpp
{
	public:
		SDLpp();
		SDLpp(const SDLpp&) = delete;
		SDLpp(SDLpp&&) = delete;
		~SDLpp();

		SDLpp& operator=(const SDLpp&) = delete;
		SDLpp& operator=(SDLpp&&) = delete;

		static bool PollEvent(SDL_Event* event);
};
