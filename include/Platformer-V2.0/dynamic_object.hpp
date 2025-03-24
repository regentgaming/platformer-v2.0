#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include <Platformer-V2.0/object.hpp>

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

        /**
         * Handles the collisions in the Y direction
         * @param physics the Physics object to pull information from
         * @param other the other object the DynamicObject is colliding with
         */
        void handleCollisionY(Physics& physics, ICollidable& other);

        /**
         * Handles the collisions in the X direction
         * @param physics the Physics object to pull information from
         * @param other the other object the DynamicObject is colliding with
         */
        void handleCollisionX(Physics& physics, ICollidable& other);
        
    protected:
        // the friction the object experiences while on the ground
        double friction;
        // the friction the object experiences while in the air
        double air_res;

    public:
        /**
         * Builds a new DynamicObject object from a Color, a BoundingBox, and a Physics object
         * @param color_p the Color of the DynamicObject
         * @param hitbox_p the BoundingBox of the DynamicObject
         * @param physics the Physics object the DynamicObject follows the rules of
         * @return a DynamicObject object
         */
        DynamicObject(Color color_p, BoundingBox hitbox_p, Physics& physics);

        /**
         * The function that runs every frame to run all physics operations on the DynamicObject
         * @param physics the physics object to pull information for collisions and gravity
         * @param deltaTime the length of time that passes between each frame
         */
        virtual void update(Physics& physics,double deltaTime);

        /**
         * Handles collisions
         * @param dynamic the object to check collision of (usually ```this``` is passed in)
         * @param physics the Physics object to pull information from
         * @param isYAxis flag to determine the axis of collision
         * @param other the other object the DynamicObject is colliding with
         */
        void handleCollision(DynamicObject& dynamic, Physics& physics, bool isYAxis, ICollidable& other);

        /**
         * A function called by DynamicObject::update to check if an object is colliding with anything in either direction
         * @param dynamic the object to check collision of (usually ```this``` is passed in)
         * @param physics the Physics object to pull information from
         * @param isYAxis flag to determine the axis of collision
         */
        void detectCollision(DynamicObject& dynamic, Physics& physics, bool isYAxis) const;

        /**
         * Returns the velocity of the DynamicObject
         * @return the velocity of the DynamicObject
         */
        const Vector2D& getVelocity() const;

        /**
         * Allows the velocity to be changed
         * @param x the x value
         * @param y the y value
         */
        void setVelocity(double x, double y);

       /**
         * Returns the acceleration of the DynamicObject
         * @return the acceleration of the DynamicObject
         */
        const Vector2D& getAcceleration() const;

        /**
         * Allows the acceleration to be changed
         * @param x the x value
         * @param y the y value
         */
        void setAcceleration(double x, double y);

        /**
         * Returns is the DynamicObject is on the ground or not
         * @returns true if the DynamicObject is on the ground, false otherwise
         */
        bool isOnGround() const;

        /**
         * Sets the onGround flag to a new value
         * @param val the new value to set the flag too
         */
        void setOnGround(bool val);

        /**
         * Applies gravity to the object
         * @param the physics object to get the gravity constant from
         */
        void applyGravity(Physics& physics);

        /**
         * Clamps the velocity to below a max value
         */
        void clampVelocity();

        /**
         * Applies friction to an object
         * @param deltaTime the length of time that passes between each frame
         */
        void applyFriction(double deltaTime);

        /**
         * Moves the object based on its velocity
         * @param isYAxis flag to determine the axis of movement
         * @param deltaTime the length of time that passes between each frame
         */
        void updatePosition(bool isYAxis, double deltaTime);
};

#endif