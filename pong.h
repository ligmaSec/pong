#pragma once


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Structs
typedef struct {
    int pos_y;
} tPlayer;

// Constants
const int WIDTH = 800, HEIGHT = 600;
const int FPS = 144, FRAME_DELAY = 1000/FPS;

// Framerate variables
Uint32 frame_start;
int frame_time;

// Global variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Rect rect_player1;
SDL_Rect rect_player2;
bool playing = false;

// Prototypes
int render_setup();
void event_loop();
void game_loop();
void render_game_state(tPlayer *player1, tPlayer *player2);
void render_board();

