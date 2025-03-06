#include "physics.hpp"

//adds an Object to the statics list
void Physics::addStatic(ICollidable* object) {
    if (&Physics::statics == nullptr) {
        Physics::statics = std::vector<ICollidable*>();
    }
    Physics::statics.push_back(object);
}

//adds a DynamicObject to the dynamics list
void Physics::addDynamic(ICollidable* object) {
    if (&Physics::dynamics == nullptr) {
        Physics::dynamics = std::vector<ICollidable*>();
    }
    Physics::dynamics.push_back(object);
}

//returns the statics list
std::vector<ICollidable*> Physics::getStatics() {
    return statics;
}

//returns the dynamics list
std::vector<ICollidable*> Physics::getDynamics() {
    return dynamics;
}