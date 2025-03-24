#include <iostream>
#include <SDL3/SDL.h>
#include <Platformer-V2.0/platformer_v2-0.hpp>

/* 
* helper function for wrapping things around the screen
* will probably be relocated soon
*/
void screenWrap(DynamicObject& dynamic, const int w, const int h) {
    BoundingBox& hitbox = dynamic.getHitbox();
    if (hitbox.LR.getX() < 0) {
        hitbox.moveTo(w, hitbox.UL.getY());
    } else if (hitbox.UL.getX() > w) {
        hitbox.moveTo(0-hitbox.w, hitbox.UL.getY());
    }

    if (hitbox.UL.getY() > h) {
        hitbox.moveTo(hitbox.UL.getX(), 0-hitbox.h);
    }
}


//test for inheriting from defaultplayer and defaultcontroller
class myPlayer : public DefaultPlayer {
    int dashSpeed;
    bool canDash;
    public:
        myPlayer(Color color_p, BoundingBox hitbox_p, Physics& physics, int dashSpeed_p) : DefaultPlayer(color_p, hitbox_p, physics){
            dashSpeed = dashSpeed_p;
        };

        void dash(int dir) {
            if (!canDash) {
                return;
            } else if (dir > 0) {
                canDash = false;
                setVelocity(dashSpeed, getVelocity().getY());
            } else if (dir < 0) {
                canDash = false;
                setVelocity(-1 * dashSpeed, getVelocity().getY());
            }
        }

        void update(Physics& physics, double deltaTime) {
            DefaultPlayer::update(physics, deltaTime);

            if (isOnGround()) {
                canDash = true;
            }

        }
};

class myController : public DefaultPlayerController {
    private:
        SDL_Scancode dashButton = BUTTON(LSHIFT);
    public:
        SDL_Scancode getDashButton() {
            return dashButton;
        }

        void setDashButton(SDL_Scancode button) {
            dashButton = button;
        }

        void checkMovement(const bool* keys, DefaultPlayer* player) {
            DefaultPlayerController::checkMovement(keys, player);
            if (keys[getDashButton()]) {
                if (myPlayer* myP = dynamic_cast<myPlayer*>(player)) {
                    if (keys[getMoveLeftButton()]){
                        myP->dash(-1);
                    } else if (keys[getMoveRightButton()]) {
                        myP->dash(1);
                    }
                }
                
            }
        }
};





int main(int argc, char *argv[]) {
    const int WIDTH = 800, HEIGHT = 600;
    SDL_Init(SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow("Game", WIDTH, HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY  | SDL_WINDOW_RESIZABLE);

    // SDL_SetWindowSurfaceVSync(window,1);
    
    SDL_Event windowEvent;

    if (!window) {
        std::cout << "Failed to create window\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,NULL);
    SDL_SetRenderVSync(renderer, 1);
    if(!renderer)
    {
        std::cout << "Failed to create renderer\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    bool keep_window_open = true;
    Physics physics = Physics();
    Object test = Object(Color(0, 255, 0), BoundingBox(-50, 500, 100, 900), physics, false);
    Object test2 = Object(Color(0, 0, 255), BoundingBox(100, 450, 25, 100), physics, true);
    myPlayer player = myPlayer(Color(255, 0, 0), BoundingBox(300, 100, 50, 50), physics, 450);
    myController controller = myController();
    controller.setJumpButton(BUTTON(SPACE));
    controller.setMoveLeftButton(BUTTON(LEFT));
    controller.setMoveRightButton(BUTTON(RIGHT));
    DynamicObject test3 = DynamicObject(Color(0, 0, 255), BoundingBox(375, 50, 50, 50), physics);
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    while (keep_window_open) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() );
        double fps = 1.0/deltaTime;
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        for (ICollidable* object : physics.getStatics()) {
            object->draw(renderer);
        }
        for (ICollidable* object : physics.getDynamics()) {
            DynamicObject& dyn = dynamic_cast<DynamicObject&>(*object);
            dyn.update(physics, deltaTime);
            screenWrap(dyn, WIDTH, HEIGHT);
            dyn.draw(renderer);
        }
        SDL_RenderPresent(renderer);
        const bool* keys = SDL_GetKeyboardState(NULL);
        controller.checkMovement(keys, &player);
        while (SDL_PollEvent(&windowEvent) > 0) {
            switch(windowEvent.type) {
                case SDL_EVENT_QUIT:
                keep_window_open = false;
                    break;
            }
        }
    }

    return EXIT_SUCCESS;

}