#include <Platformer-V2.0/default_player_controller.hpp>

//return jump button
SDL_Scancode DefaultPlayerController::getJumpButton() {
    return jumpButton;
}

//return move left button
SDL_Scancode DefaultPlayerController::getMoveLeftButton() {
    return moveLeftButton;
}

//return move right button
SDL_Scancode DefaultPlayerController::getMoveRightButton() {
    return moveRightButton;
}

//set jump button
void DefaultPlayerController::setJumpButton(SDL_Scancode button) {
    jumpButton = button;
}

//set move right button
void DefaultPlayerController::setMoveRightButton(SDL_Scancode button) {
    moveRightButton = button;
}

//set move left button
void DefaultPlayerController::setMoveLeftButton(SDL_Scancode button) {
    moveLeftButton = button;
}

//apply input
void DefaultPlayerController::checkMovement(const bool* keys, DefaultPlayer* player) {
    if (keys[getJumpButton()]) {
        player->jump();
    }
    if (keys[getMoveLeftButton()]) {
        player->move(-1);
    } else if (keys[getMoveRightButton()]) {
        player->move(1);
    } else {
        player->move(0);
    }
}