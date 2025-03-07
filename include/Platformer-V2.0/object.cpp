#include "object.hpp"

//the public constructor for building an Object
Object::Object(Color color_p, BoundingBox hitbox_p, Physics* physics, bool isOneWay_p) {
    color = color_p;
    hitbox = hitbox_p;
    isOneWay = isOneWay_p;
    physics->addStatic(this);
}

//protected constructor for subclasses
Object::Object(Color color_p, BoundingBox hitbox_p) {
    color = color_p;
    hitbox = hitbox_p;
    isOneWay = false;
}

//returns the color
Color* Object::getColor() {
    return &color;
}

//returns the hitbox
BoundingBox* Object::getHitbox() {
    return &hitbox;
}

//draws the Object
void Object::draw(SDL_Renderer* renderer) {
    SDL_FRect rect = hitbox.convertToFRect();
    SDL_SetRenderDrawColor(renderer,color.getRed(),color.getGreen(),color.getBlue(),SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer,&rect);
}