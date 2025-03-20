#include "default_player_controller.hpp"

SDL_Scancode DefaultPlayerController::getJumpButton() {
    return jumpButton;
}

SDL_Scancode DefaultPlayerController::getMoveLeftButton() {
    return moveLeftButton;
}

SDL_Scancode DefaultPlayerController::getMoveRightButton() {
    return moveRightButton;
}

void DefaultPlayerController::setJumpButton(SDL_Scancode button) {
    jumpButton = button;
}

void DefaultPlayerController::setMoveRightButton(SDL_Scancode button) {
    moveRightButton = button;
}

void DefaultPlayerController::setMoveLeftButton(SDL_Scancode button) {
    moveLeftButton = button;
}

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