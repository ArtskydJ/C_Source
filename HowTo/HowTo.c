//Re-usable file
//Written by Joseph Dykstra
//Compiled with:
//gcc -std=c99 -o HowTo.exe HowTo.c -lmingw32 -lSDLmain -lSDL -mwindows -lSDL_ttf

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "including/EasySDL.h"
#define SCR_WIDTH	640
#define SCR_HEIGHT	480
#define SCR_BPP		32

SDL_Surface *screen=NULL;
TTF_Font *font=NULL;
SDL_Rect drawrect;

int main( int argc, char* args[] )
	{
	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_SWSURFACE); //MUST SET SCREEN TO THIS VALUE!!!
	if( screen == NULL )
		return 1;    
    
    //Initialize SDL_ttf
	if( TTF_Init() == -1 )
		return 2;
	
	font = TTF_OpenFont( "lazy.ttf", 28 );
	if( font == NULL )
		return 3;
	
	//EXAMPLE START
	EZ_set_rect(&drawrect,100,100,20,20);
	SDL_FillRect(screen, &drawrect, 0x0000FF);
	SDL_Flip(screen);
	//SDL_Delay(100);
	
	EZ_apply_rect(screen, EZ_new_rect(100,200,20,20), 0x0000FF);
	SDL_Flip(screen);
	//SDL_Delay(100);
	
	EZ_apply_rect(screen, EZ_new_rect(200,200,20,20), EZ_new_Uint32(000,000,255));
	SDL_Flip(screen);
	//SDL_Delay(100);
	
	EZ_apply_text(screen,"hello",    font,EZ_new_rect(10,0,0,0), EZ_new_color(128,128,128));
	EZ_apply_text(screen,"what's up?",font,EZ_new_rect(10,50,0,0),EZ_Uint32_to_SDL(0x00FF00));
	SDL_Flip(screen);
	
	EZ_waitForExit();
	//EXAMPLE END
	
	SDL_Quit();//Quit SDL
    
	return 0;    
	}
