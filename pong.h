#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;
const int FPS = 30, FRAME_DELAY = 1000/FPS;

Uint32 frame_start;
int frame_time;

SDL_Window *window;

bool playing = false;

// Prototypes
int setup();
void event_loop();
void game_loop();