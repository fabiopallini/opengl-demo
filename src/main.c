#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "screen.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void handleKeys( unsigned char key, int x, int y );
void update();
void close();

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		gWindow = SDL_CreateWindow("OpenGL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gContext = SDL_GL_CreateContext(gWindow);
			if( gContext == NULL )
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				if(SDL_GL_SetSwapInterval( 1 ) < 0)
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				//Initialize OpenGL
				if(!initGL(SCREEN_WIDTH, SCREEN_HEIGHT)){
					printf( "Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

void handleKeys(unsigned char key, int x, int y)
{
	if( key == 'q' ){
	}
}

void update(){}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if(!init())
		printf( "Failed to initialize!\n" );
	else
	{
		bool quit = false;
		SDL_Event e;
		SDL_StartTextInput();
		while(!quit)
		{
			while(SDL_PollEvent( &e ) != 0)
			{
				if( e.type == SDL_QUIT )
					quit = true;
				else if(e.type == SDL_TEXTINPUT)
				{
					if(e.text.text[0] == 'q')
						quit = true;
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);
					handleKeys(e.text.text[ 0 ], x, y);
				}
			}
			render(SCREEN_WIDTH, SCREEN_HEIGHT);
			SDL_GL_SwapWindow(gWindow);
		}
		SDL_StopTextInput();
	}
	close();
	return 0;
}