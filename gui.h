#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500

SDL_Window* window;
SDL_Renderer* rend;

int setup(){
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "GAME", // creates a window
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(window, -1, render_flags);

    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
}