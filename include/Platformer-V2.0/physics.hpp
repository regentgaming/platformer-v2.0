#pragma once
#include "icollidable.hpp"
#include "util.hpp"
#include <vector>

class Physics {
    std::vector<ICollidable*> statics;
    std::vector<ICollidable*> dynamics;

    public:

        const double gravity = 10.0;

        /**
         * @brief Adds an ICollidable object to the list of static objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        void addStatic(ICollidable* object);

        /**
         * @brief Adds an ICollidable object to the list of dynamic objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        void addDynamic(ICollidable* object);

        std::vector<ICollidable*> getStatics() {
            return statics;
        }

        std::vector<ICollidable*> getDynamics() {
            return dynamics;
        }

        //static void detectCollision();
};