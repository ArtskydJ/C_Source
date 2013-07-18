//Snake.cpp
//Classic Snake Game
//Written by Joseph Dykstra
/* Compiled with Notepad++ and NppExec,
using MinGW (32-bit) and SDL (32-bit).
The following commands were used:
	cd $(CURRENT_DIRECTORY)
	gcc -std=c99 -o $(NAME_PART).exe $(FILE_NAME) -lmingw32 -lSDLmain -lSDL -mwindows
	$(CURRENT_DIRECTORY)\$(NAME_PART).exe
*/

//#define DEBUG
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "C:\SDL\include\SDL\SDL.h"
#define cSnake			SDL_MapRGB(screen->format,000,000,255)
#define cFood			SDL_MapRGB(screen->format,000,200,000)
#define cBack			SDL_MapRGB(screen->format,225,225,225)
#define SCR_WIDTH		640
#define SCR_HEIGHT		480
#define SCR_BPP			32
#define FULL			255
#define BlockSize		40
#define WidthBlocks		16
#define HeightBlocks	12
#define Difficulty		2
#define LF	1
#define UP	2
#define RT	3
#define DN	4

int firstx,firsty,lastx,lasty;
int selection,length,grow,startlength;
int dir=RT;
int score=0;
int board[WidthBlocks+1][HeightBlocks+1];
float speedup, delaytime;
bool foodate=false;
bool dead=false;
bool quit=false;
SDL_Surface *screen=NULL;
SDL_Rect drawrect;

int set()
	{
	int ret=SDL_Init(SDL_INIT_VIDEO);
	if (ret==0)
		{
		//Allow cout
#ifdef DEBUG
		freopen( "CON", "w", stdout );
		freopen( "CON", "w", stderr );
#endif
		//Graphics
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
		//screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);
		screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_SWSURFACE);
		}
	return ret;
	}

void reset(int selection)
	{
	SDL_WM_SetCaption("SNAKE | Score:0 | Joseph Dykstra", NULL);
	if (selection<1) {selection=1;}
	if (selection>5) {selection=5;}
	if (selection==1)
		{
		grow=2;
		startlength=3;
		speedup=0.975;
		delaytime=300;
		}
	else if (selection==2)
		{
		grow=3;
		startlength=3;
		speedup=0.9375;
		delaytime=250;
		}
	else if (selection==3)
		{
		grow=4;
		startlength=3;
		speedup=0.9;
		delaytime=200;
		}
	else if (selection==4)
		{
		grow=10;
		startlength=10;
		speedup=1;
		delaytime=150;
		}
	srand(time(0));
	foodate=0;
	dead=0;
	dir=RT;
	score=0;
	drawrect.x = 0;
	drawrect.y = 0;
	length=startlength;
	firstx=startlength-1;
	firsty=lastx=lasty=0;
	for (int x=0;x<WidthBlocks;x++)
		{
		for (int y=0;y<HeightBlocks;y++) //CLEAR BOARD
			{
			board[x][y]=0; //(rand()%3)%2;
			}
		}
	if (startlength>WidthBlocks) startlength=WidthBlocks;
	for	(int x=0;x<startlength;x++) //MAKE SNAKE
		{
		board[x][0]=x+1;
		}
	}

void makeFood()
	{
	int n=1;
	while (n) //MAKE FOOD
		{
		int x=round(rand()%(WidthBlocks-1)+1);
		int y=round(rand()%(HeightBlocks-1)+1);
		if (board[x][y]==0) {n=0; board[x][y]=-1;}
		}
	foodate=0;
	dead=0;
	}

void snakeMove()
	{
	int n=0;
	SDL_Event test_event;
	while(SDL_PollEvent(&test_event)) //GET INPUT
		{
		if (test_event.type == SDL_QUIT)
			{
			quit=1;
			}
		if (test_event.key.state == SDL_PRESSED)
			{
			switch (test_event.key.keysym.sym)
				{
				case SDLK_DOWN:	n=DN; break;
				case SDLK_RIGHT: n=RT; break;
				case SDLK_UP:		n=UP; break;
				case SDLK_LEFT:	n=LF; break;
				}
			}
		}
#ifdef DEBUG
	printf("1dir %d\n",dir);
	printf("1n	%d\n",n);
#endif
	if ((n==LF) || (n==UP) || (n==RT) || (n==DN)) //PROCESS INPUT
		{
		if((n==LF && dir!=RT) ||
			 (n==RT && dir!=LF) ||
			 (n==DN && dir!=UP) ||
			 (n==UP && dir!=DN))	 dir=n;
		}
#ifdef DEBUG
	printf("2dir %d\n",dir);
	printf("2n	%d\n",n);
#endif
	int tempx=firstx;
	int tempy=firsty;
	if (dir==LF) tempx--;
	if (dir==UP) tempy--;
	if (dir==RT) tempx++;
	if (dir==DN) tempy++;
	if	(tempx<0 || tempx>=WidthBlocks || tempy<0 || tempy>=HeightBlocks)
		{
		dead = 1;
		foodate = 1;
		}
	else
		{
		n=board[tempx][tempy]; //Out of array?????
		if (n>1) dead=1;
		if	(n<=1)	board[tempx][tempy]=length+1;
		if	(n==-1) foodate=1;
		}
#ifdef DEBUG
	printf("tempx %d\n",tempx);
	printf("tempy %d\n",tempy);
	if (dead==0) 
	printf("alive\n");
	printf("length %d\n",length);
#endif
	if (dead==0) //GROW
		{
		int high = startlength-1;
		//length=0;
		for	(int x=0;x<WidthBlocks;x++)
			{
			for	(int y=0;y<HeightBlocks;y++)
				{
				n=board[x][y];
				if (n>high) {firstx=x;firsty=y;high=n;}
				if (n==1)	 {lastx=x;lasty=y;}
				if (n>=1)	 {board[x][y]--;}//length++;}
				}
			}
		}
#ifdef DEBUG
	printf(" firstx=%d, firsty=%d, lastx=%d, lasty=%d\n\n",firstx,firsty,lastx,lasty);
#endif
	}

