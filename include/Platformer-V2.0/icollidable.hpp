#pragma once
#include "SDL2/SDL.h"

/**
 * An interface class used to represent all objects inside the Physics class
 */
class ICollidable {
    public:

        /**
         * A function that is draws the Object on the screen
         * @param renderer the SDL_Renderer pointer to the renderer that draws everything
         */
        virtual void draw(SDL_Renderer* renderer) = 0;
};