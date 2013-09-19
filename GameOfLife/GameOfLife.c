//////////////////////////////
//    Name: Game Of Life	//
// 	Author: Joseph Dykstra	//
// Written: 2013-01-15		//
//  Ported: 2013-09-11		//
//////////////////////////////

#define WIDTH   	64		//blocks horizontally
#define HEIGHT  	48		//blocks vertically
#define SIZE		10		//pixels each block
#define SCR_WIDTH	(WIDTH*SIZE)
#define SCR_HEIGHT	(HEIGHT*SIZE)
#define SCR_BPP		32
#define COL_OFF		0x222222
#define COL_ON		0x9999FF
#define RNDM		0
#define RSET		1
#define MODE_MENU	false 	// true=menu, false=skip
#define DELETE_CELL	2
#define CREATE_CELL	3


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "SDL/SDL.h"
#include "including\EasySDL.h"
char area[WIDTH+2][HEIGHT+2];
#include "Pieces.c"
SDL_Surface *screen=NULL;
SDL_Rect *drawRect;


int set(void)
	{
	int ret=SDL_Init(SDL_INIT_VIDEO);
	if (ret==0)
		{
		//Graphics
		screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_SWSURFACE);
		SDL_Flip(screen);
		atexit(SDL_Quit);
		}
	return ret;
	}


void initArea(bool INrsetRndm)
	{
	for (int i=0; i<HEIGHT+2; i++)
		{
		for (int j=0; j<WIDTH+2; j++)
			{
			if		(INrsetRndm==RSET)		//RESET
				area[j][i]=0;
			else if (INrsetRndm==RNDM)		//RANDOM
				area[j][i]=rand()%2;
			}
		}
	}

	
void clearScreen()
	{
	EZ_apply_rect(screen,EZ_new_rect(0,0,SCR_WIDTH,SCR_HEIGHT),COL_OFF);
	}


void draw(int INb)
	{
	for (int i=1; i<HEIGHT+1; i++)
		{
		for (int j=1; j<WIDTH+1; j++)
			{
			if (area[j][i])
				EZ_apply_rect(screen,EZ_new_rect((j-1)*INb,(i-1)*INb,INb,INb),COL_ON);
			else
				EZ_apply_rect(screen,EZ_new_rect((j-1)*INb,(i-1)*INb,INb,INb),COL_OFF);
			}
		}
	SDL_Flip(screen);
	}


void stepForward()
	{
	int neighbors;
	for (int i=0; i<HEIGHT+2; i++)	//Clear L & R Edges
		{
		area[0][i]=0;
		area[WIDTH+1][i]=0;
		}
	for (int j=0; j<WIDTH+2; j++)	//Clear T & B Edges
		{
		area[j][0]=0;
		area[j][HEIGHT+1]=0;
		}
	
	for (int i=1; i<HEIGHT+1; i++)
		{
		for (int j=1; j<WIDTH+1; j++)
			{
			neighbors=0;
			for (int k=-1; k<=1; k++)
				for (int l=-1; l<=1; l++)	//if ((not self) and (alive now&later) or (alive now,dead later))
					if ( (k!=0 || l!=0) && ((area[j+l][i+k]==1) || (area[j+l][i+k]==2)))	
						neighbors++;
			if (area[j][i]) //LIVE CELL
				{
				if (neighbors<2)  area[j][i]=DELETE_CELL; //Under population
				if (neighbors>3)  area[j][i]=DELETE_CELL; //Over crowding
				}
			else            //DEAD CELL
				{
				if (neighbors==3) area[j][i]=CREATE_CELL;  //Reproduction
				}
			}
		}
	for (int i=0; i<HEIGHT+1; i++)
		{
		for (int j=0; j<WIDTH+1; j++)
			{
			if (area[j][i]>=2) area[j][i]-=2;
			}
		}
	}

int startupMenu(int INmenu)
	{
	int mychoice;
	if (MODE_MENU)
		{
		/*
		output[0]="GAME OF LIFE";
		if (INmenu==0)
			{
			output[1]="Choose:";
			output[2]="Random";
			output[3]="GlidrGun";
			output[4]="Glider";
			output[5]="LtWtSpSh";
			output[6]="Misc";
			mychoice=menu(5, output, TX);
			}
		else if (INmenu==1)
			{
			output[1]="Speed:";
			output[2]="XtraFast";
			output[3]="Fast";
			output[4]="Medium";
			output[5]="Slow";
			mychoice=menu(4, output, TX);
			}
		else if (INmenu==2)
			{
			output[1]="Size:";
			output[2]="Small";
			output[3]="Medium";
			output[4]="Large";
			mychoice=menu(3, output, TX);
			}
		*/
		}
	else
		{
		if      (INmenu==0) mychoice=1; //0=random, other=create
		else if (INmenu==1) mychoice=4; //1=XtraFast, 2=fast, 3=normal, 4=slow
		else if (INmenu==2) mychoice=2; //Large
		}
	return mychoice;
	}

int main(int argc, char* argv[])
	{
	set();
	int choice[3];
	int waitTime;
	for (int i=0; i<3; i++)
		choice[i]=startupMenu(i);
	//TextOut(32,20,"Loading",0);
	if (choice[0]==RNDM)				//If chose random
		{
		printf("randomizing\n");
		srand(time(0));						//Seed randomizer
		initArea(RNDM);						//Randomize
		}
	else								//If chose diff preset
		{
		printf("loading preset\n");
		initArea(RSET);						//Reset area
		make(choice[0]);					//Create preset
		}
	waitTime=pow(5,choice[1]);
	printf("wait time=%d\n",waitTime);
	const int blksz=(choice[2]*2+1);
	clearScreen();
	int gens=0;
	while(true)
		{
		draw(SIZE);
		SDL_Delay(waitTime);
		stepForward();
		gens++;
		if (EZ_checkForExit())
			exit(0);
		}
	}