void snakeDraw()
	{
	SDL_FillRect(screen,NULL,cBack);
	drawrect.h = BlockSize;
	drawrect.w = BlockSize;
	for (int y=0;y<HeightBlocks;y++)
		{
		for (int x=0;x<WidthBlocks;x++)
			{
			if (board[x][y]>0) //Snake
				{
				drawrect.x = x*BlockSize;
				drawrect.y = y*BlockSize;
				SDL_FillRect(screen , &drawrect , cSnake);
				}
			if (board[x][y]<0) //Food
				{
				drawrect.x = x*BlockSize;
				drawrect.y = y*BlockSize;
				SDL_FillRect(screen , &drawrect , cFood);
				}
			}
		}
	SDL_Flip(screen);
	}

void snakeGrow()
	{
	if (dead==0)
		{
		for (int y=0;y<HeightBlocks;y++)
			{
			for (int x=0;x<WidthBlocks;x++)
				{
				if	(board[x][y]>=1)	{board[x][y]+=grow;}
				}
			}
		score+=1;
		length+=grow;
		delaytime*=speedup;
		floor(delaytime);
		char caption[30];
		sprintf(caption,"SNAKE | Score:%d | Joseph Dykstra",score);
		SDL_WM_SetCaption(caption,"Snake");
		}
	}

void gameOver()
	{
	if (!quit)
		quit=(MessageBox(MB_APPLMODAL,"Play Again?","GAME OVER",MB_YESNO|MB_ICONQUESTION)==IDNO);
#ifdef DEBUG
	cout<<"quit="<<quit;
#endif
	}

int main(int argc, char *argv[])
{
	int go=set();
	if (go==0)
		{
		while (!quit)
			{
			reset(Difficulty);
			while (!dead && !quit) //WHILE: ALIVE
				{
				makeFood();
				while (!dead && !foodate && !quit) //WHILE: FOOD NOT EATEN
					{
					snakeDraw();
					for (int i=0; i<delaytime && !quit; i++)
						SDL_Delay(1); //WAIT
					snakeMove();
					}
					snakeGrow();
				}
			gameOver();
			}
		}
	SDL_Quit();
	return go;
}

/* ISSUES - BUGS
*/

/*
cin>>selection;
//...
else if (selection==5)
	{
	cout<<"Start Length = ";
	cin>>startlength;
	cout<<"Grow Length  = ";
	cin>>grow;
	cout<<"Speed up     = ";
	cin>>speedup;
	cout<<"Start Delay  = ";
	cin>>delaytime;
	}
*/

/*
void intro()
	{
	cout<<" /-----\\  " <<"|\\      |        /\\        |   /  |-----" <<endl;
	cout<<"(         "  <<"| \\     |       /  \\       |  /   |     " <<endl;
	cout<<" \\        " <<"|  \\    |      /    \\      | /    |     " <<endl;
	cout<<"  \\--\\    "<<"|   \\   |     /------\\     |(     |-----" <<endl;
	cout<<"      \\   " <<"|    \\  |    /        \\    | \\    |     "<<endl;
	cout<<"       )  "  <<"|     \\ |   /          \\   |  \\   |     "<<endl;
	cout<<"\\-----/   " <<"|      \\|  /            \\  |   \\  |-----"<<endl;
	cout<<endl;
	cout<<"|\\    /|   /\\   |--\\ |--"<<"    |--\\ \\  / "<<"   --|--  /--\\  /--\\ |-- |-\\ |  |    |--\\"<<endl;
	cout<<"| \\  / |  /--\\  |   ||--" <<"    |--<  \\/  " <<"     |   (    ) \\--\\ |-- |-/ |--|    |  |"  <<endl;
	cout<<"|  \\/  | /    \\ |--/ |--" <<"    |--/  |    " <<"  \\-|    \\--/  \\--/ |-- |   |  |    |--/."  <<endl;
	cout<<endl;
	cout<<" \\    /\\    / -|- --|-- |  |    --|--  /--\\  /--\\ -|-   /\\   |  |    | /\n";
	cout<<"  \\  /  \\  /   |    |   |--|      |   (    ) \\--\\  |   /--\\  |--|    |< \n";
	cout<<"   \\/    \\/   -|-   |   |  |    \\-|    \\--/  \\--/ -|- /    \\ |  |    | \\.\n\n";
	cout<<"Controls: WASD"<<endl;
	cout<<"Choose:" <<endl;
	cout<<"1"<<setw(8)<<"Easy"  <<endl;
	cout<<"2"<<setw(8)<<"Medium"<<endl;
	cout<<"3"<<setw(8)<<"Hard"  <<endl;
	cout<<"4"<<setw(8)<<"Death" <<endl;
	cout<<"5"<<setw(8)<<"Custom"<<endl;
	}
*/