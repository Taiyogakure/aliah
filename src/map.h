#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#define TILE_SIZE 40

extern char gameMap[MAP_HEIGHT][MAP_WIDTH + 1];

void loadMap(const char *filePath);
void renderMap(SDL_Renderer *renderer);

#endif
