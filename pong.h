#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <pthread.h> 

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
tPlayer player1;
tPlayer player2;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Rect rect_player1;
SDL_Rect rect_player2;
bool playing = false;

// Prototypes
int render_setup();
void event_loop();
void game_loop();
void render_game_state();
void render_board();
void move_player1(int step);
void *receive_routine();