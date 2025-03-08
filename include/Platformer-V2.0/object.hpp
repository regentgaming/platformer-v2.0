#pragma once
#include "physics.hpp"

/**
 * The class to represent static objects and the base class for DynamicObject
 * 
 * Impliments ICollidable
 */
class Object : public ICollidable {
    private:
        /// whether or not the Object is a one-way platform (W.I.P.)
        bool isOneWay;

    protected:
        /**
         * Protected constructor to use in subclasses
         * @param color_p the Color of the Object
         * @param hitbox_p the BoundingBox of the Object
         * @return an Object object
         */
        Object(Color color_p, BoundingBox hitbox_p);

    public:
        /**
         * Builds a new Object object from a Color, a BoundingBox, a Physics object, and a boolean flag
         * @param color_p the Color of the Object
         * @param hitbox_p the BoundingBox of the Object
         * @param physics the Physics object the Object follows the rules of
         * @param isOneWay_p a boolean flag representing if the platform is one-way or not
         * @return an Object object
         */
        Object(Color color_p, BoundingBox hitbox_p, Physics* physics, bool isOneWay_p);

        /**
         * Returns the color of the Object
         * @return the color of the Object
         */
        Color* getColor();

        /**
         * Returns the hitbox of the Object
         * @return the hitbox of the Object
         */
        BoundingBox* getHitbox();

        /**
         * Returns if the Object is one-way or not
         * @return if the Object is one-way or not
         */
        bool getOneWay();

        /**
         * A function that is draws the Object on the screen
         * @param renderer the SDL_Renderer pointer to the renderer that draws everything
         */
        void draw(SDL_Renderer* renderer);

        /**
         * Returns the type of this object
         * @return a string that is the type
         */
        virtual std::string typeOf();
};
