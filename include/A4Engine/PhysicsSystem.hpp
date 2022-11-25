#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/ChipmunkSpace.hpp>
#include <entt/fwd.hpp>

class A4ENGINE_API PhysicsSystem : ChipmunkSpace //< h�ritage priv�, les m�thodes ne sont pas accessibles publiquement
{
	public:
		PhysicsSystem(entt::registry& registry);
		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem(PhysicsSystem&&) = default;
		~PhysicsSystem();

		ChipmunkSpace& GetSpace();

		// Cette syntaxe permet d'exposer publiquement des m�thodes cach�es du parent
		using ChipmunkSpace::DebugDraw;
		using ChipmunkSpace::SetDamping;
		using ChipmunkSpace::SetGravity;

		void Update(float deltaTime);

		PhysicsSystem& operator=(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(PhysicsSystem&&) = delete;

		static PhysicsSystem* Instance();

	private:
		entt::registry& m_registry;
		float m_accumulator;
		float m_timestep;

		static PhysicsSystem* s_instance;
};