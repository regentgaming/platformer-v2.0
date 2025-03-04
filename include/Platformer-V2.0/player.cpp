#include "player.hpp"

#define JUMP_FORCE -3
#define MOVE_FORCE 3

Player::Player(Color color_p, BoundingBox hitbox_p, Physics* physics) : DynamicObject::DynamicObject(color_p, hitbox_p, physics) {}

void Player::jump() {
    if (isOnGround()) {
        setOnGround(false);
        (getVelocity()->setY((getVelocity()->getY()) + JUMP_FORCE));
    }
}

void Player::move(int dir) {
    if (dir > 0) {
        (getAcceleration()->setX(MOVE_FORCE));
    } else if (dir < 0) {
        (getAcceleration()->setX(-1 * MOVE_FORCE));
    } else {
        (getAcceleration()->setX(0));
    }
}

void Player::update(Physics* physics,double deltaTime) {
    DynamicObject::update(physics, deltaTime);
}