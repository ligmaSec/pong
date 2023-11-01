#include "pong.h"

int main(int argc, char *argv[]){
    setup();
    game_loop();
    return EXIT_SUCCESS;
}

int setup(){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL){
        printf("Could not create window: %s ", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Draw middle line
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i=(WIDTH/2)-1; i<(WIDTH/2)+1; i++){
        for (int j=0; j<HEIGHT; j++){
            if (j%18 < 9){
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
    SDL_RenderPresent(renderer);
    return 0;
}

void game_loop(){
    tPlayer player1;
    player1.pos_y = HEIGHT/2;
    tPlayer player2;
    player2.pos_y = HEIGHT/2;

    playing = true;
    while (playing){
        // Stores the number of ticks at the start of the loop
        frame_start = SDL_GetTicks();

        event_loop();

        render_game_state(&player1, &player2);

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        // Down movement
        if (keystates[SDL_SCANCODE_J]){
            printf("J is pressed - Move down\n");
            player1.pos_y += 5;
        }
        else if (keystates[SDL_SCANCODE_S])
        { printf("S is pressed - Move down\n"); }
        else if (keystates[SDL_SCANCODE_DOWN])
        { printf("down key is pressed - Move down\n");}

        // Up movement
        if (keystates[SDL_SCANCODE_K])
        { printf( "K is pressed - Move up\n");}
        else if (keystates[SDL_SCANCODE_W])
        { printf("W is pressed - Move up\n"); }
        else if (keystates[SDL_SCANCODE_UP])
        { printf("up key is pressed - Move up\n"); }

        // This measures how long this iteration of the loop took
        frame_time = SDL_GetTicks() - frame_start;
        // This keeps us from displaying more frames than 30/Second
        if (FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void event_loop(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            playing = false;
        }
    }
}

void render_game_state(tPlayer *player1, tPlayer *player2){
    rect1.x = 30;
    rect1.y = player1->pos_y+20;
    rect1.w = 2;
    rect1.h = 40;
    SDL_RenderDrawRect(renderer, &rect1);
    SDL_RenderPresent(renderer);
}