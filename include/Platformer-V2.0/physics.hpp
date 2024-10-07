#include "icollidable.hpp"
#include <vector>

class Physics {
    static std::vector<ICollidable> statics;
    static std::vector<ICollidable> dynamics;
    //Dummy virtual function to make the class abstract
    virtual void makingAbstract() = 0;

    public:
        struct Vector2D {
            private:
                double x;
                double y;
            public:
                Vector2D(double x, double y) {
                    this->x = x;
                    this->y = y;
                }
                
                /**
                 * @brief Returns the x value
                 * @return the x value
                 */
                double getX() {return x;}
                /**
                 * @brief Returns the y value
                 * @return the y value
                 */
                double getY() {return y;}

                Vector2D operator+(Vector2D const& other) {
                    Vector2D ret = Vector2D(x + other.x, y + other.y);
                }
        };




        /**
         * @brief Adds an ICollidable object to the list of static objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        static void addStatic(ICollidable object) {
            if (&statics == nullptr) {
                statics = std::vector<ICollidable>();
            }
            statics.push_back(object);
        }

        /**
         * @brief Adds an ICollidable object to the list of dynamic objects.
         * If the list has nothing in it, instantiates the list
         * @param object The object to be added
         * @return None
         */
        static void addDynamic(ICollidable object) {
            if (&dynamics == nullptr) {
                dynamics = std::vector<ICollidable>();
            }
            dynamics.push_back(object);
        }
};