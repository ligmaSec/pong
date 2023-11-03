#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <pthread.h> 
#include <unistd.h> 

// Constants
const int WIDTH = 800, HEIGHT = 600;
const int FPS = 144, FRAME_DELAY = 1000/FPS;

// Structs
typedef struct {
    int pos_y;
} tPlayer;
typedef struct {
    float pos_y;
    float pos_x;
    int radius;
} tBall;

// Framerate variables
Uint32 frame_start;
int frame_time;

// Global variables
tPlayer player1;
tPlayer player2;
tBall ball;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Rect rect_player1;
SDL_Rect rect_player2;
bool playing = true;
bool is_server = true;

// Prototypes
int render_setup();
void event_loop();
void game_loop();
void draw_ball();
void render_game_state();
void render_board();
void move_player1(int step);
void *net_routine();
