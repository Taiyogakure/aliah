#include <SDL2/SDL.h>
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

    SDL_Window *window = SDL_CreateWindow("Map Loader with Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    loadMap("/assets/maps/map1.txt");
    initPlayer(&player);

    emscripten_set_main_loop_arg(main_loop, renderer, 0, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
