#include "physics.hpp"
#include "dynamicobject.hpp"

void Physics::addStatic(ICollidable* object) {
    if (&Physics::statics == nullptr) {
        Physics::statics = std::vector<ICollidable*>();
    }
    Physics::statics.push_back(object);
}

void Physics::addDynamic(ICollidable* object) {
    if (&Physics::dynamics == nullptr) {
        Physics::dynamics = std::vector<ICollidable*>();
    }
    Physics::dynamics.push_back(object);
}

void Physics::detectCollision(ICollidable* dynamic) {
    for (ICollidable* barrier : statics) {
        if (((Object*)barrier)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollision(this,((Object*)barrier)->getHitbox());
        }
    }
    for (ICollidable* other : dynamics) {
        if (other == dynamic) {
            continue;
        }
        if (((DynamicObject*)other)->getHitbox()->isIntersecting(((DynamicObject*)dynamic)->getHitbox())) { //i apologise for the sin of all this casting
            ((DynamicObject*)dynamic)->handleCollision(this,((DynamicObject*)other)->getHitbox());
        }
    }
}