#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/ChipmunkBody.hpp>
#include <A4Engine/ChipmunkShape.hpp>
#include <memory>
#include <unordered_map>

class ChipmunkShape;
struct CollisionShape;

class A4ENGINE_API RigidBodyComponent
{
	public:
		// Petite astuce, on peut se servir de structures vides comme de "tags", une fa�on de diff�rencier les constructeurs
		struct Kinematic {};
		struct Static {};

		RigidBodyComponent(float mass, float moment = 1.f);
		RigidBodyComponent(Kinematic /*unnamed*/);
		RigidBodyComponent(Static);

		void AddShape(std::shared_ptr<CollisionShape> shape, const Vector2f& offset = Vector2f(0.f, 0.f), bool recomputeMoment = true);

		float GetAngularVelocity() const;
		Vector2f GetCenterOfGravity() const;
		Vector2f GetLinearVelocity() const;
		Vector2f GetPosition() const;
		float GetRotation() const;

		void RemoveShape(const std::shared_ptr<CollisionShape>& shape, bool recomputeMoment = true);

		void SetAngularVelocity(float angularVelocity);
		void SetCenterOfGravity(const Vector2f& centerOfGravity);
		void SetLinearVelocity(const Vector2f& linearVelocity);
		void SetMass(float mass, bool recomputeMoment = true);

		void TeleportTo(const Vector2f& position);
		void TeleportTo(const Vector2f& position, float rotation);

	private:
		void RecomputeMoment();
		
		struct ShapeData
		{
			ChipmunkShape physicsShape;
			Vector2f offset;
		};

		// L'ordre des membres est important : ils sont construits dans l'ordre de d�claration
		// et d�truits dans l'ordre inverse
		// ainsi ici, les shapes seront d�truits avant que le body ne le soit (l'inverse poserait probl�me !)
		ChipmunkBody m_body;
		std::unordered_map<std::shared_ptr<CollisionShape>, ShapeData> m_shapes;
};
