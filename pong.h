#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <pthread.h> 
#include <unistd.h>
#include <math.h>

// Constants
const int WIDTH = 800, HEIGHT = 600;
const int FPS = 144, FRAME_DELAY = 1000/FPS;
const int BALL_RADIUS = 4;
const float MAX_BOUNCE_ANGLE = 5*M_PI/12;
const int PLAYER_MOVEMENT_STEP = 3;

// Structs
typedef struct {
    int pos_y;
} tPlayer;
typedef struct {
    float pos_y;
    float pos_x;
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
SDL_Surface* text;
bool playing = true;
bool is_server = true;
float ball_speed = 3;
float ball_direction = 2*M_PI;
int scores[2] = {0, 0};

// Prototypes
int render_setup();
void *net_routine();
void event_loop();
void game_loop();
void draw_ball();
void move_ball();
void check_collision();
void update_ball_direction(tPlayer *player, bool left_player);
void render_game_state();
void render_board();
void move_player1(int step);
void reset_ball(bool ball_direction_right);
