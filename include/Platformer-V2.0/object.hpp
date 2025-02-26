#pragma once
#include "icollidable.hpp"
#include "util.hpp"
#include "physics.hpp"

class Object : public ICollidable {
    private:
        Color color;
        BoundingBox hitbox;
        bool isOneWay;
    protected:
        Object(Color color_p, BoundingBox hitbox_p);
    public:
        Object(Color color_p, BoundingBox hitbox_p, Physics* physics, bool isOneWay_p);

        Color* getColor() {
            return &color;
        }

        BoundingBox* getHitbox() {
            return &hitbox;
        }

        void draw(SDL_Renderer* renderer);
};
