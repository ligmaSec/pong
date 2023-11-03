#include "pong.h"

// TODO: hardcore mode
int main(int argc, char *argv[]){
    int invalid_args = true;
    char* host = "127.0.0.1";
    int opt;
    while((opt = getopt(argc, argv, "c:")) != -1){  
        switch(opt){  
            case 'c':
                printf("Client mode\n");
                invalid_args = false;
                is_server = false;
                host = optarg;
                break;
        }
    }

    if (argc != 1 && invalid_args){
        exit(1);
    }

	render_setup();
    net_setup(is_server, host);

    pthread_t receive_thread_id; 
    pthread_create(&receive_thread_id, NULL, net_routine, NULL);
    // pthread_join(receive_thread_id, NULL);

    game_loop();
    return EXIT_SUCCESS;
}

void *net_routine(){
    if (is_server){
        while (playing){
            player2.pos_y = recv_position();
            printf("Opp position: %d\n", player2.pos_y);
            send_position(player1.pos_y);
        }
    } else {
        while (playing){
            send_position(player1.pos_y);
            player2.pos_y = recv_position();
            printf("Opp position: %d\n", player2.pos_y);
        }
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

    // Verticaly center players
    player1.pos_y = HEIGHT/2;
    player2.pos_y = HEIGHT/2;

    rect_player1.x = 30;
    rect_player2.x = WIDTH-34;
    rect_player1.w= 4;
    rect_player2.w = 4;
    rect_player1.h = 50;
    rect_player2.h = 50;

    // Center ball
    ball.pos_y = HEIGHT/2;
    ball.pos_x = WIDTH/2;
    ball.radius = 3;

    return 0;
}

void game_loop(){
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

        // ball.pos_x = player1.pos_y;

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
    draw_ball();
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

void draw_ball(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int w = 0; w < ball.radius * 2; w++){
        for (int h = 0; h < ball.radius * 2; h++){
            int dx = ball.radius - w; // horizontal offset
            int dy = ball.radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (ball.radius * ball.radius)){
                SDL_RenderDrawPoint(renderer, ball.pos_x + dx, ball.pos_y + dy);
            }
        }
    }
}