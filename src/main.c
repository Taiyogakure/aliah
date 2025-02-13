#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include "map.h"
#include "player.h"

Player player;

void main_loop(void *arg) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            emscripten_cancel_main_loop();
            break;
        }
    }

    SDL_Renderer *renderer = (SDL_Renderer *)arg;

    handlePlayerInput(&player, gameMap);

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render the map and player
    renderMap(renderer);
    renderPlayer(renderer, &player);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Binary Map with Tileset", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, 
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize the tileset texture.
    if (!initTileset(renderer, "assets/tileset.png")) {
        printf("Failed to initialize tileset.\n");
        return 1;
    }
    // Load the binary map (map.bin must be 6400 bytes).
    if (!loadMap("assets/maps/map.bin")) {
        printf("Failed to load map.\n");
        return 1;
    }

    emscripten_set_main_loop_arg(main_loop, renderer, 0, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
