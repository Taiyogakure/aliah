#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 80
#define TILE_SIZE 8

// The binary map: each element is one byte (tile index)
extern unsigned char gameMap[MAP_HEIGHT][MAP_WIDTH];

extern SDL_Texture *tilesetTexture;

int initTileset(SDL_Renderer *renderer, const char *tilesetPath);

int loadMap(const char *filePath);
void renderMap(SDL_Renderer *renderer);

#endif
