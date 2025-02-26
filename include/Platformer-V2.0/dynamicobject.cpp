#include "dynamicobject.hpp"

DynamicObject::DynamicObject(Color color_p, BoundingBox hitbox_p, Physics* physics) : Object::Object(color_p, hitbox_p) {
    physics->addDynamic(this);
    onGround = false;
}

void DynamicObject::update(Physics* physics,double deltaTime) {
    if (!onGround) {
        *(acceleration.getY()) = physics->gravity;
    } else {
        *(acceleration.getY()) = 0;
    }
    velocity = velocity + (acceleration*deltaTime);
    BoundingBox* hitbox = getHitbox();
    hitbox->UL = hitbox->UL + velocity;
    hitbox->LR = hitbox->LR + velocity;
}

void DynamicObject::handleCollision(Physics* physics, BoundingBox* other) {
    BoundingBox* hitbox = getHitbox();
    //i hate all of this it looks so ugly and tons of pointers but its fine
    if (*(hitbox->LR.getX()) > *(other->UL.getX()) || *(hitbox->UL.getX()) < *(other->LR.getX())) {
        if (*(velocity.getY()) > 0.0) {
            *(hitbox->UL.getY()) += *(other->UL.getY()) - *(hitbox->LR.getY());
            *(hitbox->LR.getY()) += *(other->UL.getY()) - *(hitbox->LR.getY());
            *(velocity.getY()) = 0;
            onGround = true;
        } else if (*(velocity.getY()) < 0.0) {
            *(hitbox->UL.getY()) += *(other->LR.getY()) - *(hitbox->UL.getY());
            *(hitbox->LR.getY()) += *(other->LR.getY()) - *(hitbox->UL.getY());
            *(velocity.getY()) = *(velocity.getY()) * -1;
        }
    }

    if (*(hitbox->LR.getY()) < *(other->UL.getY()) || *(hitbox->UL.getY()) > *(other->LR.getY())) {
        if (*(velocity.getX()) > 0.0) {
            *(hitbox->UL.getX()) += *(other->UL.getX()) - *(hitbox->LR.getX());
            *(hitbox->LR.getX()) += *(other->UL.getX()) - *(hitbox->LR.getX());
            *(velocity.getX()) = 0;
        } else if (*(velocity.getX()) < 0.0) {
            *(hitbox->UL.getX()) += *(other->LR.getX()) - *(hitbox->UL.getX());
            *(hitbox->LR.getX()) += *(other->LR.getX()) - *(hitbox->UL.getX());
            *(velocity.getX()) = 0;
        }
    }
    
}