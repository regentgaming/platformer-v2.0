#include <Platformer-V2.0/default_player.hpp>

#define JUMP_FORCE -300
#define MOVE_FORCE 300
#define FRICTION 10

//public constructor for building a DefaultPlayer object
DefaultPlayer::DefaultPlayer(Color color_p, BoundingBox hitbox_p, Physics& physics) : DynamicObject::DynamicObject(color_p, hitbox_p, physics) {
    friction = FRICTION;
}

//function that makes the DefaultPlayer jump
void DefaultPlayer::jump() {
    if (isOnGround()) {
        setOnGround(false);
        setVelocity(getVelocity().getX(), getVelocity().getY() + JUMP_FORCE);
    }
}

//function that makes the DefaultPlayer move
void DefaultPlayer::move(int dir) {
    if (dir > 0) {
        setAcceleration(MOVE_FORCE, getAcceleration().getY());
    } else if (dir < 0) {
        setAcceleration(-1 * MOVE_FORCE, getAcceleration().getY());
    } else {
        setAcceleration(0, getAcceleration().getY());
    }
}

//update function for each frame
void DefaultPlayer::update(Physics& physics,double deltaTime) {
    DynamicObject::update(physics, deltaTime);
}