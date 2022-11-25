#include <A4Engine/ChipmunkShape.hpp>
#include <A4Engine/ChipmunkBody.hpp>
#include <A4Engine/Transform.hpp>
#include <chipmunk/chipmunk.h>
#include <algorithm>

ChipmunkShape::ChipmunkShape(ChipmunkBody& body, cpShape* shape) :
m_handle(shape)
{
	if (cpSpace* space = cpBodyGetSpace(body.GetHandle()))
		cpSpaceAddShape(space, m_handle);
}

ChipmunkShape::ChipmunkShape(ChipmunkShape&& shape) noexcept
{
	m_handle = shape.m_handle;
	shape.m_handle = nullptr;
}

ChipmunkShape::~ChipmunkShape()
{
	if (m_handle)
	{
		// On d�senregistre le shape du space automatiquement avant de le d�truire
		if (cpSpace* space = cpShapeGetSpace(m_handle))
			cpSpaceRemoveShape(space, m_handle);

		cpShapeFree(m_handle);
	}
}

void ChipmunkShape::SetFriction(float friction)
{
	cpShapeSetFriction(m_handle, friction);
}

ChipmunkShape& ChipmunkShape::operator=(ChipmunkShape&& space) noexcept
{
	// On poss�de d�j� potentiellement une Surface
	// On la donne � Surface (qui va �tre d�truit de toute fa�on)
	// tout en volant son pointeur : on �change donc les pointeurs
	// => std::swap
	std::swap(m_handle, space.m_handle);
	return *this;
}

ChipmunkShape ChipmunkShape::BuildBox(ChipmunkBody& body, float width, float height, float radius)
{
	return ChipmunkShape(body, cpBoxShapeNew(body.GetHandle(), width, height, radius));
}

ChipmunkShape ChipmunkShape::BuildBox(ChipmunkBody& body, float left, float bottom, float right, float top, float radius)
{
	return ChipmunkShape(body, cpBoxShapeNew2(body.GetHandle(), cpBB{ left, top, right, bottom }, radius));
}

ChipmunkShape ChipmunkShape::BuildBox(ChipmunkBody& body, const Vector2f& topLeftCorner, const Vector2f& bottomRightCorner, float radius)
{
	float left = topLeftCorner.x;
	float bottom = bottomRightCorner.y;
	float right = bottomRightCorner.x;
	float top = topLeftCorner.y;

	return BuildBox(body, left, bottom, right, top, radius);
}

ChipmunkShape ChipmunkShape::BuildCircle(ChipmunkBody& body, float radius, const Vector2f& offset)
{
	return ChipmunkShape(body, cpCircleShapeNew(body.GetHandle(), radius, cpv(offset.x, offset.y)));
}

ChipmunkShape ChipmunkShape::BuildConvexHull(ChipmunkBody& body, const std::vector<Vector2f>& positions, const Matrix3f& transform, float radius)
{
	std::vector<cpVect> verts;
	verts.reserve(positions.size());
	for (std::size_t i = 0; i < positions.size(); ++i)
	{
		Vector2 pos = transform * positions[i];
		verts.push_back(cpv(pos.x, pos.y));
	}

	return ChipmunkShape(body, cpPolyShapeNew(body.GetHandle(), static_cast<int>(verts.size()), verts.data(), cpTransformIdentity, radius));
}

ChipmunkShape ChipmunkShape::BuildSegment(ChipmunkBody& body, const Vector2f& from, const Vector2f& to, float radius)
{
	return ChipmunkShape(body, cpSegmentShapeNew(body.GetHandle(), cpv(from.x, from.y), cpv(to.x, to.y), radius));
}

float ChipmunkShape::ComputeBoxMoment(float mass, float width, float height)
{
	return static_cast<float>(cpMomentForBox(mass, width, height));
}

float ChipmunkShape::ComputeBoxMoment(float mass, float left, float bottom, float right, float top)
{
	return static_cast<float>(cpMomentForBox2(mass, cpBB{ left, top, right, bottom }));
}

float ChipmunkShape::ComputeBoxMoment(float mass, const Vector2f& topLeftCorner, const Vector2f& bottomRightCorner)
{
	float left = topLeftCorner.x;
	float bottom = bottomRightCorner.y;
	float right = bottomRightCorner.x;
	float top = topLeftCorner.y;

	return static_cast<float>(ComputeBoxMoment(mass, left, bottom, right, top));
}

float ChipmunkShape::ComputeCircleMoment(float mass, float radius, const Vector2f& offset)
{
	return static_cast<float>(cpMomentForCircle(mass, 0.f, radius, cpv(offset.x, offset.y)));
}

float ChipmunkShape::ComputePolyMoment(float mass, const std::vector<Vector2f>& positions, const Matrix3f& transform, float radius)
{
	std::vector<cpVect> verts;
	verts.reserve(positions.size());
	for (std::size_t i = 0; i < positions.size(); ++i)
	{
		Vector2 pos = transform * positions[i];
		verts.push_back(cpv(pos.x, pos.y));
	}

	return static_cast<float>(cpMomentForPoly(mass, static_cast<int>(verts.size()), verts.data(), cpvzero, radius));
}

float ChipmunkShape::ComputeSegmentMoment(float mass, const Vector2f& from, const Vector2f& to, float radius)
{
	return static_cast<float>(cpMomentForSegment(mass, cpv(from.x, from.y), cpv(to.x, to.y), radius));
}
