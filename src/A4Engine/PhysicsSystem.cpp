#include <A4Engine/PhysicsSystem.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <entt/entt.hpp>

PhysicsSystem::PhysicsSystem(entt::registry& registry) :
m_registry(registry),
m_accumulator(0.f),
m_timestep(1.f / 50.f)
{
	// Par mesure de simplicit�, on utilise un Singleton ici
	// n�anmoins, en pratique les singletons sont un peu le "goto de l'architecture".
	// Il serait mieux de permettre d'avoir plusieurs Space
	if (s_instance != nullptr)
		throw std::runtime_error("only one PhysicsSystem can be created");

	s_instance = this;

	// Par default
	SetGravity({ 0.f, 981.f });
	SetDamping(0.9f);
}

PhysicsSystem::~PhysicsSystem()
{
	// Le PhysicsSystem est d�truit avant le registry (qui lui-m�me d�truit les composants RigidBodyComponent, ceux-ci d�truisant les cpBody/cpShape)
	// cela pose probl�me, pour y rem�dier on va forcer la destruction des composants en les enlevant
	m_registry.clear<RigidBodyComponent>();

	s_instance = nullptr;
}

ChipmunkSpace& PhysicsSystem::GetSpace()
{
	// L'h�ritage priv� interdit � tout autre classe que nous de r�cup�rer une r�f�rence sur le parent � partir de nous
	// mais nous pouvons faire une fonction pour l'autoriser
	return *this;
}

void PhysicsSystem::Update(float deltaTime)
{
	m_accumulator += deltaTime;
	while (m_accumulator >= m_timestep)
	{
		Step(m_timestep);
		m_accumulator -= m_timestep;
	}

	auto view = m_registry.view<Transform, RigidBodyComponent>();
	for (entt::entity entity : view)
	{
		Transform& entityTransform = view.get<Transform>(entity);
		RigidBodyComponent& entityBody = view.get<RigidBodyComponent>(entity);

		entityTransform.SetPosition(entityBody.GetPosition());
		entityTransform.SetRotation(entityBody.GetRotation());
	}
}

PhysicsSystem* PhysicsSystem::Instance()
{
	return s_instance;
}

PhysicsSystem* PhysicsSystem::s_instance = nullptr;