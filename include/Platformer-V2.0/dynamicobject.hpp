#pragma once
#include "object.hpp"

class DynamicObject : public Object {
    private:
        Vector2D velocity;
        Vector2D acceleration;
    public:
        bool onGround;
        DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics);
        virtual void update(Physics* physics,double deltaTime);
        void handleCollisionY(Physics* physics, BoundingBox* other);
        void handleCollisionX(Physics* physics, BoundingBox* other);
        void detectCollisionY(ICollidable* dynamic, Physics* physics);
        void detectCollisionX(ICollidable* dynamic, Physics* physics);
        Vector2D* getVelocity();
        Vector2D* getAcceleration();
};