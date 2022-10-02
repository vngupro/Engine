#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "SDLpp.hpp"
#include "SDLppWindow.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppTexture.hpp"
#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include "InputSystem.hpp"
#include "Math.hpp"

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    ResourceManager::Purge();
    std::shared_ptr<SDLppTexture> runner = ResourceManager::GetTexture(renderer, "assets/run.png");// SDLppTexture::LoadFromFile(renderer, "assets/runner.png");
    Sprite sprite(runner);
    std::cout << runner.use_count() << std::endl;
    std::shared_ptr<SDLppTexture> runner2 = ResourceManager::GetTexture(renderer, "assets/run.png");
    std::cout << runner.use_count() << std::endl;

    sprite.Resize(256, 256);

    sprite.SetRect(SDL_Rect{ 0, 0, 32, 32 });

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    int frameIndex = 0;
    int frameCount = 5;
    float timer = 0.0f;

    bool isOpen = true;
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
        }

        SDL_Event event;
        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;
        }

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();

        sprite.Draw(renderer, 147, 257);
        renderer.Present();

        InputSystem::BindKeyPressed(SDLK_SPACE, "Attack");
        InputSystem::BindMouseButtonPressed(SDL_BUTTON_LEFT, "Attack");
        //InputSystem::OnAction("Attack", []()
        //    {

        //    });
    }

    runner.reset();
    runner2.reset();
    ResourceManager::Purge();
    //Vector2<float> v = Vector2<float>::up();
    Vector2 v = Vector2(1.f, 1.f);
    std::cout << v << std::endl;    // 1, 1
    v = v + v;
    std::cout << v << std::endl;    // 2, 2
    v += v;
    std::cout << v << std::endl;    // 4, 4
    v = v * 2.f;
    std::cout << v << std::endl;    // 8, 8
    v *= 2.f;
    std::cout << v << std::endl;    // 16, 16
    v = v / 2.f;
    std::cout << v << std::endl;    // 8, 8
    v /= 2.f;
    std::cout << v << std::endl;    // 4, 4

    Transform transform;
    transform.SetPosition(Vector2(42.f, -6.f));
    transform.SetRotation(-270.f);
    transform.SetScale(Vector2(0.5f, 2.0f));
    std::cout << transform << std::endl;
    
    std::cout << transform.TransformPoint(Vector2(0.f, 0.f)) << std::endl;
    std::cout << transform.TransformPoint(Vector2(10.f, 0.f)) << std::endl;
    std::cout << transform.TransformPoint(Vector2(0.f, 10.f)) << std::endl;
    std::cout << transform.TransformPoint(Vector2(21.f, -3.f)) << std::endl;

    transform.SetScale(Vector2(-0.5f, -2.0f));
    std::cout << transform.TransformPoint(Vector2(-42.f, -42.f)) << std::endl;

    return 0;
}