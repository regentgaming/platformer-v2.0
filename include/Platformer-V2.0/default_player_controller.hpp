#ifndef DEFAULT_PLAYER_CONTROLLER_H
#define DEFAULT_PLAYER_CONTROLLER_H

#include "SDL3/SDL_scancode.h"
#include "default_player.hpp"

#define BUTTON(x) SDL_SCANCODE_##x

class DefaultPlayerController {
    private:
        SDL_Scancode jumpButton = BUTTON(W);
        SDL_Scancode moveLeftButton = BUTTON(A);
        SDL_Scancode moveRightButton = BUTTON(D);
    public:
        SDL_Scancode getJumpButton();
        SDL_Scancode getMoveLeftButton();
        SDL_Scancode getMoveRightButton();
        void setJumpButton(SDL_Scancode button);
        void setMoveRightButton(SDL_Scancode button);
        void setMoveLeftButton(SDL_Scancode button);
        virtual void checkMovement(const bool* keys, DefaultPlayer* player);
};


#endif