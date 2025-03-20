#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H


#include "SDL3/SDL.h"
#include <string>
#include "util.hpp"

/**
 * An interface class used to represent all objects inside the Physics class
 */
class ICollidable {
    public:

        /// the color of the Object
        Color color;
        /// the hitbox of the Object
        BoundingBox hitbox;

        /**
         * A function that is draws the Object on the screen
         * @param renderer the SDL_Renderer pointer to the renderer that draws everything
         */
        virtual void draw(SDL_Renderer* renderer) = 0;


        /**
         * Returns the hitbox of the Object
         * @return the hitbox of the Object
         */
        virtual BoundingBox* getHitbox() = 0;
};

#endif