#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    int x;  // Player x-coordinate in tile units
    int y;  // Player y-coordinate in tile units
} Player;

void initPlayer(Player *player);
void handlePlayerInput(Player *player, const char gameMap[5][11]);
void renderPlayer(SDL_Renderer *renderer, const Player *player);

#endif
