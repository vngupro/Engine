#include "SDLpp.hpp"
#include <SDL.h>

SDLpp::SDLpp()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
}

SDLpp::~SDLpp()
{
	SDL_Quit();
}

bool SDLpp::PollEvent(SDL_Event* event)
{
	return SDL_PollEvent(event);
}
