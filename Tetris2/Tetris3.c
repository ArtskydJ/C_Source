//Tetris
//Joseph Dykstra
//Port started 07-15-2013
//Finished ??-??-2013
#include "SDL/SDL.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//#define DEBUG

#include "DefinitionsAndData.c"
#include "SmallFunctions.c"
#include "InitAndQuit.c"
#include "TetrominoManip.c"
#include "InputOutputAndDraw.c"
#ifdef DEBUG
	#include "Debug.c"
	#ifdef MODE
		#undef MODE
	#endif
	#define MODE	6
#endif


/*	Modes:
 * 0	normal
 * 1	fast
 * 2	debug clearFullRows()
 * 3	dubug rotation
 * 4	debug peiceSetinto()
 * 5	debug peiceCreate()
 * 6	debug gravity in inputOutput()
 */


int main( int argc, char *argv[] )
	{
	initReset();
	srand(time(0));
	ClearScreen();
	if (MODE==0||MODE==1)
		{
		char playagain=true;
		char piecemoving;
		while (playagain)
			{
			ClearScreen();
			selectGame(1);
			gameResetVars();
			selectGame(MODE);
			alive=true;
			while (alive)
				{
				pieceResetVars();
				pieceCreate();
				piecemoving=move(dwn,tetUD);	//If a piece was made where it...
				alive=piecemoving;				//can't move down, end the game.
				if (alive) ClearScreen();
				for (int i=0; piecemoving; i++) //waiting
					{
					piecemoving=inputOutput(true,true,i);
					boardDraw(true,(i%10)==0);
					SDL_Delay(10);
#ifdef DEBUG
					debugStream(i);
#endif
					}
				delaytime*=speedup;
				pieceSetInto(currentPiece);
				clearFullRows();
				}
			playagain=gameEnd();
			}
		}
#ifdef DEBUG
	else
		{
		debug(MODE);
		}
#endif
	SDL_Quit();
	return 0;
	}

/*
BUGS

Unfunctional modes:
	0 - dies right away (add debugging messages)
	1
Functional modes:
	2
	3
	4
	5
	6





Process Order:
-Rotation
-Move
-Drop
-Gravity

Soft Drop					DONE
Hard Drop					DONE
Clockwise Rotation			DONE
Right Side Bias				DONE
Delayed Auto Shift			DONE
Wall kicks					DONE

Allow only 1 floor kick									DELETED (Don't Like)
Allow I wall kicking always.							DONE
Allow I floor kicking even when not touching ground		DONE

Adhere to SRS guidelines, some ARS guidelines
	http://tetris.wikia.com/wiki/SRS
	http://tetris.wikia.com/wiki/ARS

*/
