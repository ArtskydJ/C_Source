void selectGame(char INfastmode)
	{
	prevQuadClear=false;
	prevRht=0;
	prevLft=0;
	score=0;
	//disp="";
	//accesshigh="Tet";
	if (INfastmode) //debugging
		{
		gamespeed=0;
		gametype=2;
		}
	else
		{}

	if		(gamespeed==0)
		{
		speedup=0.975;
		delaytime=800;
		}
	else if (gamespeed==1)
		{
		speedup=0.9375;
		delaytime=600;
		}
	else if (gamespeed==2)
		{
		speedup=0.9;
		delaytime=400;
		}
	if			(gametype==0)
		{
		chnc[Itet]=2;
		chnc[Jtet]=1;
		chnc[Ltet]=1;
		chnc[Otet]=2;
		chnc[Stet]=0;
		chnc[Ttet]=1;
		chnc[Ztet]=0;
		chnc[prob]=7;
		}
	else if (gametype==1)
		{
		chnc[Itet]=3;
		chnc[Jtet]=1;
		chnc[Ltet]=1;
		chnc[Otet]=3;
		chnc[Stet]=1;
		chnc[Ttet]=2;
		chnc[Ztet]=1;
		chnc[prob]=12;
		}
	else if (gametype==2)
		{
		chnc[Itet]=1;
		chnc[Jtet]=1;
		chnc[Ltet]=1;
		chnc[Otet]=1;
		chnc[Stet]=1;
		chnc[Ttet]=1;
		chnc[Ztet]=1;
		chnc[prob]=7;
		}
	else if (gametype==3)
		{
		chnc[Itet]=2;
		chnc[Jtet]=3;
		chnc[Ltet]=3;
		chnc[Otet]=2;
		chnc[Stet]=4;
		chnc[Ttet]=3;
		chnc[Ztet]=4;
		chnc[prob]=21;
		}
	else if (gametype==4)
		{
		chnc[Itet]=1;
		chnc[Jtet]=3;
		chnc[Ltet]=3;
		chnc[Otet]=2;
		chnc[Stet]=4;
		chnc[Ttet]=2;
		chnc[Ztet]=4;
		chnc[prob]=19;
		}
	else if (gametype==5) //DEBUG ONLY
		{
		chnc[Itet]=0;
		chnc[Jtet]=1;
		chnc[Ltet]=0;
		chnc[Otet]=2;
		chnc[Stet]=0;
		chnc[Ttet]=0;
		chnc[Ztet]=1;
		chnc[prob]=4;
		}
	ClearScreen();
	}
	

void gameResetVars()
	{	
	for (int i=0; i<AREA_HEIGHT; i++)
		{
		for (int j=0; j<AREA_WIDTH; j++)
			{
			area[j][i]=0;
			}
		}
	
	for (int i=0; i<3; i++)
		{
		int pieceToCreate=prob;
		int rndm=(rand())%(chnc[prob]);
		int add=0;
		for (int j=0; (j<=Ztet)&&(pieceToCreate==prob); j++)
			{
			add+=chnc[j];
			if (add>rndm) pieceToCreate=j*4;
			}
		if (pieceToCreate==prob)
			{
			ClearScreen();
			TextOutput(0,24,add,0);
			TextOutput(0,16,rndm,0);
			TextOutput(0,00,0,0);
			Wait(1000);
			}
		nextPiece[i]=pieceToCreate;
		}
	showDisp		= 0;
	viewDbg			= 0;
	gametype		= 0;
	gamespeed		= 0;
	delaytime		= 0;
	lockDelay		= 0;
	prevRht			= 0;
	prevLft			= 0;
	prevDrp			= 0;
	prevRot			= 0;
	currentPiece	= 0;
	currentRotate 	= 0;
	tetLR			= 0;
	tetUD			= 0;
	drop			= 0;
	prevWaited		= 0;
	speedup			= 0;
	score			= 0;
	msg				= 0;
	disp			= 0;
	accesshigh		= 0;
	alive			= 1;
	refresh			= 1;
}


void pieceResetVars()
	{
	lockDelay		= 0;
	prevRht			= 0;
	prevLft			= 0;
	prevDrp			= 0;
	prevRot			= 0;
	currentRotate	= 0;
	prevWaited		= 0;
	currentRotate	= 0;
	drop			= 0;
	lockDelay		= 0;
	floorKickUsed	= 0;
	tetLR			= (AREA_WIDTH/2)-2;
	tetUD			= -2;
	}

	
char gameEnd()
	{
	disp=888;
	inputOutput(0,0,0);
	char plyagn=false;
	Wait(2500);
	ClearScreen();
	if (highMade) writeHighName(accesshigh,score);
	ClearScreen();
	//ASK TO PLAY AGAIN
	return plyagn;
	}
	
	
void initReset()
	{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0)
		{
		fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
		exit( -1 );
		}
	screen = SDL_SetVideoMode( SCR_WIDTH, SCR_HEIGHT, SCR_BPP, SDL_SWSURFACE );
	if( !screen )
		{
		fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
		SDL_Quit();
		exit( -1 );
		}
	//freopen( "CON", "w", stdout );
	//freopen( "CON", "w", stderr );
	//Graphics
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	}