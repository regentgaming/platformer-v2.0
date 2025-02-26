#pragma once
#include "object.hpp"

class DynamicObject : public Object {
    private:
        Vector2D velocity;
        Vector2D acceleration;
        bool onGround;
    public:
        DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics);
        void update(Physics* physics,double deltaTime);
        void handleCollision(Physics* physics, BoundingBox* other);
};