void debugStream(int INint)
	{
	bool insideLoop=0;
	for (int i=0;i<5&&!insideLoop;i++) //check if any debugs are allowed
		{
		insideLoop+=allowDbg[i];
		}
	if (insideLoop)									 //if any are...
		{
		insideLoop=true;
		while (insideLoop)							//go to the next allowed one.
			{
			if (allowDbg[viewDbg]) insideLoop=false;
			if (insideLoop==true)	viewDbg++;
			if (viewDbg>=5)				viewDbg=0;
			}
		if			(viewDbg==0)
			printf("dsp %s   ahi %s   sdp %d     i %d\n",disp,accesshigh,speedup,INint);
		else if (viewDbg==1)
			printf("sc %d   gt %d   gs %d   dt %d   lD %d\n",score,gametype,gamespeed,delaytime,lockDelay);
		else if (viewDbg==2)
			printf("pW %d   pL %d   pR %d   pD %d   pR %d\n",prevWaited,prevLft,prevRht,prevDrp,prevRot);
		else if (viewDbg==3)
			printf("cP %d   cR %d   tL %d   tU %d\n",currentPiece,currentRotate,tetLR,tetUD);
		else if (viewDbg==4)
			printf("dp %d   lv %d   pQ %d   hM %d\n",drop,alive,prevQuadClear,highMade);
		}
	}


void debug(int INmode)
	{
	printf("Debug #%d\n",INmode);
	SDL_Delay(2000);
	prevQuadClear=false;
	prevLft=0;
	prevRht=0;
	selectGame(1);
	gameResetVars();
	score=rand()%20000+10000;
	ClearScreen();

	if (INmode==2) //ClearFullRows()
		{
		for (int i=0; i<AREA_HEIGHT+2; i++)
			{
			for (int j=0; j<AREA_WIDTH; j++)
				{
				area[j][i]=rand()%15;
				if (area[j][i]>0)
					area[j][i]=area[j][i]%3+1;
				}
			}
		//inputOutput(false,false,0);
		boardDraw(true,true);
		SDL_Delay(5000);
		clearFullRows();
		ClearScreen();
		SDL_Delay(250);
		//inputOutput(false,false,0);
		boardDraw(true,true);
		SDL_Delay(5000);
		}

	else if (INmode==3) //displayTetromino()
		{
		int tets,angl;
		for (tets=0; tets<7; tets++)
			{
			for (angl=0; angl<4; angl++)
				{
				ClearScreen();
				displayTetromino(tets*4,angl,0,0,REAL_TET);
				SDL_Delay(1000);
				}
			}
		}

	else if (INmode==4) //peiceSetinto()
		{
		pieceCreate();
		tetUD=10;
		pieceSetInto(currentPiece);
		inputOutput(false,false,0);
		boardDraw(true,true);
		SDL_Delay(3000);
		debugStream(0);
		ClearScreen();
		displayTetromino(currentPiece,currentRotate,tetLR*BLOCK_SIZE,tetUD*BLOCK_SIZE,REAL_TET);
		SDL_Delay(500);
		inputOutput(false,false,0);
		boardDraw(true,true);
		SDL_Delay(3000);
		}
	else if (INmode==5) //peiceCreate()
		{
		while (1)
			{
			pieceCreate();
			ClearScreen();
			NumOut(0,48,currentPiece,4096);
			NumOut(0,40,nextPiece[0],4096);
			NumOut(0,32,nextPiece[1],4096);
			NumOut(0,24,nextPiece[2],4096);
			SDL_Delay(400);
			}
		}
	else if (INmode==6) //gravity
		{
		pieceCreate();
		while(1)
			{
			ClearScreen();
			inputOutput(false,false,0);
			boardDraw(true,true);
			SDL_Delay(1000);
			tetUD--;
			}
		}
	}
