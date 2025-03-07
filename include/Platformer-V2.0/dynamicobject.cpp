#include "dynamicobject.hpp"
#include <cmath>

#define MAX_VEL_X 5
#define MAX_VEL_Y 10
#define FRICTION 0.05

//the public constructor for building a DynamicObject
DynamicObject::DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics) : Object::Object(color_p, hitbox_p) {
    physics->addDynamic(this);
    onGround = false;
}

//returns the velocity
Vector2D* DynamicObject::getVelocity() {
    return &velocity;
}

//returns the acceleration
Vector2D* DynamicObject::getAcceleration() {
    return &acceleration;
}

//returns if it is on the ground or not
bool DynamicObject::isOnGround() {
    return onGround;
}

//sets whether it is on the ground or not
void DynamicObject::setOnGround(bool val) {
    onGround = val;
}

//right now these two functions ignore if the static object is a one-way platform or not (only collidable from above, can walk through sides or jump up through it)
//also dynamic objects are unable to be pushed right now
//will be remedied soon^tm

//detects collisions in the y direction
void DynamicObject::detectCollisionY(ICollidable* dynamic, Physics* physics) {
    onGround = false;
    for (ICollidable* barrier : physics->getStatics()) {
        if (((Object*)barrier)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionY(physics,((Object*)barrier)->getHitbox());
        }
    }
    for (ICollidable* other : physics->getDynamics()) {
        if (other == dynamic) {
            continue;
        }
        if (((DynamicObject*)other)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionY(physics,((DynamicObject*)other)->getHitbox());
        }
    }
}

//detects collisions in the x direction
void DynamicObject::detectCollisionX(ICollidable* dynamic, Physics* physics) {
    for (ICollidable* barrier : physics->getStatics()) {
        if (((Object*)barrier)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionX(physics,((Object*)barrier)->getHitbox());
        }
    }
    for (ICollidable* other : physics->getDynamics()) {
        if (other == dynamic) {
            continue;
        }
        if (((DynamicObject*)other)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionX(physics,((DynamicObject*)other)->getHitbox());
        }
    }
}

//handles collisions in the y direction
void DynamicObject::handleCollisionY(Physics* physics, BoundingBox* other) {
    BoundingBox* hitbox = getHitbox();
    if ((velocity.getY()) > 0.0) {
        hitbox->move(0,(other->UL.getY()) - (hitbox->LR.getY()));
        velocity.setY(0);
        onGround = true;
    } else if ((velocity.getY()) < 0.0) {
        hitbox->move(0,(other->LR.getY() - hitbox->UL.getY()));
        velocity.setY(velocity.getY() * -1);
    }
}

//handles collisions in the y direction
void DynamicObject::handleCollisionX(Physics* physics, BoundingBox* other) {
    BoundingBox* hitbox = getHitbox();
    if ((velocity.getX()) > 0.0) {
        hitbox->move(other->UL.getX() - hitbox->LR.getX(),0);
        velocity.setX(0);
    } else if ((velocity.getX()) < 0.0) {
        hitbox->move(other->LR.getX() - hitbox->UL.getX(),0);
        velocity.setX(0);
    }
}

//update function for each frame
void DynamicObject::update(Physics* physics,double deltaTime) {
    // onGround = false;
    if (!onGround) {
        (acceleration.setY(physics->gravity));
    } else {
        (acceleration.setY(0));
    }

    BoundingBox* hitbox = getHitbox();
    
    velocity.setY((velocity.getY()) + ((acceleration.getY()) * deltaTime ));
    hitbox->move(0, velocity.getY());
    detectCollisionY(this, physics);

    velocity.setX((velocity.getX()) + ((acceleration.getX()) * deltaTime));
    hitbox->move(velocity.getX(), 0);
    detectCollisionX(this, physics);

    if ((velocity.getY()) > MAX_VEL_Y) {
        velocity.setY(MAX_VEL_Y);
    } else if ((velocity.getY()) < (MAX_VEL_Y * -1)) {
        velocity.setY(-1 * MAX_VEL_Y);
    }

    if ((velocity.getX()) > MAX_VEL_X) {
        velocity.setX(MAX_VEL_X);
    } else if ((velocity.getX()) < (MAX_VEL_X * -1)) {
        velocity.setX(-1 * MAX_VEL_X);
    }
    if (acceleration.getX() == 0 && onGround) {
        velocity.setX(velocity.getX() + velocity.getX() * -1 * FRICTION);
        if (fabs(velocity.getX()) < 0.01) {
            velocity.setX(0);
        }
    }
}
