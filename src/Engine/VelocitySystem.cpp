#include <Engine/VelocityComponent.h>
#include <Engine/VelocitySystem.hpp>
#include <Engine/Transform.hpp>
#include <iostream>

VelocitySystem::VelocitySystem()
{
}

void VelocitySystem::Update(entt::registry& registry)
{
    auto view = registry.view<Transform, Velocity>();
    for (entt::entity entity : view)
    {
        auto& transform = view.get<Transform>(entity);
        auto& velocity = view.get<Velocity>(entity);

        transform.Translate(Vector2f(velocity.x, velocity.y));
    }

    // For Debug purpose
    //auto transformView = registry.view<Transform, Name>();
    //for (entt::entity entity : transformView)
    //{
    //    auto& transform = transformView.get<Transform>(entity);
    //    auto& name = transformView.get<Name>(entity);

    //    std::cout << "Entity " << name.name << " position : (" << transform.GetPosition() << std::endl;
    //}
}
