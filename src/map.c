#include "map.h"
#include <stdio.h>

char gameMap[MAP_HEIGHT][MAP_WIDTH + 1];

void loadMap(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: Unable to load map from %s\n", filePath);
        return;
    }

    for (int i = 0; i < MAP_HEIGHT; i++) {
        if (fgets(gameMap[i], MAP_WIDTH + 2, file) == NULL) {  // +2 for newline and null terminator
            break;
        }
    }

    fclose(file);
}

void renderMap(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (gameMap[y][x] == '#') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else if (gameMap[y][x] == 'E') {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else if (gameMap[y][x] == 'O') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            } else {
                continue;
            }

            SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
