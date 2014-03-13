//Vex Lift Sync (test lift vals)
//Joseph Dykstra
//2013-11-09

//--DO CHANGE--//
#define START_SEN_L	600
#define target		3000
#define START_SEN_R	800
#define LOOP_NUM	150
//--DO CHANGE--//

//**DO NOT CHANGE**//
#include <stdio.h>
//#include <math.h>
#define L_LIFT		0
#define R_LIFT		1
#define FWD			127
#define REV			(-127)
#define p			(1)
#define LIFT_SLEW	8
#define EMU_P		(4)
#define capValue(Min,Value,Max)		Value = (Value<Min)? (Min):(Value); Value = (Value>Max)? (Max):(Value)

int motorTarget[2], motorSlewed[2], motor[2];
int senLeftLiftPot = START_SEN_L;
int senRightLiftPot = START_SEN_R;
int fakeTarget;

int abs(int INval)
	{ return (INval<0) ? -INval : INval; }

float slew(int INtargetValue, int INlastValue, float INslew)
	{
	int diff = INtargetValue-INlastValue;
	if		(diff >  INslew) diff = INslew;
	else if (diff < -INslew) diff =-INslew;
	return diff;
	}


int main()
	{
	printf("LEFT\t\t\t\t\t\t\t\tDIFF\t\tRIGHT\n");
	for (int i=0; i<LOOP_NUM; i++)
		{
		fakeTarget=0;
		float tLLift, tRLift, tLLiftAdd, tRLiftAdd;
		if (abs(target)>127)
			{
			tLLift = (float) p * (target - senLeftLiftPot);
			tRLift = (float) p * (target - senRightLiftPot);
			capValue(REV, tLLift, FWD);
			capValue(REV, tRLift, FWD);
			fakeTarget=target;
			}
		else
			{
			printf("speed");
			tLLift = target;
			tRLift = target;
			}
		
		tLLiftAdd = -senLeftLiftPot + senRightLiftPot;
		/*tLLiftAdd = (fakeTarget-senLeftLiftPot>0) ? 0 : tLLiftAdd;
		tLLiftAdd = (fakeTarget-senLeftLiftPot<0) ? 0 : tLLiftAdd;*/
		
		tRLiftAdd = -senRightLiftPot + senLeftLiftPot;
		capValue(REV, tLLiftAdd, FWD);
		capValue(REV, tRLiftAdd, FWD);
		/*tRLiftAdd = (fakeTarget-senRightLiftPot>0) ? 0 : tRLiftAdd;
		tRLiftAdd = (fakeTarget-senRightLiftPot<0) ? 0 : tRLiftAdd;*/
		
		
		/*if (tLLift-fakeTarget !=0 && tRLift-fakeTarget !=0)
			{
			tLLift *= (float)(senLeftLiftPot-fakeTarget)/(senRightLiftPot-fakeTarget);
			tRLift *= (float)(senRightLiftPot-fakeTarget)/(senLeftLiftPot-fakeTarget);
			}*/
		
		motorTarget[L_LIFT] = tLLift+tLLiftAdd;
		motorTarget[R_LIFT] = tRLift+tRLiftAdd;
		
		
		motorSlewed[L_LIFT] += slew(motorTarget[L_LIFT], motorSlewed[L_LIFT], LIFT_SLEW);
		capValue(REV, motorSlewed[L_LIFT], FWD);
		motor[L_LIFT] = motorSlewed[L_LIFT];
		
		motorSlewed[R_LIFT] += slew(motorTarget[R_LIFT], motorSlewed[R_LIFT], LIFT_SLEW);
		capValue(REV, motorSlewed[R_LIFT], FWD);
		motor[R_LIFT] = motorSlewed[R_LIFT];
		
		
		senLeftLiftPot +=  motor[L_LIFT]/EMU_P; //reversed pot
		senRightLiftPot += motor[R_LIFT]/EMU_P;
		
		printf("pot: %d\ttrgt: %d\tmotor: %d\tdelta: %d\tdiff: %d\t",senLeftLiftPot, motorTarget[L_LIFT], motor[L_LIFT], senLeftLiftPot-fakeTarget,senLeftLiftPot-senRightLiftPot);
		printf("pot: %d\ttrgt: %d\tmotor: %d\tdelta: %d\n",senRightLiftPot,  motorTarget[R_LIFT], motor[R_LIFT], senRightLiftPot-fakeTarget);
		}
	}