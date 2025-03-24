#include <Platformer-V2.0/physics.hpp>

//adds an Object to the statics list
void Physics::addStatic(ICollidable& object) {
    Physics::statics.push_back(&object);
}

//adds a DynamicObject to the dynamics list
void Physics::addDynamic(ICollidable& object) {
    Physics::dynamics.push_back(&object);
}

//returns the statics list
const std::vector<ICollidable*>& Physics::getStatics() const {
    return statics;
}

//returns the dynamics list
const std::vector<ICollidable*>& Physics::getDynamics() const {
    return dynamics;
}