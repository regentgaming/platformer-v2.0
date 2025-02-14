#include "object.hpp"
#include "physics.hpp"


Object::Object(Color color_p, BoundingBox hitbox_p, Vector2D position_p, Physics* Physics, bool isOneWay_p) {
    color = color_p;
    hitbox = hitbox_p;
    position = position_p;
    isOneWay = isOneWay_p;
    Physics->addStatic(this);
}

void Object::draw(SDL_Renderer* renderer) {
    SDL_FRect rect = hitbox.convertToFRect();
    SDL_SetRenderDrawColor(renderer,color.getRed(),color.getGreen(),color.getBlue(),SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(renderer,&rect);
    
}