int readHigh(int INaccess)
	{
	return 0;
	}

int writeHigh(int INaccess, int INscore)
	{
	return 0;
	}


int writeHighName(int INaccess, int INscore)
	{
	return 0;
	}

char ButtonPressed(int INbutton)
	{
	return 0;
	}

void ClearScreen()
	{
	drawRect.w = SCR_WIDTH;
	drawRect.h = SCR_HEIGHT;
	drawRect.x = 0;
	drawRect.y = 0;
	SDL_FillRect(screen, &drawRect, SDL_MapRGB(screen->format, color[0][0], color[0][1], color[0][2]));
	SDL_Flip(screen);
	printf("cls\n");
	}

void TextOutput(int x, int y, int n, int options)
	{
	//std::cout<<"text "<<n<<"\n";
	}

void Wait(int waittime)
	{
	//std::cout<<"wait/n";
	}

void LineOut(int INx, int INy, int INlen, int INwid, int INoptions)
	{
	//0, width*blksz+1, 99, width*blksz+1, 0
	}

void RectOut(int INx, int INy, int INwidth, int INheight, int INoptions)
	{
	//std::cout<<"RectOut/n";
	}

void NumOut(int INx, int INy, int INnum, int INoptions)
	{
	//std::cout<<"RectOut/n";
	}

	
	