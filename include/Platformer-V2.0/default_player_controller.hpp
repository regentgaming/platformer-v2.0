#ifndef DEFAULT_PLAYER_CONTROLLER_H
#define DEFAULT_PLAYER_CONTROLLER_H

#include <SDL3/SDL_scancode.h>
#include <Platformer-V2.0/default_player.hpp>

/**
 * Macro function to generate SDL scancodes for buttons
 * @param x the button to generate the code for
 */
#define BUTTON(x) SDL_SCANCODE_##x

/**
 * Represents the object that specifies the controls to interact with the player
 * 
 * Can be inherited from to add new controls
 */
class DefaultPlayerController {
    private:

        /**  
         * The button to trigger the jump action
         * 
         * The default is W
         */
        SDL_Scancode jumpButton = BUTTON(W);

        /**  
         * The button to trigger moving left
         * 
         * The default is A
         */
        SDL_Scancode moveLeftButton = BUTTON(A);

        /**  
         * The button to trigger moving right
         * 
         * The default is D
         */
        SDL_Scancode moveRightButton = BUTTON(D);
    public:

        /**
         * Returns the jump button
         * @return the SDL_Scancode representing the jump button
         */
        SDL_Scancode getJumpButton();

        /**
         * Returns the move left button
         * @return the SDL_Scancode representing the move left button
         */
        SDL_Scancode getMoveLeftButton();

        /**
         * Returns the move right button
         * @return the SDL_Scancode representing the move right button
         */
        SDL_Scancode getMoveRightButton();

        /**
         * Sets the jump button
         * @param button the SDL_Scancode representing the jump button
         */
        void setJumpButton(SDL_Scancode button);

        /**
         * Sets the move right button
         * @param button the SDL_Scancode representing the move right button
         */
        void setMoveRightButton(SDL_Scancode button);

        /**
         * Sets the move left button
         * @param button the SDL_Scancode representing the move left button
         */
        void setMoveLeftButton(SDL_Scancode button);

        /**
         * Function that applies the input to the player
         * @param keys an array representing what keys are pressed down (gathered from SDL)
         * @param player the player to apply the input to
         */
        virtual void checkMovement(const bool* keys, DefaultPlayer* player);
};


#endif