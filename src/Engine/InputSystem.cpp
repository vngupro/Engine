#include "InputSystem.hpp"

void InputSystem::BindKeyPressed(SDL_Keycode key, std::string action)
{
	Get().BindKeyPressed_Impl(key, action);
}

void InputSystem::BindKeyPressed_Impl(SDL_Keycode key, std::string action)
{
	auto range = key_inputs.equal_range(key);
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second == action)
		{
			return;
		}
	}

	key_inputs.emplace(key, action);
}

void InputSystem::BindMouseButtonPressed(Uint8 mouse, std::string action)
{
	Get().BindMouseButtonPressed_Impl(mouse, action);
}

void InputSystem::BindMouseButtonPressed_Impl(Uint8 mouse, std::string action)
{
	auto range = mouse_inputs.equal_range(mouse);
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second == action)
		{
			return;
		}
	}

	mouse_inputs.emplace(mouse, action);
}

void InputSystem::OnAction(std::string action, ActionFunc actionFunc)
{
	Get().OnAction_Impl(action, actionFunc);
}

void InputSystem::OnAction_Impl(std::string action, ActionFunc actionFunc)
{
	auto range = action_map.equal_range(action);
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second == actionFunc)
		{
			return;
		}
	}

	action_map.emplace(action, actionFunc);
}

void InputSystem::BindAxis(Uint8 axis, std::string action)
{
	Get().BindAxis_Impl(axis, action);
}

void InputSystem::BindAxis_Impl(Uint8 axis, std::string action)
{
	auto range = axis_inputs.equal_range(axis);
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second == action)
		{
			return;
		}
	}

	axis_inputs.emplace(axis, action);
}

void InputSystem::BindGamepadButtonPressed(Uint8 button, std::string action)
{
	Get().BindGamepadButtonPressed_Impl(button, action);
}

void InputSystem::BindGamepadButtonPressed_Impl(Uint8 button, std::string action)
{
	auto range = button_inputs.equal_range(button);
	for (auto it = range.first; it != range.second; it++)
	{
		if (it->second == action)
		{
			return;
		}
	}

	button_inputs.emplace(button, action);
}
