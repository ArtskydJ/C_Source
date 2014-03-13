//	Joseph Dykstra
//	2013-11-18
//	http://xkcd.com/710/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
	{
	srand((unsigned)time(NULL));
	int n=rand()%100, i;
	printf("Original:%d\n",n);
	for (i=0; n>1; i++)
		{
		if (n%2==0)
			n/=2;
		else
			n=n*3+1;
		printf("%d\n",n);
		}
	printf("Iterations: %d\n",i);
	}