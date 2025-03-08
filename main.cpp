#include <iostream>
#include "include/SDL3/SDL.h"
#include "include/Platformer-V2.0/player.hpp"

/* 
* helper function for wrapping things around the screen
* will probably be relocated soon
*/
void screenWrap(DynamicObject* dynamic, const int w, const int h) {
    BoundingBox* hitbox = dynamic->getHitbox();
    if (hitbox->LR.getX() < 0) {
        hitbox->moveTo(w,hitbox->UL.getY());
    } else if (hitbox->UL.getX() > w) {
        hitbox->moveTo(0-hitbox->w,hitbox->UL.getY());
    }

    if (hitbox->UL.getY() > h) {
        hitbox->moveTo(hitbox->UL.getX(),0-hitbox->h);
    }
}

int main(int argc, char *argv[]) {
    const int WIDTH = 800, HEIGHT = 600;
    SDL_Init(SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow("Game", WIDTH, HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY  | SDL_WINDOW_RESIZABLE);

    // SDL_SetWindowSurfaceVSync(window,1);
    
    SDL_Event windowEvent;

    if (!window) {
        std::cout << "Failed to create window\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,NULL);
    SDL_SetRenderVSync(renderer,1);
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
    Object test = Object(Color(0,255,0),BoundingBox(-50,500,100,900),&physics,false);
    Object test2 = Object(Color(0,0,255),BoundingBox(100,450,25,100),&physics,true);
    Player player = Player(Color(255,0,0),BoundingBox(300,100,50,50),&physics);
    DynamicObject test3 = DynamicObject(Color(0,0,255),BoundingBox(375,50,50,50),&physics);
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    while (keep_window_open) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() );
        double fps = 1.0/deltaTime;
        
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        for (ICollidable* object : physics.getStatics()) {
            object->draw(renderer);
        }
        for (ICollidable* object : physics.getDynamics()) {
            ((DynamicObject*)object)->update(&physics,deltaTime);
            screenWrap((DynamicObject*)object,WIDTH,HEIGHT);
            object->draw(renderer);
        }
        SDL_RenderPresent(renderer);
        const bool* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_W]) {
                player.jump();
            }
            if (keys[SDL_SCANCODE_A]) {
                player.move(-1);
            } else if (keys[SDL_SCANCODE_D]) {
                player.move(1);
            } else {
                player.move(0);
            }
        while (SDL_PollEvent(&windowEvent) > 0) {
            switch(windowEvent.type) {
                case SDL_EVENT_QUIT:
                keep_window_open = false;
                    break;
            }
        }
    }

    return EXIT_SUCCESS;

}