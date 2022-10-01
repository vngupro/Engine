#pragma once
#include "DLLDefine.hpp"
#include <SDL.h>
#include <string>

class ENGINE_API InputSystem
{
public:
	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;
	InputSystem(InputSystem&&) = delete;
	InputSystem& operator=(InputSystem&&) = delete;

	static InputSystem& Get()
	{
		static InputSystem instance;
		return instance;
	}

	static void BindKeyPressed(const SDL_KeyCode& key, const std::string& action);
	static void BindMouseButtonPressed(const Uint8& mouse, const std::string& action);
	static void OnAction(const std::string action, void (*func)());

private:
	InputSystem() {};
	static void BindKeyPressed_Impl(const SDL_KeyCode& key, const std::string& action);
	static void BindMouseButtonPressed_Impl(const Uint8& mouse, const std::string& action);
	static void OnAction_Impl(const std::string action, void (func)());
};