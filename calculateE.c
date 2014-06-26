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
	double e=2, tJ, tK;
	int y=1;
	for (long x = 1; x<=CALC_LENGTH; ) {
		if ((x%3)==0)

		if (x == CALC_LENGTH-3)       tJ = e;
		else if (x == CALC_LENGTH-1)  tK = e;

		#ifdef PRINT_DURING
			const long kPrint = pow(10,PRINT_INTERVAL);
			if (((x/2) % kPrint) < 3 || x == CALC_LENGTH) {
				printf("%1.16f\n",e);
			}
		#endif
	}
	printf("Estimation: %1.16f", (tJ+tK)/2);
}
