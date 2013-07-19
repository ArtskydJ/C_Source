//InputOutputAndDraw.c
//Input, Output, and Drawing functions for Tetris
//Written by Joseph Dykstra


bool inputOutput(bool INallowInput, bool INallowOutput, int INwaited)
	{
	char temppiecemoving=true; //return this
//INPUT
//INPUT
	if (INallowInput)
		{
		char btnPressed=0;
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)) //GET INPUT
			{
			if (test_event.key.state == SDL_PRESSED)
				btnPressed=test_event.key.keysym.sym;
			}
	
		if (btnPressed==BTN_H_DROP)
			{
			lockDelay=0;
			drop=dropWHard;
			}
		else if (btnPressed==BTN_S_DROP)
			{
			lockDelay=0;
			drop=dropSoft;
			prevDrp++;
			}
		else
			{
			prevDrp=0;
			if (drop==dropWHard)
				{
				drop=dropHard;
				lockDelay=waitLock;
				}
			else
				drop=0;
			}
		
		if (btnPressed==BTN_ROTATE)
			{
			if (prevRot==0)
				{
				if (rotate())
					{
					lockDelay=0;
					refresh=true;
					currentRotate++;
					if (currentRotate>=4)
						currentRotate=0;
					}
				}
			prevRot++;
			if (prevRot>waitRotateAgain)
				prevRot=0;
			}
		else
			{
			prevRot=0;
			}
		
		if (btnPressed==BTN_MOVE_LEFT)
			{
			prevLft++;
			if ((prevLft>=waitSlowMove || prevLft<0) && move(lft,tetUD))
				{
				lockDelay=0;
				if (prevLft<0)
					prevLft=0;
				else
					prevLft=waitSlowMove-waitFastMove;
				tetLR++;
				refresh=true;
				}
			}
		else
			{
			prevLft=-5;
			}
		
		if (btnPressed==BTN_MOVE_RIGHT)
			{
			prevRht++;
			if ((prevRht>=waitSlowMove || prevRht<0) && move(rht,tetUD))
				{
				lockDelay=0;
				if (prevRht<0)
					prevRht=0;
				else
					prevRht=waitSlowMove-waitFastMove;
				tetLR--;
				refresh=true;
				}
			}
		else
			{
			prevRht=-5;
			}
		}

//OUTPUT
//OUTPUT
	if (INallowOutput) //Gravity and Drop
		{
		if (drop==dropHard)																									 //HARD DROP
			{
			char tempLoop=true;
			while (tempLoop)
				{
				if (move(dwn,tetUD))
					{
					tetUD--;
					score+=2;
					}
				else
					{
					tempLoop=false;
					lockDelay++;
					if (lockDelay>=waitLock)
						temppiecemoving=false;
					}
				}
			refresh=true;
			drop=0;
			}
		if ((INwaited%waitGravity<=prevWaited%waitGravity) || drop==dropSoft) //SOFT DROP or GRAVITY
			{
			if (drop==dropSoft)
				score++;
			refresh=true;
			if (move(dwn,tetUD))
				tetUD--;
			else
				lockDelay++;
			if (lockDelay>=waitLock)
				{
				temppiecemoving=false;
				lockDelay=0;
				}
			drop=0;
			}
		prevWaited=INwaited;
		if (score>readHigh(accesshigh))
			{
			writeHigh(accesshigh,score);
			highMade=true;
			}
		}
	return temppiecemoving; //THIS LINE WAS ADDED LATER
	}
	
	
void displayTetromino(int INtet,int INrot, int INx, int INy, bool INreal)
	{
	for (int i=0; i<4; i++)
		{
		drawRect.x = (INx + tet[INtet+INrot][i  ]) * BLOCK_SIZE;
		drawRect.y = (INy + tet[INtet+INrot][i+4]) * BLOCK_SIZE;
		drawRect.w = BLOCK_SIZE;
		drawRect.h = BLOCK_SIZE;
		if (INreal==REAL_TET)			//REAL TETROMINO
			SDL_FillRect(screen, &drawRect, SDL_MapRGB(screen->format, color[INtet/4+1][0], color[INtet/4+1][1], color[INtet/4+1][2]));
		else if (INreal==GHOST_TET)		//GHOST TETROMINO
			SDL_FillRect(screen, &drawRect, SDL_MapRGBA(screen->format, color[INtet/4+1][0], color[INtet/4+1][1], color[INtet/4+1][2],GHOST_ALPHA));
		SDL_Flip(screen);
		printf("dispTet(%d,%d)\n",INtet,INrot);
		}
	}


