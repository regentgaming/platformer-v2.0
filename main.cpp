#include <iostream>
#include "include/SDL2/SDL.h"
#include "include/Platformer-V2.0/physics.hpp"
#include "include/Platformer-V2.0/object.hpp"

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
    Object test = Object(Color(255,0,0),BoundingBox(400,400,40,40),Vector2D(400,400),&physics);
    Object test2 = Object(Color(255,0,255),BoundingBox(500,500,40,40),Vector2D(500,500),&physics);
    while (keep_window_open) {
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        for (ICollidable* object : physics.getStatics()) {
            (*object).draw(renderer);
        }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&windowEvent) > 0) {
            switch(windowEvent.type) {
                case SDL_QUIT:
                keep_window_open = false;
                    break;
            }
        }
    }

    return EXIT_SUCCESS;

}