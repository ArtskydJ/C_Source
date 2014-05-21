//	Exercise 7.27
//
//	Programmed by Joseph Dykstra, finished 05/11/2012.
//	Ported to C on 2013-07-16
//	Compiles with the GNU c99 compiler
//	gcc -std=c99 -o "C:/path/to/EightQueens3.exe" "C:/path/to/EightQueens3.c"
 
#define FAST		//Skips some debug stream
//#define DEBUG		//
#include <stdio.h>
#include <conio.h>
void clearcolumn(int),clearboard(),printboard();
int valid(int,int);
int temp=0, board[8][8], makeBool(int);

#ifdef DEBUG
#include <stdlib.h> //srand, rand
#include <time.h>   //randomization
int main() //replaces current main() function
	{
	srand(time(0));
	while(1)
		{
		int curr_col=0;
		int curr_row=0;
		for (int a=0; a<8; a++) //randomly generated queens
			for (int s=0; s<8; s++)
				board[a][s] = !makeBool(rand()%20); //about one in 20 are generated, ~3 are generated
		printboard();
		printf("row:"); //user enters potential position for a queen to be...
		cin>>curr_row;
		curr_row--;
		printf("column:"); //...placed in, and then it checks if it can be placed there.
		cin>>curr_col;
		curr_col--;
		printf("%d,%d is %salid.\n\n\n",curr_row,curr_col,valid(curr_row,curr_col)?"inv":"v");
		}
	}
#else
int main()
	{
	clearboard();
	int curr_col=0; //column
	int curr_row=0; //row
	while (curr_col<8) //'for' loops seem to cause trouble here...
		{
		curr_row=0;
		while (curr_row<8) //...and here
			{
			if (valid(curr_row,curr_col)==0) //if valid
				{
				if (board[curr_row][curr_col]==0) //if board is clear here
					{
					board[curr_row][curr_col]=1; //set queen here
					curr_row=10; //exit row loop
					curr_col++; //go to next column
					temp=0; //dont execute temp
					#ifndef FAST
						printf("\nColumn %d completed.\n",curr_col);
					#endif
					}
				else
					{
					board[curr_row][curr_col]=-1; //set as a position a queen can not be placed
					temp=1; //execute temp
					#ifndef FAST
						printf("\nSkipping square\n");
					#endif
					}
				}
			else		//if not valid
				temp=1;	//execute temp
			
			if (temp==1) //temp
				{
				curr_row++; //go to next row
				if (curr_row==8) //if at the end
					{
					#ifndef FAST
						printf("Can't go into column %d\n. Backing up:\n|",(curr_col+1));
					#endif
					clearcolumn(curr_col); //curr_colear current column
					curr_col-=1; //go to previous column
					curr_row=10; //exit row loop
					}
				}
			}//end of row loop
		#ifndef FAST
			printboard();
		#endif
		} // FINISHED!!!
	printboard(); //print the board, do not disable this
	printf("\nPress any key to continue...");
	getch();
	}
#endif

int valid(int INrow,int INcol) //checks if the square is valid
	{
	//the reason the returnme variable adds a makeboolean (makeBool)...
	//...number is in case board[?][?] is a negative integer.
	int returnme=0;
	int check;
	for (check=0; check<INcol; check++) //left
		returnme+=makeBool(board[INrow][check]);
	
	for (check=1; check<=INrow && check<=INcol; check++) //up&left diagonal
		returnme+=makeBool(board[INrow-check][INcol-check]);
	
	for (check=1; (INrow+check)<=7 && (INcol-check)>=0; check++) //down&left diagonal
		returnme+=makeBool(board[INrow+check][INcol-check]);

	//cout << returnme; //debugging code
	return	returnme;
	}

int makeBool(int INval) //takes the int input, and outputs a boolean integer.
	{
	return (INval<=0) ? 0 : 1;
	}

void clearboard()
	{
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++)
			board[x][y] = 0;
	}

void clearcolumn(int INcolumn)
	{
	for (int i=0; i<8; i++)
		board[i][INcolumn] = 0;
	}

void printboard()
	{
	int blk=0;
	printf("RC1_2_3_4_5_6_7_8C\n1|");
	for (int col=0; col<8; col++)
		{
		for (int row=0; row<8; row++)
			{
			if (board[col][row]==1) //IF QUEEN
				printf("*|");	 //'*' either color if queen
			else								 //IF NO QUEEN
				{
				if (blk%2)
					printf(" |"); //' ' if white and no queen
				else
					printf("=|"); //'=' if black and no queen
				}
			blk++;
			}
		blk++;
		if (col<7)
			printf("\n%d|",(col+2));
		else
			printf("\nR\n");
		}
	}