void boardDraw(bool INallowDraw, bool INallowLog)
	{
	if (INallowDraw)			//refresh the screen:
		{
		if (refresh)
			ClearScreen();	
		
		
		
		//OUTER EDGE LINE...
		//oh noes
		
		//AREA...
		drawRect.w = BLOCK_SIZE;
		drawRect.h = BLOCK_SIZE;
		for (int x=0; x<AREA_WIDTH; x++)
			if (INallowLog) printf("-");
		if (INallowLog) printf("\n");
		for (int y=2; y<AREA_HEIGHT+2; y++)
			{
			for (int x=0; x<AREA_WIDTH; x++)
				{
				int test=area[x][y];
				if (test>0) //Piece
					{
					drawRect.x = x*BLOCK_SIZE;
					drawRect.y = (y-2)*BLOCK_SIZE; //2 rows are hidden
					SDL_FillRect(screen, &drawRect, SDL_MapRGB(screen->format, color[test][0], color[test][1], color[test][2]));
					if (INallowLog) printf("%d",test);
					}
				else
					if (INallowLog) printf(" ");
				}
			if (INallowLog) printf("\n");
			}
		for (int x=0; x<AREA_WIDTH; x++)
			if (INallowLog) printf("-");
		if (INallowLog) printf("\n\n");
		
		
		//NEXT PIECES / MESSAGE
		for (int i=0; i<previewPieces; i++)//tet,rot,x,			y,			type
			displayTetromino(nextPiece[i], 1, AREA_WIDTH+1, (5*i), REAL_TET);
	
		//CURRENT TETROMINO
#ifdef SHOW_CURR_PIECE
		displayTetromino(currentPiece,currentRotate,tetLR,tetUD,REAL_TET);
#endif
		
#ifdef SHOW_GHOST_PIECE
		int tempUD=tetUD;
		char tempLoop=1;
		//Ghost Piece
		while (tempLoop)
			{
			if (move(dwn,tempUD)) {tempUD--;}
			else
				{
				//tetUD++;
				tempLoop=false;
				displayTetromino(currentPiece,currentRotate,tetLR,tempUD,GHOST_TET);
				}
			}
#endif
		
		//OUTER EDGE LINE
		drawRect.x = AREA_WIDTH*BLOCK_SIZE;
		drawRect.y = 0;
		drawRect.w = BLOCK_SIZE/2;
		drawRect.h = AREA_HEIGHT*BLOCK_SIZE;
		SDL_FillRect(screen, &drawRect, SDL_MapRGB(screen->format, color[C_TEXT][0], color[C_TEXT][1], color[C_TEXT][2]));
		
		//SCORE IN WINDOW NAME
		char tempCaption[40];
		sprintf(tempCaption,"TETRIS | Score:%d | Joseph Dykstra",score);
		SDL_WM_SetCaption(tempCaption, NULL);
		SDL_Flip(screen);
		}
	}

	
	
	
	
	
/*
for (int i=0; i<previewPieces; i++)//tet,rot,	x,					y
	displayTetromino(nextPiece[i], 0, 63-4*BLOCK_SIZE, 78-(4*BLOCK_SIZE*i)+(nextPiece[i]==Otet*4)*BLOCK_SIZE,REAL_TET);
if (showDisp>0&&disp==0)
	{
	TextOutput(msgX,msgY,0,0);
	showDisp=0;
	}
if (disp!=0)
	{
	TextOutput(msgX,msgY,disp,0);
	showDisp++;
	if (showDisp==0) refresh=2;
	if (showDisp>waitDisp) disp=0;
	}
*/
