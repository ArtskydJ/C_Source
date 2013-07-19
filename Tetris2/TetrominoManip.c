char move(int INdir, int INud)
	{
	int canMove=0;
	int addLR  =0;
	int addUD  =0;
	int tempLR =0;
	int tempUD =0;
	if		(INdir==dwn) addUD=-1;
	else if (INdir==lft) addLR= 1;
	else if (INdir==rht) addLR=-1;
	for (int i=0; i<4; i++)
		{
		tempLR=tet[currentPiece+currentRotate][i  ]+tetLR+addLR;
		tempUD=tet[currentPiece+currentRotate][i+4]+INud +addUD;
		if ((tempLR>=0)&&(tempLR<AREA_WIDTH)&&(tempUD>=0)) //&&(tempUD<height)
			{canMove+=(area[tempLR][tempUD]);}
		else canMove++;
		}
	//NumOut(0,16,canMove,0);
	//Wait(500);
	return (canMove==0);	//canMove in:	0123	0123
	}						//canMove out:	1000	TFFF


char rotate()
	{
	int canRotate=1, addRot=0, tempLR, tempUD, addUD=0, addLR=0;
	addRot=(currentRotate+1)%4;
	for (int i=0; (i<3 && canRotate>0); i++)
		{
		if (i==0) addUD= 0;	//1st	Level
		if (i==1) addUD=-1;	//2nd	D
		if (i==2) addUD= 1;	//3rd	U
		if (i==3) addUD=-2*(currentPiece*4==Itet);	//4th D if I tetromino
		if (i==4) addUD= 2*(currentPiece*4==Itet);	//5th U if I tetromino
		for (int j=0; (j<5 && canRotate>0); j++)
			{
			if (j==0) addLR= 0;	//1st	Center
			if (j==1) addLR=-1;	//2nd	L
			if (j==2) addLR= 1;	//3rd	R
			if (j==3) addLR=-2*(currentPiece*4==Itet);	//4th L if I tetromino
			if (j==4) addLR= 2*(currentPiece*4==Itet);	//5th R if I tetromino
			canRotate=0;
			for (int k=0; k<4; k++)
				{
				tempLR=tet[currentPiece+currentRotate+addRot][k	]+tetLR+addLR;
				tempUD=tet[currentPiece+currentRotate+addRot][k+4]+tetUD+addUD;
				if ((tempLR>=0)&&(tempUD>=0)&&(tempLR<AREA_WIDTH)&&(tempUD<AREA_HEIGHT+2)&&(tetUD>0))
					canRotate += area[tempLR][tempUD];
				else
					canRotate++;
				}
			}
		}
	if (canRotate==0)
		{
#ifdef ONE_FLOOR_KICK
		if (!(addUD>0 && floorKickUsed==true))
			{
#endif
			tetLR+=addLR;
			tetUD+=addUD;
#ifdef ONE_FLOOR_KICK
			if (addUD>0)
				floorKickUsed=true;
			}
#endif
		}
	return (canRotate==0);
	}
	
	
	

void pieceCreate()
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
	currentPiece=nextPiece[0];
	for (int i=1; i<previewPieces; i++)
		{
		nextPiece[i-1]=nextPiece[i];
		}
	nextPiece[previewPieces-1]=pieceToCreate;
	}


void pieceSetInto(int pieceType)
	{
	int tempLR,tempUD;
	for (int i=0; i<4; i++)
		{
		tempLR = tet[currentPiece+currentRotate][i  ]+tetLR;
		tempUD = tet[currentPiece+currentRotate][i+4]+tetUD+2; //2 upper hidden rows...
		area[tempLR][tempUD]=(pieceType/4)+1; //tetI=0, and Empty=0, so add 1
		}
	}


int clearFullRows()
	{
/*
go down...
if full...
	start going up
	overwrite the one below with current
	until fully up
do not restart at previous full
*/
	int blocksInRow=0;
	int numOfFilledLines=0;
	for (int i=0; i<AREA_HEIGHT+2; i++)		//From the top, check all rows...
		{
		blocksInRow=0;
		for (int j=0; j<AREA_WIDTH; j++)		//Add up number of blocks in row...
			blocksInRow+=(area[j][i]>0);
		
		if (blocksInRow>=AREA_WIDTH)				//If the row is full...
			{
			for (int k=i; k>=0; k--)						//...start going up the rows
				{
				for (int j=0; j<AREA_WIDTH; j++)
					{
					//printf("clear:%d",area[j][k]);
					if (k>0)	area[j][k]=area[j][k-1];		//...and overwrite current row with row above it
					else		area[j][k]=0;					//...if no row above it, empty it.
					}
				}
			numOfFilledLines++;
			}
		if (blocksInRow>0 && i<2)					//If the row has some blocks too high...
			{
			alive=false;								//...then ur dead, lol.
			}
		}

	//add to score
	switch(numOfFilledLines)
		{
		case 1:
			score+=100;
			prevQuadClear=false;
			break;
		case 2:
			score+=300;
			prevQuadClear=false;
			break;
		case 3:
			score+=500;
			prevQuadClear=false;
			break;
		case 4:
			if (!prevQuadClear)
				score+=800;
			else
				score+=1200;
			prevQuadClear=true;
			break;
		}
	if (numOfFilledLines<0)
		disp=numOfFilledLines;
	
	printf("full=%d\n",numOfFilledLines);
	return numOfFilledLines;
	}