#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <icollidable.hpp>

class Screen {
    /// a vector containing all the static objects for the scene
    std::vector<ICollidable*> statics;
    /// a vector containing all the dynamic objects for the scene
    std::vector<ICollidable*> dynamics;
};

#endif