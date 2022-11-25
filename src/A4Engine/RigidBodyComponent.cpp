#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/ChipmunkShape.hpp>
#include <A4Engine/CollisionShape.hpp>
#include <A4Engine/PhysicsSystem.hpp>

RigidBodyComponent::RigidBodyComponent(float mass, float moment) :
m_body(ChipmunkBody::Build(PhysicsSystem::Instance()->GetSpace(), mass, moment))
{
}

RigidBodyComponent::RigidBodyComponent(Kinematic) :
m_body(ChipmunkBody::BuildKinematic(PhysicsSystem::Instance()->GetSpace()))
{
}

RigidBodyComponent::RigidBodyComponent(Static) :
m_body(ChipmunkBody::BuildStatic(PhysicsSystem::Instance()->GetSpace()))
{
}

void RigidBodyComponent::AddShape(std::shared_ptr<CollisionShape> shape, const Vector2f& offset, bool recomputeMoment)
{
	ShapeData shapeData{
		shape->Build(m_body, offset),
		offset
	};

	auto [it, inserted] = m_shapes.emplace(std::move(shape), std::move(shapeData));

	// Si la shape a bien �t� ajout�e
	if (inserted && recomputeMoment)
		RecomputeMoment();
}

float RigidBodyComponent::GetAngularVelocity() const
{
	return m_body.GetAngularVelocity();
}

Vector2f RigidBodyComponent::GetCenterOfGravity() const
{
	return m_body.GetCenterOfGravity();
}

Vector2f RigidBodyComponent::GetLinearVelocity() const
{
	return m_body.GetLinearVelocity();
}

Vector2f RigidBodyComponent::GetPosition() const
{
	return m_body.GetPosition();
}

float RigidBodyComponent::GetRotation() const
{
	return m_body.GetRotation();
}

void RigidBodyComponent::RemoveShape(const std::shared_ptr<CollisionShape>& shape, bool recomputeMoment)
{
	std::size_t count = m_shapes.erase(shape);
	if (count > 0 && recomputeMoment) // si on a bien enlev� un shape
		RecomputeMoment();
}

void RigidBodyComponent::SetAngularVelocity(float angularVelocity)
{
	m_body.SetAngularVelocity(angularVelocity);
}

void RigidBodyComponent::SetCenterOfGravity(const Vector2f& centerOfGravity)
{
	m_body.SetCenterOfGravity(centerOfGravity);
}

void RigidBodyComponent::SetLinearVelocity(const Vector2f& linearVelocity)
{
	m_body.SetLinearVelocity(linearVelocity);
}

void RigidBodyComponent::SetMass(float mass, bool recomputeMoment)
{
	m_body.SetMass(mass);
	if (recomputeMoment)
		RecomputeMoment();
}

void RigidBodyComponent::TeleportTo(const Vector2f& position)
{
	m_body.SetPosition(position);

	// Les objets statiques doivent �tre r�index�s manuellement en cas de d�placement
	if (m_body.IsStatic())
		m_body.ReindexShapes();
}

void RigidBodyComponent::TeleportTo(const Vector2f& position, float rotation)
{
	m_body.SetPosition(position);
	m_body.SetRotation(rotation);
}

void RigidBodyComponent::RecomputeMoment()
{
	if (!m_body.IsDynamic())
		return; // on ne touche pas aux objets kin�matiques ou statiques

	float mass = m_body.GetMass();

	// Le moment angulaire final est la somme de tous les moments angulaires
	float moment = 0.f;
	for (auto&& [shape, shapeData] : m_shapes)
		moment += shape->ComputeMoment(mass, shapeData.offset);
	
	m_body.SetMoment(moment);
}
