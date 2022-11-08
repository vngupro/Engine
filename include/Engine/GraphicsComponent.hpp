#pragma once

#include <Engine/Export.hpp>
#include <memory>

class Renderable;

struct ENGINE_API GraphicsComponent
{
	std::shared_ptr<Renderable> renderable;
};
