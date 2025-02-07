#include "icollidable.hpp"
#include "util.hpp"
#include <vector>

class Physics {
    static std::vector<ICollidable&> statics;
    static std::vector<ICollidable&> dynamics;
    //Dummy virtual function to make the class abstract
    virtual void makingAbstract() = 0;

    public:
        /**
         * @brief Adds an ICollidable object to the list of static objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        static void addStatic(ICollidable& object) {
            if (&statics == nullptr) {
                statics = std::vector<ICollidable&>();
            }
            statics.push_back(object);
        }

        /**
         * @brief Adds an ICollidable object to the list of dynamic objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        static void addDynamic(ICollidable& object) {
            if (&dynamics == nullptr) {
                dynamics = std::vector<ICollidable&>();
            }
            dynamics.push_back(object);
        }

        static void detectCollision();
};