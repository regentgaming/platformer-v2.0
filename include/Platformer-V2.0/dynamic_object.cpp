#include <Platformer-V2.0/dynamic_object.hpp>
#include <cmath>
#include <iostream>

#define MAX_VEL_X 200
#define MAX_VEL_Y 500
#define FRICTION 5

//the public constructor for building a DynamicObject
DynamicObject::DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics) : Object::Object(color_p, hitbox_p) {
    physics->addDynamic(this);
    velocity = Vector2D(0,0);
    acceleration = Vector2D(0,0);
    friction = FRICTION;
    air_res = friction * 0.1;
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

//detects collisions in the y direction
void DynamicObject::detectCollisionY(ICollidable* dynamic, Physics* physics) {
    onGround = false;
    for (ICollidable* barrier : physics->getStatics()) {
        if ((barrier)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionY(physics,(barrier),((Object*)barrier)->typeOf());
        }
    }
    for (ICollidable* other : physics->getDynamics()) {
        if (other == dynamic) {
            continue;
        }
        if (((DynamicObject*)other)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollisionY(physics,(other),((DynamicObject*)other)->typeOf());
        }
    }
}

//detects collisions in the x direction
void DynamicObject::detectCollisionX(ICollidable* dynamic, Physics* physics) {
    for (ICollidable* barrier : physics->getStatics()) {
        if (((Object*)barrier)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) {
            ((DynamicObject*)dynamic)->handleCollisionX(physics,(barrier),((Object*)barrier)->typeOf());
        }
    }
    for (ICollidable* other : physics->getDynamics()) {
        if (other == dynamic) {
            continue;
        }
        if (((DynamicObject*)other)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) {
            ((DynamicObject*)dynamic)->handleCollisionX(physics,(other),(*(DynamicObject*)other).typeOf());
        }
    }
}

//handles collisions in the y direction
void DynamicObject::handleCollisionY(Physics* physics, ICollidable* other, std::string type) {
    BoundingBox* hitbox = getHitbox();
    bool isStatic = type == "Object";
    bool oneWay = false;
    if (isStatic) {
        if (((Object*)other)->getOneWay()) {
            oneWay = true;
        }
    }
    if ((velocity.getY()) > 0.0) {
        hitbox->move(0,(other->getHitbox()->UL.getY()) - (hitbox->LR.getY()));
        velocity.setY(0);
        onGround = true;
    } else if (((velocity.getY()) < 0.0 && !oneWay)) {
        hitbox->move(0,(other->getHitbox()->LR.getY() - hitbox->UL.getY()));
        velocity.setY(velocity.getY() * -1);
    }
}

//handles collisions in the y direction
void DynamicObject::handleCollisionX(Physics* physics, ICollidable* other, std::string type) {
    BoundingBox* hitbox = getHitbox();
    bool isDynamic = type == "DynamicObject";
    bool isStatic = type == "Object";
    bool oneWay = false;
    if (isStatic) {
        if (((Object*)other)->getOneWay()) {
            oneWay = true;
        }
    }
    if (!oneWay || oneWay && velocity.getY() > 0) {
        if ((velocity.getX()) > 0.0) {
            hitbox->move(other->getHitbox()->UL.getX() - hitbox->LR.getX(),0);
            if (isDynamic) {
                ((DynamicObject*)other)->getVelocity()->setX(velocity.getX());
            } else {
                velocity.setX(0);
            }
            
        } else if ((velocity.getX()) < 0.0) {
            hitbox->move(other->getHitbox()->LR.getX() - hitbox->UL.getX(),0);
            if (isDynamic) {
                ((DynamicObject*)other)->getVelocity()->setX(velocity.getX());
            } else {
                velocity.setX(0);
            }
        }
    }
}

//update function for each frame
void DynamicObject::update(Physics* physics,double deltaTime) {
    if (!onGround) {
        (acceleration.setY(physics->gravity));
    } else {
        (acceleration.setY(0));
    }

    BoundingBox* hitbox = getHitbox();
    
    velocity.setY((velocity.getY()) + ((acceleration.getY()) * deltaTime ));
    hitbox->move(0, velocity.getY() * deltaTime);
    detectCollisionY(this, physics);

    if ((velocity.getX()) > MAX_VEL_X) {
        acceleration.setX(0);
    } else if ((velocity.getX()) < (MAX_VEL_X * -1)) {
        acceleration.setX(0);
    }

    velocity.setX((velocity.getX()) + ((acceleration.getX()) * deltaTime));
    hitbox->move(velocity.getX() * deltaTime, 0);
    detectCollisionX(this, physics);

    if ((velocity.getY()) > MAX_VEL_Y) {
        velocity.setY(MAX_VEL_Y);
    } else if ((velocity.getY()) < (MAX_VEL_Y * -1)) {
        velocity.setY(-1 * MAX_VEL_Y);
    }

    
    if (acceleration.getX() == 0 && onGround) {
        velocity.setX(velocity.getX() + velocity.getX() * -1 * friction * deltaTime);
        if (fabs(velocity.getX()) < 0.01) {
            velocity.setX(0);
        }
    } else if (acceleration.getX() == 0 && !onGround) {
        velocity.setX(velocity.getX() + velocity.getX() * -1 * air_res * deltaTime);
        if (fabs(velocity.getX()) < 0.01) {
            velocity.setX(0);
        }
    }
}

//returns the type of the object
std::string DynamicObject::typeOf() {
    return "DynamicObject";
}
