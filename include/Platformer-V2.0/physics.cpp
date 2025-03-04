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