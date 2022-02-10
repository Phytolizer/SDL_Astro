//
// Created by William Aey on 2/1/2022.
//

#include "Astro/Check_collision.h"

bool collision::checkCollision(std::vector<astroidMovment> *movementSlope,
                               player *pla) {

    /*
     * checks for collision between player and astroids
     * */
    bool returnValue  {false};
    for (size_t i{0}; i < movementSlope->size(); i++) {

        SDL_bool collision = SDL_HasIntersection(
                movementSlope->at(i).instance->getDestRect(), pla->getDestRect());
        if (collision == true) {
            returnValue = true;
            movementSlope->erase(movementSlope->begin() + i);
            i--;
        }
    }
    return returnValue;
}

void collision::checkCollision(std::vector<astroidMovment> *movementSlope,
                               std::vector<projectile *> *projectiles) {

    /*
     * checks for collision between astroids and projectiles
     * */
    for (size_t i{0}; i < movementSlope->size(); i++) {
        for (size_t j{0}; j < projectiles->size(); j++) {
            SDL_bool collision =
                    SDL_HasIntersection(movementSlope->at(i).instance->getDestRect(),
                                        projectiles->at(j)->getDestRect());
            if (collision == true) {
                movementSlope->erase(movementSlope->begin() + i);
                projectiles->erase(projectiles->begin() + j);
                i--;
            }
    }
  }

}

