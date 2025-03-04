#include <iostream>
#include "include/SDL2/SDL.h"
#include "include/Platformer-V2.0/physics.hpp"
#include "include/Platformer-V2.0/player.hpp"

int main(int argc, char *argv[]) {
    const int WIDTH = 800, HEIGHT = 600;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI  | SDL_WINDOW_RESIZABLE);
    
    SDL_Event windowEvent;

    if (!window) {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        std::cout << "Failed to create renderer\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    bool keep_window_open = true;
    Physics physics = Physics();
    Object test = Object(Color(0,255,0),BoundingBox(0,500,100,800),&physics,false);
    Player player = Player(Color(255,0,0),BoundingBox(300,100,50,50),&physics);
    DynamicObject test3 = DynamicObject(Color(0,0,255),BoundingBox(375,50,50,50),&physics);
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    while (keep_window_open) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() );
        
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        for (ICollidable* object : physics.getStatics()) {
            object->draw(renderer);
        }
        for (ICollidable* object : physics.getDynamics()) {
            ((DynamicObject*)object)->update(&physics,deltaTime);
            object->draw(renderer);
        }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&windowEvent) > 0) {
            if (SDL_GetKeyboardState(NULL)[SDLK_w]) {
                std::cout << "jumped\n";
                player.jump();
            }
            switch(windowEvent.type) {
                case SDL_QUIT:
                keep_window_open = false;
                    break;
                case SDL_KEYDOWN:
                    // std::cout << "key press\n";
                    switch (windowEvent.key.keysym.sym) {
                        case SDLK_w:
                            player.jump();
                            break;
                        case SDLK_a:
                            player.move(-1);
                            break;
                        case SDLK_d:
                            player.move(1);
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    // std::cout << "key unpress\n";
                    player.move(0);
                    break;
            }
        }
    }

    return EXIT_SUCCESS;

}