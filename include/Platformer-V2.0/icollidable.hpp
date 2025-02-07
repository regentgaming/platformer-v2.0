/**
 * @brief An interface class used to represent all objects inside the Physics class
 */
class ICollidable {
    public:
        virtual void handleCollision(ICollidable& other) = 0;
};