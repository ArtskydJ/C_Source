//Triangle.c
//Joseph Dykstra
//2013-06-28

int moves[18][3]={
	{0,	1,	3}, //0 1 3 6 10
	{1,	3,	6},
	{3,	6,	10},
	{0,	2,	5}, //0 2 5 9 14
	{2,	5,	9},
	{5,	9,	14},
	{2,	4,	7}, //2 4 7 11
	{4,	7,	11},
	{1,	4,	8}, //1 4 8 13
	{4,	8,	13},
	{3,	7,	12}, //3 7 12
	{5,	8,	12}, //5 8 12
	{3,	4,	5}, //3 4 5
	{6,	7,	8}, //6 7 8 9
	{7,	8,	9},
	{10,11,	12}, //10 11 12 13 14
	{11,12,	13},
	{12,13,	14}
};
int board[15];
int i;
for (i = 0; i<15; i++) {
	board[i]=i;
}
char options = 2;
char valid;
char froms[5]
char tos[5];
int fromi, toi;


void drawBoard() {
	printf("\t\t\t\t\t1%s\n\n",
		board[0]?"x":"o"
	);
	printf("\t\t\t\t2%s\t3%s\n\n",
		board[1]?"x":"o",
		board[2]?"x":"o"
	);
	printf("\t\t\t4%s\t5%s\t6%s\n\n",
		board[3]?"x":"o",
		board[4]?"x":"o",
		board[5]?"x":"o"
	);
	printf("\t\t7%s\t8%s\t9%s\t10%s\n\n",
		board[6]?"x":"o",
		board[7]?"x":"o",
		board[8]?"x":"o",
		board[9]?"x":"o"
	);
	printf("\t11%s\t12%s\t13%s\t14%s\t15%s\n",
		board[10]?"x":"o",
		board[11]?"x":"o",
		board[12]?"x":"o",
		board[13]?"x":"o",
		board[14]?"x":"o"
	);
}


int validation(int from, int to) {
	int result = 0;
	if ((from>=1 && from<=15) && (to>=1 && to<=15)) {
		for(i = 0; i < 18; i++) {
			if (moves[i][1] == from && moves[i][3] == to) {
				if (board[moves[i][1]] && board[moves[i][2]] && !board[moves[i][3]]) {
					result = 1;
					board[moves[i][3]] = board[moves[i][1]];
					board[moves[i][2]] = 0;
					board[moves[i][1]] = 0;
				}
				i = 18;
			} else if (moves[i][3] == from && moves[i][1] == to) {
				if (board[moves[i][3]] &&  board[moves[i][2]] && !board[moves[i][1]]) {
					result = 1;
					board[moves[i][1]] = board[moves[i][3]];
					board[moves[i][2]] = 0;
					board[moves[i][3]] = 0;
				}
				i = 18;
			}
		}
	}
	return result;
}


int main(void) {
	while(options) {
		valid = 0;
		while(!valid) {
			//input box a-o and a-o
			printf("\nMove peg from: ");
			froms = getstr();
			printf("\nMove peg to: ");
			tos = getstr();
			fromi = atoi(froms);
			toi = atoi(tos);
			//move if valid
			valid = validation();
			//print valid yes/no			
			printf("%salid move", valid?"V":"Inv");
		}

		//check if can move more
		int n;
		for (n = 0; n < 18; n++) {
			if(!board[moves[n][0]] && board[moves[n][1]] && board[moves[n][2]]) {
				options++;
			}
			if(!board[moves[n][2]] && board[moves[n][1]] && board[moves[n][0]]) {
				options++;
			}
		}
		
		//draw
		drawBoard();
	}
}
