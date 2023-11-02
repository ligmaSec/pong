#include "pong.h"

// TODO: hardcore mode
int main(int argc, char *argv[]){
	render_setup();
    net_setup(true);

    pthread_t receive_thread_id; 
    pthread_create(&receive_thread_id, NULL, receive_routine, NULL);
    // pthread_join(receive_thread_id, NULL);

    game_loop();
    return EXIT_SUCCESS;
}

void *receive_routine(void *arg){
    while (playing){
        player2.pos_y = recv_position();
        printf("Opp position: %d\n", player2.pos_y);
        send_position(player1.pos_y);
    }
}

int render_setup(){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL){
        printf("Could not create window: %s ", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    render_board();

    rect_player1.x = 30;
    rect_player2.x = WIDTH-34;
    rect_player1.w= 4;
    rect_player2.w = 4;
    rect_player1.h = 50;
    rect_player2.h = 50;

    return 0;
}

void game_loop(){
    player1.pos_y = HEIGHT/2;
    player2.pos_y = HEIGHT/2;

    playing = true;
    while (playing){
        // Stores the number of ticks at the start of the loop
        frame_start = SDL_GetTicks();

        event_loop();
        render_game_state();

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        // Down movement
        if (
            keystates[SDL_SCANCODE_J] ||
            keystates[SDL_SCANCODE_S] ||
            keystates[SDL_SCANCODE_DOWN]
        ){
            move_player1(5);
        }

        // Up movement
        if (
            keystates[SDL_SCANCODE_K] ||
            keystates[SDL_SCANCODE_W] ||
            keystates[SDL_SCANCODE_UP]
        ){
            move_player1(-5);
        }

	    // printf("player1 position : %d\n", player1.pos_y);

        // This measures how long this iteration of the loop took
        frame_time = SDL_GetTicks() - frame_start;
        // This keeps us from displaying more frames than 144/Second
        if (FRAME_DELAY > frame_time){
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
            break;
        } else if (event.type == SDL_MOUSEWHEEL){
            if (event.wheel.y > 0){ // scroll up
                move_player1(-15);
            } else if (event.wheel.y < 0){ // scroll down
                move_player1(15);
            }
        }
    }
}

void move_player1(int step){
    player1.pos_y += step;
    if (player1.pos_y <= 0){
        player1.pos_y = HEIGHT;
    } else if (player1.pos_y >= HEIGHT){
        player1.pos_y = 0;
    }
}

void render_game_state(){
    render_board();
    rect_player1.y = player1.pos_y-25;
    rect_player2.y = player2.pos_y-25;
    SDL_RenderFillRect(renderer, &rect_player1);
    SDL_RenderFillRect(renderer, &rect_player2);
    SDL_RenderPresent(renderer);
}

void render_board(){
    // Black background
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
}
