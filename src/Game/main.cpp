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

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    ResourceManager resourceManager(renderer);
    InputManager inputManager;

    std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture("assets/runner.png");
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    SDL_Rect texRect = texture.get()->GetRect();

    //Vector2f topLeftCorner = transform.TransformPoint(Vector2f(0.f, 0.f));
    //Vector2f topRightCorner = transform.TransformPoint(Vector2f(m_width, 0.f));
    //Vector2f bottomLeftCorner = transform.TransformPoint(Vector2f(0.f, m_height));
    //Vector2f bottomRightCorner = transform.TransformPoint(Vector2f(m_width, m_height));
    Transform transformParent;
    Transform transform;
    transform.SetParent(&transformParent);

    transformParent.SetPosition(Vector2f(300.f, 100.f));
    transform.SetPosition(Vector2f(150.f, 150.f));

    Vector2f topLeftCorner = transform.TransformPoint(Vector2f(0.f, 0.f));
    Vector2f topRightCorner = transform.TransformPoint(Vector2f(200.f, 0.f));
    Vector2f bottomLeftCorner = transform.TransformPoint(Vector2f(0.f, 200.f));
    Vector2f bottomRightCorner = transform.TransformPoint(Vector2f(200.f, 200.f));

    //float invWidth = 1.f / texRect.w;
    //float invHeight = 1.f / texRect.h;

    //SDL_Vertex vertices[4];
    SDL_Vertex vertex
    {
        SDL_FPoint{ topLeftCorner.x, topLeftCorner.y },
        SDL_Color{ 255, 255, 255, 255 },
        //SDL_FPoint{ m_rect.x * invWidth, m_rect.y * invHeight };

    };
    vertices.push_back(vertex);

    SDL_Vertex vertex2
    {
        SDL_FPoint{ topRightCorner.x, topRightCorner.y },
        SDL_Color{ 255, 255, 255, 255 }
    };
    //vertices[1].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, m_rect.y * invHeight };
    vertices.push_back(vertex2);


    SDL_Vertex vertex3
    {
        SDL_FPoint{ bottomLeftCorner.x, bottomLeftCorner.y },
        SDL_Color{ 255, 255, 255, 255 }
    };
    vertices.push_back(vertex3);

    SDL_Vertex vertex4
    {
        SDL_FPoint{ bottomRightCorner.x, bottomRightCorner.y },
        SDL_Color{ 255, 255, 255, 255 }
    };
    vertices.push_back(vertex4);

    //vertices[2].tex_coord = SDL_FPoint{ m_rect.x * invWidth, (m_rect.y + m_rect.h) * invHeight };
    //vertices[3].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, (m_rect.y + m_rect.h) * invHeight };

    indices = { 0, 1, 2, 2, 1, 3 };
    std::cout << vertices[0].color.a << std::endl;
    //Model house("house", vertices, indices, texture);
    //house.ExportToJson();
    Model::LoadModel("assets/house.model");
    return 0;

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
    ImGui_ImplSDLRenderer_Init(renderer.GetHandle());

    InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");

    //std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture("assets/runner.png");

    Sprite sprite(texture);
    sprite.Resize(256, 256);

    sprite.SetRect(SDL_Rect{ 0, 0, 32, 32 });

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

            std::cout << frameIndex << std::endl;
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

        sprite.Draw(renderer, transformParent);
        sprite.Draw(renderer, transform);

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
