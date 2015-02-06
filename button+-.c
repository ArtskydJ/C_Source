int senseButton(int val, bool lr_ud, int add, int high, bool cut)
	{
	int lu,rd;
	if (lr_ud)
		{
		lu=BTNLEFT;
		rd=BTNRIGHT;
		}
	else
		{
		lu=BTNCENTER;
		rd=BTNEXIT;
		}
	if (ButtonPressed(lu)) //change to on press
		{
		val-=add;
		}
	if (ButtonPressed(rd)) //change to on press
		{
		val+=add;
		}
	if (cut)
		{
		if (val<0)    {val=0;}
		if (val>high) {val=high;}
		}
	else
		{
		if (val<0)  {val=high;}
		if (val>high)  {val=0;}
		}
	return val;
	}
