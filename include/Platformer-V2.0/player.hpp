#pragma once
#include "dynamicobject.hpp"

class Player : public DynamicObject {
    public:
        Player(Color color_p, BoundingBox hitbox_p, Physics* physics);
        void jump();
        void move(int dir);
        void update(Physics* physics,double deltaTime);
};