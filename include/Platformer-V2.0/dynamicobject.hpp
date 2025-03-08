#pragma once
#include "object.hpp"

/**
 * Represents all Objects that are affected by physics and are able to move
 * 
 * Inherits from Object
 */
class DynamicObject : public Object {
    private:
        /// the Vector2D for the velocity of the DynamicObject
        Vector2D velocity;
        /// the Vector2D for the acceleration of the DynamicObject
        Vector2D acceleration;
        /// whether the DynamicObject is on the ground or not
        bool onGround;
    protected:
        // the friction the object experiences while on the ground
        double friction;

    public:
        /**
         * Builds a new DynamicObject object from a Color, a BoundingBox, and a Physics object
         * @param color_p the Color of the DynamicObject
         * @param hitbox_p the BoundingBox of the DynamicObject
         * @param physics the Physics object the DynamicObject follows the rules of
         * @return a DynamicObject object
         */
        DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics);

        /**
         * The function that runs every frame to run all physics operations on the DynamicObject
         * @param physics the physics object to pull information for collisions and gravity
         * @param deltaTime the length of time that passes between each frame
         */
        virtual void update(Physics* physics,double deltaTime);

        /**
         * Handles the collisions in the Y direction
         * @param physics the Physics object to pull information from
         * @param other the other object the DynamicObject is colliding with
         * @param type a string represeting the type passed in (used for special interactions)
         */
        void handleCollisionY(Physics* physics, ICollidable* other, std::string type);

        /**
         * Handles the collisions in the X direction
         * @param physics the Physics object to pull information from
         * @param other the other object the DynamicObject is colliding with
         * @param type a string represeting the type passed in (used for special interactions)
         */
        void handleCollisionX(Physics* physics, ICollidable* other, std::string type);

        /**
         * A function called by DynamicObject::update to check if an object is colliding with anything in the Y direction
         * @param dynamic the object to check collision of (usually ```this``` is passed in)
         * @param physics the Physics object to pull information from
         */
        void detectCollisionY(ICollidable* dynamic, Physics* physics);

        /**
         * A function called by DynamicObject::update to check if an object is colliding with anything in the X direction
         * @param dynamic the object to check collision of (usually ```this``` is passed in)
         * @param physics the Physics object to pull information from
         */
        void detectCollisionX(ICollidable* dynamic, Physics* physics);

        /**
         * Returns the velocity of the DynamicObject
         * @return the velocity of the DynamicObject
         */
        Vector2D* getVelocity();

       /**
         * Returns the acceleration of the DynamicObject
         * @return the acceleration of the DynamicObject
         */
        Vector2D* getAcceleration();

        /**
         * Returns is the DynamicObject is on the ground or not
         * @returns true if the DynamicObject is on the ground, false otherwise
         */
        bool isOnGround();

        /**
         * Sets the onGround flag to a new value
         * @param val the new value to set the flag too
         */
        void setOnGround(bool val);

        /**
         * Returns the type of this object
         * @return a string that is the type
         */
        virtual std::string typeOf();
};