// Joseph Dykstra
// This must be run from explorer or cmd
// Does not work if launched from NPPexec
#include <stdio.h> //printf, gets
#include <stdlib.h> //atoi
#include <stdbool.h> //bool, true, false

#define NO_BITS 16

int main()
	{
	int x;
	//while(true){}
	char str[256];
	while (x)
		{
		printf("\nEnter number: (0 to quit)\n");
		gets(str);
		x = atoi(str);
		bool tBit[NO_BITS];
		for (int i=0; i<NO_BITS; i++)
			{
			tBit[i] = (x & (1<<(NO_BITS-1-i)) ) != 0;
			}
		printf("Binary: ");
		for (int i=0; i<NO_BITS; i++)
			{
			printf("%d",tBit[i]);
			}
		}
	return 0;
	}