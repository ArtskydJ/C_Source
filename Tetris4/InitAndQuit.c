void initReset(void)
	{
	printf("\n");
#ifdef DEBUG_STREAM
	printf("initReset - start");
#endif

	atexit(quit);
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0)
		{
		printf("SDL_Init() bad");
		fprintf( stderr, "Could not initialize SDL: %s\n", SDL_GetError() );
		quit();
		exit(-1);
		}
	else printf("SDL_Init() good");

	screen = SDL_SetVideoMode( SCR_WIDTH, SCR_HEIGHT, SCR_BPP, SDL_SWSURFACE );
	if( !screen )
		{
		printf("SDL_SetVideoMode() bad");
		fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
		exit(-1);
		}
	else printf("SDL_SetVideoMode() good");
	if( TTF_Init() == -1 )
		{
		printf("TTF_Init() bad");
		fprintf( stderr, "Could not initialize TTF: %s\n", SDL_GetError() );
		exit(-1);
		}
	else printf("TTF_Init() good");
	font = TTF_OpenFont("arial.ttf", TEXT_SIZE);
	if( font == NULL )
		{
		printf("TTF_OpenFont() bad");
		exit(-1);
		}
	else printf("TTF_OpenFont() good");
	
	icon = SDL_CreateRGBSurface(SDL_SWSURFACE, 64, 64, SCR_BPP, 0, 0, 0, 255);
	if(icon == NULL)
		{
		printf("SDL_CreateRGBSurface() bad");
		fprintf(stderr, "CreateRGBSurface failed with icon: %s\n", SDL_GetError());
		exit(1);
		}
	else printf("SDL_CreateRGBSurface() good");
	
	EZ_apply_rect(icon, EZ_new_rect(0,	0,	64,	64), otherColors[C_BACK]);
	EZ_apply_rect(icon, EZ_new_rect(48,	8,	16,	48), otherColors[C_TEXT]);
	EZ_apply_rect(icon, EZ_new_rect(16,	40,	16,	16), otherColors[C_TEXT]);
	SDL_WM_SetIcon(icon,NULL);
	
	SDL_WM_SetCaption("Tetris | Joseph Dykstra", NULL);
	
	SDL_EnableKeyRepeat(150,10); //Defaults are 500 and 30, respectively.
#ifdef DEBUG_STREAM
	printf(" - end\n");
#endif
	}


void selectGame(char INfastmode)
	{
#ifdef DEBUG_STREAM
	printf("selectGame - start");
#endif
	prevQuadClear=false;
	//prevRht=0;
	//prevLft=0;
	score=0;
	//disp="";
	//accesshigh="Tet";
	if (INfastmode) //debugging
		{
		gamespeed=0;	//0=slow
		gametype=2;		//2=normal
		}
	else
		{
		//choose gamespeed
		//choose gametype
		}

	if		(gamespeed==0)
		{
		//speedup=0.975;
		speedup=1;
		delaytime=120;
		}
	else if (gamespeed==1)
		{
		speedup=0.9375;
		delaytime=100;
		}
	else if (gamespeed==2)
		{
		speedup=0.9;
		delaytime=80;
		}
	if		(gametype==0)
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
	else if (gametype==5) //DEBUG_STREAM ONLY
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
#ifdef DEBUG_STREAM
	printf(" - end\n");
#endif
	}
	

void gameResetVars(void)
	{
#ifdef DEBUG_STREAM
	printf("gameResetVars - start");
#endif
	for (int i=0; i<AREA_HEIGHT+2; i++)
		{
		for (int j=0; j<AREA_WIDTH; j++)
			{
			area[j][i]=EMPTY_AREA;
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
			if (add>rndm) pieceToCreate=j;
			}
		if (pieceToCreate==prob)
			{
			fprintf( stderr, "Error in randomizer code. add:%d, rndm:%d\n", add,rndm);
			SDL_Quit();
			exit( -1 );
			}
		nextPiece[i]=pieceToCreate;
		}
	viewDbg			= 0;
	//gametype		= 0;
	//gamespeed		= 0;
	//delaytime		= 0;
	lockDelay		= 0;
	currentPiece	= 0;
	currentRotate 	= 0;
	currentHoldPiece= EMPTY_AREA;
	usedHoldPiece	= false;
	tetLR			= 0;
	tetUD			= 0;
	drop			= 0;
	prevWaited		= 0;
	speedup			= 0;
	score			= 0;
	alive			= true;
	playagain		= true;
	piecemoving		= true;
	paused 			= false;
#ifdef DEBUG_STREAM
	printf(" - end\n");
#endif
}


	
char gameEnd(void)
	{
#ifdef DEBUG_STREAM
	printf("gameEnd - start");
#endif
	//drawBoard();
	//bool tPlayAgain=false;
	//SDL_Delay(2500);
	//if (highMade) writeHighName(accesshigh,score);
	//ASK TO PLAY AGAIN
#ifdef DEBUG_STREAM
	printf(" - end\n");
#endif
	return 0;//tPlayAgain;
	}


void quit(void)
	{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
	}

	
	
	
// was in init()
// icon creation code
		
		
	/*drawRect.w = 64;
	drawRect.h = 64;
	drawRect.x = 0;
	drawRect.y = 0;
	SDL_FillRect(icon, &drawRect, SDL_MapRGB(icon->format,
		otherColors[C_BACK][0],
		otherColors[C_BACK][1],
		otherColors[C_BACK][2]));*/
		
		
	/*drawRect.w = 16;
	drawRect.h = 48;
	drawRect.x = 48;
	drawRect.y = 8;
	SDL_FillRect(icon, &drawRect, SDL_MapRGB(icon->format,
		tetColors[Jtet][0],
		tetColors[Jtet][1],
		tetColors[Jtet][2]));
	drawRect.w = 16;
	drawRect.h = 16;
	drawRect.x = 16;
	drawRect.y = 40;
	SDL_FillRect(icon, &drawRect, SDL_MapRGB(icon->format,
		tetColors[Jtet][0],
		tetColors[Jtet][1],
		tetColors[Jtet][2]));*/