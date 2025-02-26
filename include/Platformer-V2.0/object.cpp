#include "object.hpp"
#include "physics.hpp"


Object::Object(Color color_p, BoundingBox hitbox_p, Physics* physics, bool isOneWay_p) {
    color = color_p;
    hitbox = hitbox_p;
    isOneWay = isOneWay_p;
    physics->addStatic(this);
}

Object::Object(Color color_p, BoundingBox hitbox_p) {
    color = color_p;
    hitbox = hitbox_p;
    isOneWay = false;
}

void Object::draw(SDL_Renderer* renderer) {
    SDL_FRect rect = hitbox.convertToFRect();
    SDL_SetRenderDrawColor(renderer,color.getRed(),color.getGreen(),color.getBlue(),SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(renderer,&rect);
}