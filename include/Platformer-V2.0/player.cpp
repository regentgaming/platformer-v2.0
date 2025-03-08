#include "player.hpp"

#define JUMP_FORCE -300
#define MOVE_FORCE 300
#define FRICTION 10

//public constructor for building a Player object
Player::Player(Color color_p, BoundingBox hitbox_p, Physics* physics) : DynamicObject::DynamicObject(color_p, hitbox_p, physics) {
    friction = FRICTION;
}

//function that makes the Player jump
void Player::jump() {
    if (isOnGround()) {
        setOnGround(false);
        (getVelocity()->setY((getVelocity()->getY()) + JUMP_FORCE));
    }
}

//function that makes the Player move
void Player::move(int dir) {
    if (dir > 0) {
        (getAcceleration()->setX(MOVE_FORCE));
    } else if (dir < 0) {
        (getAcceleration()->setX(-1 * MOVE_FORCE));
    } else {
        (getAcceleration()->setX(0));
    }
}

//update function for each frame
void Player::update(Physics* physics,double deltaTime) {
    DynamicObject::update(physics, deltaTime);
}

//returns the type of the object
std::string Player::typeOf() {
    return "Player";
}