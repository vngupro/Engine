#pragma once
#include "DLLDefine.hpp"
#include <SDL.h>
#include <string>
#include <map>
#include <iostream>
#include <SDL_gamecontroller.h>

typedef void(*ActionFunc)();
#define DEAD_ZONE 15000

class ENGINE_API InputSystem
{

public:
	std::multimap<SDL_Keycode, std::string> key_inputs;
	std::multimap<Uint8, std::string>  mouse_inputs;
	std::multimap<Uint8, std::string> button_inputs;
	std::multimap<Uint8, std::string> axis_inputs;
	std::multimap<std::string, ActionFunc> action_map;

	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;
	InputSystem(InputSystem&&) = delete;
	InputSystem& operator=(InputSystem&&) = delete;

	static InputSystem& Get()
	{
		static InputSystem instance;
		return instance;
	}

	static void BindKeyPressed(SDL_Keycode key, std::string action);
	static void BindMouseButtonPressed(Uint8 mouse, std::string action);
	static void BindGamepadButtonPressed(Uint8 button, std::string action);
	static void BindAxis(Uint8 axis, std::string action);
	static void OnAction(std::string action, ActionFunc actionFunc);

private:
	InputSystem() {};
	void BindKeyPressed_Impl(SDL_Keycode key, std::string action);
	void BindMouseButtonPressed_Impl(Uint8 mouse, std::string action);
	void BindGamepadButtonPressed_Impl(Uint8 button, std::string action);
	void BindAxis_Impl(Uint8 axis, std::string action);
	void OnAction_Impl(std::string action, ActionFunc actionFunc);
};

// Dangerous will change it when I'm not lazy anymore
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::multimap<T, std::string> m)
{
	for (auto it = m.begin(); it != m.end(); it++)
	{
		stream << it->first << "\t" << it->second << std::endl;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::multimap<std::string, ActionFunc> m)
{
	for (auto it = m.begin(); it != m.end(); it++)
	{
		stream << it->first << "\t";
		it->second();
	}
	return stream;
}

//std::ostream& operator<<(std::ostream& stream, const std::multimap<SDL_Keycode, std::string> m)
//{
//	for (auto it = m.begin(); it != m.end(); it++)
//	{
//		stream << it->first << "\t" << it->second << std::endl;
//	}
//	return stream;
//}
//
//std::ostream& operator<<(std::ostream& stream, const std::multimap<Uint8, std::string> m)
//{
//	for (auto it = m.begin(); it != m.end(); it++)
//	{
//		stream << it->first << "\t" << it->second << std::endl;
//	}
//	return stream;
//}
//
//std::ostream& operator<<(std::ostream& stream, const std::multimap<SDL_GameControllerButton, std::string> m)
//{
//	for (auto it = m.begin(); it != m.end(); it++)
//	{
//		stream << it->first << "\t" << it->second << std::endl;
//	}
//	return stream;
//}
//
//std::ostream& operator<<(std::ostream& stream, const std::multimap<SDL_GameControllerAxis, std::string> m)
//{
//	for (auto it = m.begin(); it != m.end(); it++)
//	{
//		stream << it->first << "\t" << it->second << std::endl;
//	}
//	return stream;
//}