#include <iostream>
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

    SDLppTexture runner = SDLppTexture::LoadFromFile(renderer, "assets/runner.png");
    Sprite sprite(runner);
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

    //Vector2<int> vect(1, 1);
    //Transform transform;
    //transform.SetPosition(Vector2(42.f, -6.f));
    //transform.SetRotation(-270.f);
    //transform.SetScale(Vector2(0.5f, 2.0f));

    //transform.TransformPoint(Vector2(0.f, 0.f));
    //transform.TransformPoint(Vector2(0.f, 0.f));
    //transform.TransformPoint(Vector2(0.f, 0.f));
    //transform.TransformPoint(Vector2(0.f, 0.f));

    //transform.SetScale(Vector2(-0.5f, -2.0f));
    //transform.TransformPoint(Vector2(-42.f, -42.f));

    return 0;
}
