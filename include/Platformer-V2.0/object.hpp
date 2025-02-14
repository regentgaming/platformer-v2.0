#pragma once
#include "icollidable.hpp"
#include "util.hpp"
#include "physics.hpp"

class Object : public ICollidable {
    private:
        Color color;
        BoundingBox hitbox;
        bool isOneWay;
    public:
        Object(Color color_p, BoundingBox hitbox_p, Physics* Physics, bool isOneWay_p = false);

        Color getColor() {
            return color;
        }

        BoundingBox getHitbox() {
            return hitbox;
        }

        //virtual void handleCollision(ICollidable& other);

        void draw(SDL_Renderer* renderer);
};
