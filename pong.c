#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;
const int FPS = 30, FRAME_DELAY = 1000/FPS;

Uint32 frame_start;
int frame_time;

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );

    if ( NULL == window )
    {
        printf("Could not create window: %s ", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    SDL_RenderPresent( renderer );

    bool playing = true;
    

    while ( playing )
    {
        // Stores the number of ticks at the start of the loop
        frame_start = SDL_GetTicks();

        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if (event.type == SDL_QUIT)
            { break; }

            // if ( SDL_KEYDOWN == event.type )
            // {	
                // down movement
            // }
            // else if ( SDL_KEYUP == event.type )
            // {
		    //     // down movement
            //     if ( SDLK_j == event.key.keysym.sym )
            //     { printf("J is not pressed - Stop moving down\n"); }
            //     else if ( SDLK_s == event.key.keysym.sym )
            //     { printf("S is not pressed - Stop moving down\n"); }
            //     else if ( SDLK_DOWN == event.key.keysym.sym )
            //     { printf("down key is not pressed - Stop moving down\n"); }

		    //     // up movement
            //     if ( SDLK_k == event.key.keysym.sym )
            //     { printf("K is not pressed - Stop moving down\n"); }
            //     else if ( SDLK_w == event.key.keysym.sym )
            //     { printf("W is not pressed - Stop moving down\n"); }
            //     else if ( SDLK_UP == event.key.keysym.sym )
            //     { printf("up key is not pressed - Stop moving down\n"); }
            // }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if (keystates[SDL_SCANCODE_J])
        { printf("J is pressed - Move down\n");}
        else if (keystates[SDL_SCANCODE_S])
        { printf("S is pressed - Move down\n"); }
        else if (keystates[SDL_SCANCODE_DOWN])
        { printf("down key is pressed - Move down\n");}

        // up movement
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

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
