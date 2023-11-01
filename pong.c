#include <stdio.h>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

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

    SDL_Event event;

    while ( 1 )
    {
        if ( SDL_PollEvent( &event ) )
        {
            if ( SDL_QUIT == event.type )
            { break; }

            if ( SDL_KEYDOWN == event.type )
            {	//down movement
                if ( SDLK_j == event.key.keysym.sym )
                { printf( "J is pressed - Move down\n");}
                if ( SDLK_s == event.key.keysym.sym )
                { printf("S is pressed - Move down\n"); }
                if ( SDLK_DOWN == event.key.keysym.sym )
                { printf("down key is pressed - Move down\n"); }

		//up movement
		
                if ( SDLK_k == event.key.keysym.sym )
                { printf( "K is pressed - Move up\n");}
                if ( SDLK_w == event.key.keysym.sym )
                { printf("W is pressed - Move up\n"); }
                if ( SDLK_UP == event.key.keysym.sym )
                { printf("up key is pressed - Move up\n"); }
            }
            else if ( SDL_KEYUP == event.type )
            {
		//down movement
                if ( SDLK_j == event.key.keysym.sym )
                { printf("J is not pressed - Stop moving down\n"); }
                if ( SDLK_s == event.key.keysym.sym )
                { printf("S is not pressed - Stop moving down\n"); }
                if ( SDLK_DOWN == event.key.keysym.sym )
                { printf("down key is not pressed - Stop moving down\n"); }

		//up movement
		//

                if ( SDLK_k == event.key.keysym.sym )
                { printf("K is not pressed - Stop moving down\n"); }
                if ( SDLK_w == event.key.keysym.sym )
                { printf("W is not pressed - Stop moving down\n"); }
                if ( SDLK_UP == event.key.keysym.sym )
                { printf("up key is not pressed - Stop moving down\n"); }
            }
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit( );

    return EXIT_SUCCESS;
}
