#pragma once
#include "SDL2/SDL.h"



/**
 * A class to represent a 2 dimensional vector
 */
class Vector2D {
    private:
        /// the x component
        double x;

        /// the y component
        double y;
    public:
        /**
         * Builds a new Vector2D from a x and y position
         * @param x_p the x component
         * @param y_p the y component
         * @return a Vector2D object
         */
        Vector2D(double x_p, double y_p) {
            x = x_p;
            y = y_p;
        }

        /**
         * Default constructor
         * @return a Vector2D object
         */
        Vector2D() = default;

        /**
         * Returns the x component of the vector
         * @return the x value
         */
        double getX() {return x;}

        /**
         * Sets the x component of the vector
         * @param x_p the new x component to set it to
         */
        void setX(double x_p) {
            x = x_p;
        }

        /**
         * Returns the y component of the vector
         * @return the y value
         */
        double getY() {return y;}


        /**
         * Sets the y component of the vector
         * @param y_p the new y component to set it to
         */
        void setY(double y_p) {
            y = y_p;
        }
};


/**
 * A class representing the bounding box of an object
 */
class BoundingBox {
    public:
        /// vector to the upper-left corner of the box
        Vector2D UL;
        /// vector to the bottom-left corner of the box
        Vector2D LR;
        /// height of the box
        double h;
        /// width of the box
        double w;

        /**
         * Builds a new BoundingBox from a point (the upper-left most point), the width, and the height
         * @param x the left side x value
         * @param y the top side y value
         * @param height the height of the box
         * @param width the width of the box
         * @return a BoundingBox object
         */
        BoundingBox(double x, double y, double height, double width) {
            UL = Vector2D(x,y);
            LR = Vector2D(x+width,y+height);
            h = height;
            w = width;
        }

        /**
         * Default constructor
         * @return a BoundingBox object
         */
        BoundingBox() = default;

        /**
         * A function to check if this BoundingBox is colliding
         * with another BoundingBox
         * @param other the other BoundingBox to check collision against
         * @return true if the 2 BoundingBoxes are colliding, false otherwise
         */
        bool isIntersecting(BoundingBox* other) {
            return (LR.getX() > other->UL.getX() && other->LR.getX() > UL.getX()) && (LR.getY() > other->UL.getY() && other->LR.getY() > UL.getY());
        }

        /**
         * A function to move the BoundingBox by an offset from the current position,
         * maintaining the BoundingBox's size
         * @param dx the change in the box's x position
         * @param dy the change in the box's y position
         */
        void move(double dx, double dy) {
            UL.setX(UL.getX() + dx);
            UL.setY(UL.getY() + dy);
            LR.setX(UL.getX() + w);
            LR.setY(UL.getY() + h);
        }

        /**
         * A function to move the BoundingBox to an absolute position,
         * maintaining the BoundingBox's size
         * @param x the new x position for the box
         * @param y the new y position for the box
         */
        void moveTo(double x, double y) {
            UL.setX(x);
            UL.setY(y);
            LR.setX(UL.getX() + w);
            LR.setY(UL.getY() + h);
        }

        /**
         * A function that is used in the draw functions that converts
         * the BoundingBox into a SDL_FRect that SDL is able
         * to render to the screen
         * @return a SDL_FRect struct representation of the BoundingBox object
         */
        SDL_FRect convertToFRect() {
            SDL_FRect rect;
            rect.x = UL.getX();
            rect.y = UL.getY();
            rect.h = h;
            rect.w = w;
            return rect;
        }
};

/**
 * A class that represents a RGB color
 */
class Color {
    private:
        /// the red value
        int red;
        /// the green value
        int green;
        /// the blue value
        int blue;
    public:
        /**
         * Builds a new Color object from a red, green, and blue value
         * @param r the red value
         * @param g the green value
         * @param b the blue value
         * @return a Color object
         */
        Color(int r, int g, int b) {
            red = r;
            green = g;
            blue = b;
        }

        /**
         * Default constructor
         * @return a Color object
         */
        Color() = default;

        /**
         * Returns the red value
         * @return the red value
         */
        int getRed() {
            return red;
        }

        /**
         * Returns the blue value
         * @return the blue value
         */
        int getBlue() {
            return blue;
        }

        /**
         * Returns the green value
         * @return the green value
         */
        int getGreen() {
            return green;
        }
};
