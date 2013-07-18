//Re-usable file
//Written by Joseph Dykstra
#include "SDL/SDL.h"
#define SCR_WIDTH	640
#define SCR_HEIGHT	480
#define SCR_BPP		32

SDL_Surface *screen=NULL;
SDL_Rect drawrect;

int main( int argc, char* args[] )
	{
	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_SWSURFACE); //MUST SET SCREEN TO THIS VALUE!!!
	
	//EXAMPLE START
	drawrect.h = 100;
	drawrect.w = 200;
	drawrect.x = 200;
	drawrect.y = 100;
	SDL_FillRect(screen , &drawrect , SDL_MapRGB(screen->format,000,000,255));
	SDL_Flip(screen);
	SDL_Delay(2500);
	//EXAMPLE END
	
	SDL_Quit();//Quit SDL
    
	return 0;    
	}

