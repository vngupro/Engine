#include "InputSystem.hpp"

void InputSystem::BindKeyPressed(const SDL_KeyCode& key, const std::string& action)
{
	return Get().BindKeyPressed_Impl(key, action);
}

void InputSystem::BindKeyPressed_Impl(const SDL_KeyCode& key, const std::string& action)
{

}

void InputSystem::BindMouseButtonPressed(const Uint8& mouse, const std::string& action)
{
	return Get().BindMouseButtonPressed_Impl(mouse, action);
}

void InputSystem::BindMouseButtonPressed_Impl(const Uint8& mouse, const std::string& action)
{

}
