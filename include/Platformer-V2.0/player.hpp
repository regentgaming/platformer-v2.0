#pragma once
#include "dynamicobject.hpp"

/**
 * Represents the special DynamicObject that the player controls
 * 
 * Inherits from DynamicObject
 */
class Player : public DynamicObject {
    public:
        /**
         * Builds a new Player object from a Color, a BoundingBox, and a Physics object
         * @param color_p the Color of the Player
         * @param hitbox_p the BoundingBox of the Player
         * @param physics the Physics object the Player follows the rules of
         * @return a Player object
         */
        Player(Color color_p, BoundingBox hitbox_p, Physics* physics);

        /**
         * The function that when triggered, makes the player jump
         */
        void jump();

        /**
         * The function that applies left and right accelerations to the player
         * @param dir what determines the direction of the movement: 1 is +x, -1 is -x, 0 is standing still
         */
        void move(int dir);

        /**
         * The function that runs every frame to run all physics operations on the Player
         * @param physics the physics object to pull information for collisions and gravity
         * @param deltaTime the length of time that passes between each frame
         */
        void update(Physics* physics,double deltaTime);
};