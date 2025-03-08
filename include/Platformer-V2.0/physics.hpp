#pragma once
#include "icollidable.hpp"
#include "util.hpp"
#include <vector>

/**
 * A class that contains all the physics objects and constants for the project
 */
class Physics {
    /// a vector containing all the static objects for the project
    std::vector<ICollidable*> statics;
    /// a vector containing all the dynamic objects for the project
    std::vector<ICollidable*> dynamics;

    public:
        /// the acceleration due to gravity for the project (not real world accurate)
        const double gravity = 400;

        /**
         * Adds an ICollidable object to the list of static objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         */
        void addStatic(ICollidable* object);

        /**
         * Adds an ICollidable object to the list of dynamic objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         */
        void addDynamic(ICollidable* object);

        /**
         * Returns the static object vector
         * @return the static object vector
         */
        std::vector<ICollidable*> getStatics();

        /**
         * Returns the dynamic object vector
         * @return the dynamic object vector
         */
        std::vector<ICollidable*> getDynamics();
};