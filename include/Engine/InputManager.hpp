#pragma once

#include <Engine/Export.hpp>
#include <SDL.h>
#include <functional> //< std::function
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association cl�/valeur

enum class MouseButton
{
	Left,
	Right,
	Middle,
	X1,
	X2
};

class ENGINE_API InputManager
{
	public:
		InputManager();
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		~InputManager();

		// Appuyer sur la touche "keyCode" d�clenchera "action"
		void BindKeyPressed(SDL_KeyCode keyCode, std::string action);

		// Appuyer sur le bouton "button" d�clenchera "action"
		void BindMouseButtonPressed(MouseButton button, std::string action);

		// Appuyer sur le bouton "button" du contr�leur (manette) d�clenchera "action"
		void BindControllerButton(SDL_GameControllerButton button, std::string action);

		// R�initialise toutes les associations clavier/souris vers des actions
		void ClearBindings();

		// G�re l'�v�nement de la SDL et d�clenche les actions associ�es, s'il y en a
		void HandleEvent(const SDL_Event& event);

		// Renvoie vrai si l'action est en cours
		bool IsActive(const std::string& action) const;

		// Lorsque l'action "action" se d�clenche, on appellera "func"
		void OnAction(std::string action, std::function<void(bool)> func);

		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		static InputManager& Instance();

	private:
		struct ActionData
		{
			std::function<void(bool)> func;
			bool isActive;
		};

		ActionData& GetActionData(const std::string& action);
		void TriggerAction(const std::string& action);
		void ReleaseAction(const std::string& action);

		std::unordered_map<int /*mouseButton*/, std::string /*action*/> m_mouseButtonToAction;
		std::unordered_map<SDL_GameControllerButton /*controllerButton*/, std::string /*action*/> m_controllerButtonToAction;
		std::unordered_map<SDL_Keycode /*key*/, std::string /*action*/> m_keyToAction;
		std::unordered_map<std::string /*action*/, ActionData> m_actions;

		static InputManager* s_instance;
};