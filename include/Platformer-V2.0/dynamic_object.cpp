#include <Platformer-V2.0/dynamic_object.hpp>
#include <cmath>
#include <iostream>

#define MAX_VEL_X 200
#define MAX_VEL_Y 500
#define FRICTION 5

//the public constructor for building a DynamicObject
DynamicObject::DynamicObject(Color color_p, BoundingBox hitbox_p, Physics& physics) : Object::Object(color_p, hitbox_p) {
    physics.addDynamic(*this);
    velocity = Vector2D(0, 0);
    acceleration = Vector2D(0, 0);
    friction = FRICTION;
    air_res = friction * 0.1;
    onGround = false;
}

//returns the velocity
const Vector2D& DynamicObject::getVelocity() const {
    return velocity;
}

//sets velocity
void DynamicObject::setVelocity(double x, double y) {
    velocity.setX(x);
    velocity.setY(y);
}

//returns the acceleration
const Vector2D& DynamicObject::getAcceleration() const{
    return acceleration;
}

//sets acceleration
void DynamicObject::setAcceleration(double x, double y) {
    acceleration.setX(x);
    acceleration.setY(y);
}

//returns if it is on the ground or not
bool DynamicObject::isOnGround() const {
    return onGround;
}

//sets whether it is on the ground or not
void DynamicObject::setOnGround(bool val) {
    onGround = val;
}

//handles collisions
void DynamicObject::handleCollision(DynamicObject& dynamic, Physics& physics, bool isYAxis, ICollidable& other) {
    if (isYAxis) {
        dynamic.handleCollisionY(physics, other);
    } else {
        dynamic.handleCollisionX(physics, other);
    }
}

//detects collisions
void DynamicObject::detectCollision(DynamicObject& dynamic, Physics& physics, bool isYAxis) const {
    if (isYAxis) {dynamic.onGround = false;};
    //check if colliding with any static object
    for (ICollidable* barrier : physics.getStatics()) {
        if ((*barrier).getHitbox().isIntersecting(dynamic.getHitbox())) {
            dynamic.handleCollision(dynamic, physics, isYAxis, *barrier);
        }
    }
    //check if colliding with any dynamic object
    for (ICollidable* other : physics.getDynamics()) {
        if (other == &dynamic) { //make sure its not colliding with itself
            continue;
        }
        if ((*other).getHitbox().isIntersecting(dynamic.getHitbox())) {
            dynamic.handleCollision(dynamic, physics, isYAxis, *other);
        }
    }
}

//handles collisions in the y direction
void DynamicObject::handleCollisionY(Physics& physics, ICollidable& other) {
    BoundingBox& hitbox = getHitbox();
    bool oneWay = other.getOneWay();

    //checks what side it hit from, and then moves it out of the object towards that side
    if (velocity.getY() > 0.0) {
        hitbox.move(0, other.getHitbox().UL.getY() - hitbox.LR.getY());
        velocity.setY(0);
        onGround = true;
    //if object is one way, ignore bottom collisions
    } else if ((velocity.getY() < 0.0 && !oneWay)) {
        hitbox.move(0, other.getHitbox().LR.getY() - hitbox.UL.getY());
        velocity.setY(velocity.getY() * -1);
    }
}

//handles collisions in the x direction
void DynamicObject::handleCollisionX(Physics& physics, ICollidable& other) {
    BoundingBox& hitbox = getHitbox();
    bool oneWay = other.getOneWay();

    //checks what side it hit from, and then moves it out of the object towards that side
    //if object is one way, ignore side collisions while on ground
    if (!oneWay || oneWay && velocity.getY() > 0) {
        if (velocity.getX() > 0.0) {
            hitbox.move(other.getHitbox().UL.getX() - hitbox.LR.getX(), 0);
        } else if (velocity.getX() < 0.0) {
            hitbox.move(other.getHitbox().LR.getX() - hitbox.UL.getX(), 0);
        }
        
        try {
            DynamicObject& dyn = dynamic_cast<DynamicObject&>(other);
            dyn.setVelocity(velocity.getX(), dyn.getVelocity().getY());
        } catch (const std::bad_cast& e) {
            velocity.setX(0);
        }
    }
}

//helper function to apply gravity
void DynamicObject::applyGravity(Physics& physics) {
    if (!isOnGround()) {
        setAcceleration(getAcceleration().getX(), physics.gravity);
    } else {
        setAcceleration(getAcceleration().getX(), 0);
    }
}

//helper function to clamp the velocity
void DynamicObject::clampVelocity() {
    if (fabs(getVelocity().getX()) > MAX_VEL_X) {
        setAcceleration(0, getAcceleration().getY());
    }

    if (getVelocity().getY() > MAX_VEL_Y) {
        setVelocity(getVelocity().getX(), MAX_VEL_Y);
    } else if (getVelocity().getY() < (MAX_VEL_Y * -1)) {
        setVelocity(getVelocity().getX(), -1 * MAX_VEL_Y);
    }
}

//helper function to apply friction
void DynamicObject::applyFriction(double deltaTime) {
    double resistance = onGround ? friction : air_res;
    if (acceleration.getX() == 0) {
        velocity.setX(velocity.getX() + velocity.getX() * -1 * resistance * deltaTime);
        if (fabs(velocity.getX()) < 0.01) {
            velocity.setX(0);
        }
    }
}

//helper function to update the position
void DynamicObject::updatePosition(bool isYAxis, double deltaTime) {
    if (isYAxis) {
        velocity.setY(velocity.getY() + (acceleration.getY() * deltaTime ));
        hitbox.move(0, velocity.getY() * deltaTime);
    } else {
        velocity.setX(velocity.getX() + (acceleration.getX() * deltaTime));
        hitbox.move(velocity.getX() * deltaTime, 0);
    }
}

//update function for each frame
void DynamicObject::update(Physics& physics, double deltaTime) {
    applyGravity(physics);

    //update vertical position and collisions
    updatePosition(true, deltaTime);
    detectCollision(*this, physics, true);

    //update horizontal position and collisions
    updatePosition(false, deltaTime);
    detectCollision(*this, physics, false);
    
    //ensure velocity stays in bounds
    clampVelocity();

    //apply friction
    applyFriction(deltaTime);
}
