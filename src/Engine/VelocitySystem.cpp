#include <Engine/VelocityComponent.h>
#include <Engine/VelocitySystem.hpp>
#include <Engine/Transform.hpp>
#include <iostream>

VelocitySystem::VelocitySystem()
{
}

void VelocitySystem::Update(entt::registry& registry)
{
    // Une vue est une façon de récupérer uniquement les entités possédant certains composants
// Nous n'allons donc récupérer que les entités possédant à la fois une Position et une Velocity
    //auto posVelView = registry.view<Position, Velocity>();

    //// On peut itérer dessus comme un tableau
    //for (entt::entity entity : posVelView)
    //{
    //    // On peut ensuite récupérer une référence sur les composants depuis la vue
    //    auto& pos = posVelView.get<Position>(entity);
    //    auto& vel = posVelView.get<Velocity>(entity);

    //    // et les modifier comme bon nous semble
    //    pos.x += vel.x;
    //    pos.y += vel.y;
    //}

    //// On fait de même pour l'association Position/std::string (que toutes nos entités possèdent ici)
    //auto posView = registry.view<Position, std::string>();
    //for (entt::entity entity : posView)
    //{
    //    auto& pos = posView.get<Position>(entity);
    //    auto& name = posView.get<std::string>(entity);

    //    // On affiche le nom de l'entité et sa position actuelle
    //    std::cout << "Entity " << name << " position: (" << pos.x << ", " << pos.y << ")\n";
    //}

    //std::cout << "---" << std::endl;

    auto view = registry.view<Transform, Velocity>();
    for (entt::entity entity : view)
    {
        auto& transform = view.get<Transform>(entity);
        auto& velocity = view.get<Velocity>(entity);

        transform.Translate(Vector2f(velocity.x, velocity.y));
    }

    auto transformView = registry.view<Transform, Name>();
    for (entt::entity entity : transformView)
    {
        auto& transform = transformView.get<Transform>(entity);
        auto& name = transformView.get<Name>(entity);

        std::cout << "Entity " << name.name << " position : (" << transform.GetPosition() << std::endl;
    }
}
