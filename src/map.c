#include "map.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

unsigned char gameMap[MAP_HEIGHT][MAP_WIDTH];

SDL_Texture *tilesetTexture = NULL;

int initTileset(SDL_Renderer *renderer, const char *tilesetPath) {
    SDL_Surface *surface = IMG_Load(tilesetPath);
    if (!surface) {
        printf("Error loading tileset '%s': %s\n", tilesetPath, IMG_GetError());
        return 0;
    }
    tilesetTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!tilesetTexture) {
        printf("Error creating texture from surface: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

int loadMap(const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (!file) {
        printf("Error: Unable to open map file '%s'\n", filePath);
        return 0;
    }
    size_t bytesRead = fread(gameMap, sizeof(unsigned char), MAP_WIDTH * MAP_HEIGHT, file);
    fclose(file);
    if (bytesRead != MAP_WIDTH * MAP_HEIGHT) {
        printf("Error: Map file '%s' size mismatch. Expected %d bytes, got %zu bytes\n", filePath, MAP_WIDTH * MAP_HEIGHT, bytesRead);
        return 0;
    }
    return 1;
}

void renderMap(SDL_Renderer *renderer) {
    SDL_Rect srcRect, dstRect;
    srcRect.w = TILE_SIZE;
    srcRect.h = TILE_SIZE;
    dstRect.w = TILE_SIZE;
    dstRect.h = TILE_SIZE;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            unsigned char tileIndex = gameMap[y][x];
            srcRect.x = tileIndex * TILE_SIZE;
            srcRect.y = 0;
            dstRect.x = x * TILE_SIZE;
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &dstRect);
        }
    }
}
