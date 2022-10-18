#include <iostream>
#include <SDL.h>
#include <Engine/InputManager.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/SDLpp.hpp>
#include <Engine/SDLppWindow.hpp>
#include <Engine/SDLppRenderer.hpp>
#include <Engine/SDLppTexture.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Transform.hpp>
#include <Engine/Model.hpp>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <entt/entt.hpp>
#include <Engine/VelocityComponent.h>
#include <Engine/VelocitySystem.hpp>
#include <Engine/RenderSystem.hpp>
#include <Engine/CameraComponent.hpp>
#include <Engine/Structure.hpp>

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    ResourceManager resourceManager(renderer);
    InputManager inputManager;
    
    // HOUSE 
    std::shared_ptr<SDLppTexture> houseTex = ResourceManager::Instance().GetTexture("assets/house1772x1920.png");
    SDL_Rect houseTexRect = houseTex.get()->GetRect();

    Transform houseTransform;
    houseTransform.SetPosition(Vector2f(150.f, 150.f));
    
    // for debug purpose only
    //Sprite houseSprite(houseTex);
    //houseSprite.Resize(houseTexRect.w / 10.f, houseTexRect.h / 10.f);
    float houseW = houseTexRect.w / 10.f;
    float houseH = houseTexRect.h / 10.f;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    Vector2f topLeftCorner = houseTransform.TransformPoint(Vector2f(0.f, 0.f));
    Vector2f topRightCorner = houseTransform.TransformPoint(Vector2f(houseW, 0.f));
    Vector2f bottomLeftCorner = houseTransform.TransformPoint(Vector2f(0.f, houseH));
    Vector2f bottomRightCorner = houseTransform.TransformPoint(Vector2f(houseW, houseH));

    float offsetX = 0.18f;
    float offsetY = 0.15f;
    // the position of the vertices are going to be the width and height of the model

    /*
    *               0
    *              / \
    *             /   \
    *            1_____2
    *            |\    |
    *            |  \  |
    *            3____\4
    */
    SDL_Vertex vertex0
    {
        SDL_FPoint{ topLeftCorner.x + houseW / 2.f, topLeftCorner.y },
        SDL_Color { 255, 255, 255, 255 },
        SDL_FPoint{ 0.5f, 0.f }
        //SDL_FPoint{ m_rect.x * invWidth, m_rect.y * invHeight } // I don't understand the formula
    };
    vertices.emplace_back(vertex0);

    SDL_Vertex vertex1
    {
        SDL_FPoint{ topLeftCorner.x, topLeftCorner.y + houseH / 2.f },
        SDL_Color{ 255, 255, 255, 255 },
        SDL_FPoint{ 0.f + offsetX, 0.5f }
    };
    //vertices[1].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, m_rect.y * invHeight };
    vertices.emplace_back(vertex1);

    SDL_Vertex vertex2
    {
        SDL_FPoint{ topRightCorner.x, topRightCorner.y + houseH / 2.f },
        SDL_Color{ 255, 255, 255, 255 },
        SDL_FPoint{ 1.f - offsetX, 0.5f }
    };
    vertices.emplace_back(vertex2);

    SDL_Vertex vertex3
    {
        SDL_FPoint{ bottomLeftCorner.x, bottomLeftCorner.y },
        SDL_Color{ 255, 255, 255, 255 },
        SDL_FPoint{ 0.f + offsetX, 1.0f - offsetY }
    };
    vertices.emplace_back(vertex3);

    SDL_Vertex vertex4
    {
        SDL_FPoint{ bottomRightCorner.x, bottomRightCorner.y },
        SDL_Color{ 255, 255, 255, 255 },
        SDL_FPoint{ 1.f - offsetX, 1.f - offsetY}
    };
    vertices.emplace_back(vertex4);

    //vertices[2].tex_coord = SDL_FPoint{ m_rect.x * invWidth, (m_rect.y + m_rect.h) * invHeight };
    //vertices[3].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, (m_rect.y + m_rect.h) * invHeight };

    indices = { 0, 1, 2, 1, 3, 4, 1, 4, 2 };
    
    Model house("house", vertices, indices, houseTex);
    //house.ExportToJson();
    house.ExportToCbor();
    house.ExportToBinary();
    Model house2 = Model::LoadModelFromJson("assets/house.model");
    //Model house3 = Model::LoadModelFromCbor("assets/house.cmodel");
    //Model house4 = Model::LoadModelFromBinary("assets/house.bmodel");
    
    // ENTT
    // Sprite runner = player
    std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture("assets/runner.png");

    Sprite sprite(texture);
    sprite.Resize(256, 256);
    sprite.SetRect(SDL_Rect{ 0, 0, 32, 32 });

    Transform transform;
    transform.SetPosition(Vector2f(150.f, 150.f));
    
    Transform transformParent;
    transformParent.SetPosition(Vector2f(300.f, 100.f));
    
    transform.SetParent(&transformParent);

    entt::registry registry;

    entt::entity player = registry.create();
    {
        auto& entityName = registry.emplace<Name>(player, "Player");
        auto& entityTransform = registry.emplace<Transform>(player, transform);
        auto& entitySprite = registry.emplace<Sprite>(player, sprite);
    }
    
    entt::entity parent = registry.create();
    {
        auto& entityName = registry.emplace<Name>(parent, "Parent");
        auto& entityTransform = registry.emplace<Transform>(parent, transformParent);
        auto& entitySprite = registry.emplace<Sprite>(parent, sprite);
        auto& entityVelocity = registry.emplace<Velocity>(parent, 0.f, 0.1f);
    }

    RenderSystem renderSystem;
    VelocitySystem velocitySystem;

    Vector2f camOffset(500.0f, 10.0f);
    Transform camTransform;
    camTransform.SetPosition(Vector2f(1280.f / 2 + camOffset.x, 720.f / 2 + camOffset.y));
    //camTransform.SetPosition(Vector2f(0.f, 0.f));
    CameraComponent camera(camTransform, 1280, 720);
    //return 0;
    renderSystem.Update(registry, renderer, camera);
    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
    ImGui_ImplSDLRenderer_Init(renderer.GetHandle());

    InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");

    //std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture("assets/runner.png");

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    int frameIndex = 0;
    int frameCount = 5;
    float timer = 0.0f;

    float scale = 1.f;

    bool isOpen = true;

    float rotation = 10.f;

    while (isOpen)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = (float) (now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

        timer += deltaTime;
        if (timer > 0.1f)
        {
            timer -= 0.1f;
            frameIndex++;
            if (frameIndex >= frameCount)
                frameIndex = 0;  

            sprite.SetRect({ frameIndex * 32, 0, 32, 32 });

            //std::cout << frameIndex << std::endl;
        }

        SDL_Event event;
        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;

            ImGui_ImplSDL2_ProcessEvent(&event);

            InputManager::Instance().HandleEvent(event);
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();


        ImGui::Begin("Window");

        if (ImGui::InputFloat("Rotation", &rotation, 0.1f, 0.5f))
        {
            transformParent.SetRotation(rotation);
        }

        ImGui::End();

        if (InputManager::Instance().IsActive("MoveRight"))
        {
            scale += 0.1f * deltaTime;
            transformParent.SetScale(Vector2f(scale, scale));
			//transformParent.Translate(Vector2f(500.f * deltaTime, 0.f));
            //transformParent.Rotate(30.f * deltaTime);
        }

        //houseSprite.Draw(renderer, houseTransform);
        //sprite.Draw(renderer, transformParent);
        //sprite.Draw(renderer, transform);
        house2.Draw(renderer, transform);

        //renderSystem.Update(registry, renderer);
        renderSystem.Update(registry, renderer, camera);
        //velocitySystem.Update(registry);

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        renderer.Present();
	}

    
	// Cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

    return 0;
}
