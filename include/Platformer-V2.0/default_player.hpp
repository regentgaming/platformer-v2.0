#ifndef DEFAULT_PLAYER_H
#define DEFAULT_PLAYER_H


#include <Platformer-V2.0/dynamic_object.hpp>

/**
 * Represents the special DynamicObject that the player controls
 * 
 * Inherits from DynamicObject
 * 
 * Can be inherited from to add new functinality to the player
 */
class DefaultPlayer : public DynamicObject {
    public:
        /**
         * Builds a new DefaultPlayer object from a Color, a BoundingBox, and a Physics object
         * @param color_p the Color of the DefaultPlayer
         * @param hitbox_p the BoundingBox of the DefaultPlayer
         * @param physics the Physics object the DefaultPlayer follows the rules of
         * @return a DefaultPlayer object
         */
        DefaultPlayer(Color color_p, BoundingBox hitbox_p, Physics* physics);

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
         * The function that runs every frame to run all physics operations on the DefaultPlayer
         * @param physics the physics object to pull information for collisions and gravity
         * @param deltaTime the length of time that passes between each frame
         */
        virtual void update(Physics* physics,double deltaTime);

        /**
         * Returns the type of this object
         * @return a string that is the type
         */
        virtual std::string typeOf();
};

#endif