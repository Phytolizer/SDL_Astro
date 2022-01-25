//
// Created by William Aey on 1/25/2022.
//

#pragma once
#define SDL_ASTRO_GAME_H
#include "SDL_image.h"
#include "SDL.h"
#include "player.h"
#include <iostream>
class Game {
public:
    Game();

    virtual ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running();

private:
    int counter = 0;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

