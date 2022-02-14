//
// Created by TANK1_41 on 1/25/2022.
//

#include "Astro/player.h"
#include "Astro/game.h"
#include "Astro/textureManager.h"

player::player(Game *game, int x, int y) : game(game) {
    xpos = x;
    ypos = y;
    playertex = game->textures.loadTexture("assets/player.png");
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 64;
    srcRect.h = 64;
    destRect.w = 64;
    destRect.h = 64;
    spriteCenter = {28, 0};
}

player::~player() {}

void player::update() {
    // gets mouse state and sets the angle that the spite should be angled at
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    spriteAngle = atan2(ypos - mouseY, xpos - mouseX);
    spriteAngle = (spriteAngle * 180.f) / 3.141f;
    spriteAngle -= 90;

    /*
 * spawns new projectiles when left mouse is pressed
 * */
    static int spawnRate{60};
    if (spawnRate >= 60) {
        if (SDL_GetMouseState(&mouseX, &mouseY) == 1) {
            projectile *shoot = new projectile(game, destRect, spriteAngle, mouseX, mouseY);
            game->addProjectile(shoot);
            spawnRate = 0;
        }
    } else {
        spawnRate++;
    }
    /*
     * checks for keyboard input and applies directional movement
     * */
    int numKeys;
    const Uint8 *keys = SDL_GetKeyboardState(&numKeys);
    if (keys[SDL_SCANCODE_W]) {
        yVelocity = -1;
    } else if (keys[SDL_SCANCODE_S]) {
        yVelocity = 1;
    } else {
        yVelocity = 0;
    }

    if (keys[SDL_SCANCODE_A]) {
        xVelocity = -1;
    } else if (keys[SDL_SCANCODE_D]) {
        xVelocity = 1;
    } else {
        xVelocity = 0;
    }
    int w, h{0};
    SDL_GetWindowSize(game->getWindow(), &w, &h);
    if (yVelocity == 1 && destRect.y < h - 25) {
        ypos += 4;

    } else if (yVelocity == -1 && destRect.y > 25) {
        ypos -= 4;
    }


    if (xVelocity == 1 && destRect.x < w - 50) {
        xpos += 4;
    } else if (xVelocity == -1 && destRect.x > 0) {
        xpos -= 4;
    }
    // sets active position
    destRect.x = xpos;
    destRect.y = ypos;
}

void player::render() {
    SDL_RenderCopyEx(game->renderer, playertex, &srcRect, &destRect, spriteAngle,
                     &spriteCenter, SDL_FLIP_NONE);
}

SDL_Rect *player::getDestRect() {
    SDL_Rect *temp = &destRect;
    return temp;
}
