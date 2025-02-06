#include "player.h"
#include "map.h"

#define TILE_SIZE 40

void initPlayer(Player *player) {
    player->x = 1;
    player->y = 1;
}

void handlePlayerInput(Player *player, const char gameMap[5][11]) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int newX = player->x, newY = player->y;

    if (state[SDL_SCANCODE_UP]) {
        newY -= 1;
    } 
    if (state[SDL_SCANCODE_DOWN]) {
        newY += 1;
    } 
    if (state[SDL_SCANCODE_LEFT]) {
        newX -= 1;
    } 
    if (state[SDL_SCANCODE_RIGHT]) {
        newX += 1;
    }

    // Boundary and wall checks
    if (newX >= 0 && newX < MAP_WIDTH &&
        newY >= 0 && newY < MAP_HEIGHT &&
        gameMap[newY][newX] != '#') {
        player->x = newX;
        player->y = newY;
    }
}

void renderPlayer(SDL_Renderer *renderer, const Player *player) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect rect = {player->x * TILE_SIZE, player->y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}
