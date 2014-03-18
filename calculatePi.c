//Calculate Pi
//calculatePi.c
//Joseph Dykstra
//2014-03-18

#include <stdio.h>
#include <math.h>

#define CALC_LENGTH    500000000
#define PRINT_INTERVAL 8
//#define PRINT_DURING

int main(){
	double pi=0, tJ, tK;
	int y=1;
	const long kEnd = CALC_LENGTH;
	const long kPrint = pow(10,PRINT_INTERVAL);
	for (long x = 1; x<=kEnd; x += 2) {
		pi += (double)y*4/x;
		y = -y;
#ifdef PRINT_DURING
		if (((x/2) % kPrint) < 3 || x == kEnd) {
			printf("%1.16f\n",pi);
		}
#endif
		if (x == kEnd-3)		tJ = pi;
		else if (x == kEnd-1)	tK = pi;
	}
	printf("Estimation: %1.16f", (tJ+tK)/2);
}
