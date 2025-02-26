#pragma once
#include "SDL2/SDL.h"

/**
 * @brief An interface class used to represent all objects inside the Physics class
 */
class ICollidable {
    public:
        virtual void draw(SDL_Renderer* renderer) = 0;
};