#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 80
#define TILE_SIZE 8

extern char gameMap[MAP_HEIGHT][MAP_WIDTH + 1];

void loadMap(const char *filePath);
void renderMap(SDL_Renderer *renderer);

#endif
