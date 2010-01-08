#include <inttypes.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "globals.h"
#include "card.h"
#include "usart.h"


void InitPorts()
{
	DDRB = (1 << DDB_SCK) | (1 << DDB_T1);
	DDRC = (1 << DDC_IN1) | (1 << DDC_IN2) | (1 << DDC_IN3) | (1 << DDC_IN4);
	DDRD = (1 << DDD_OE) | (1 << DDD_RCK);
	DataPort = 0;
	ClockPort = 0;
}

void SetLevelPins(int state) 
{
	DataPort = state;
  	ClockPort &= ~(1 << P_SCK);
 	ClockPort |= (1 << P_SCK);
  	ClockPort &= ~(1 << P_SCK);
}

void Latch()
{
	LatchPort &= ~(1 << P_RCK);
	LatchPort |= (1 << P_RCK);
	LatchPort &= ~(1 << P_RCK);
	LatchPort &= ~(1 << P_OE);
}

void fade() //2 bresenhams
{
	int i;

	while (XChanged != 1)
	{
	    if (fademode == 1) XChanged = 1; 
		for (i = 0; i < MaxLedPins; i++)
		{
			if (dY[i] > 0) 
			{
				if (2*(eY[i] + dY[i]) < PWMres)
				{
					eY[i] += dY[i];
				}
				else
				{
					PWM[i]++;
					eY[i] += (dY[i]-PWMres);
				}
			}
			else
			{
				if (2*(eY[i] + dY[i]) > (-1*PWMres))
				{
					eY[i] += dY[i];
				}
				else
				{
					if (PWM[i] > 0) PWM[i]--; //BugFixPWMDec 09.11.23
					eY[i] += (dY[i]+PWMres);
				}
			}
		}
		
		if (2*(eX + dX) < PWMres)
		{
			eX += dX;
		}
		else
		{
			X++;
			Hold++;
			eX += dX-PWMres;
			XChanged = 1;
		}

	}
	XChanged = 0;
}

int main()
{
	volatile unsigned int i, aColumn, aLevel, aLedPin, mask, patterncntr;
	volatile div_t aDivRes;

	patterncntr = 0;
	Hold = 0;

	InitPorts();
	CARDinit();
	USARTinit();

	while (1) 
	{
	
		while (patterncntr < numanimas)
		{
			X = 0;
			eX = 0;
			XChanged = 0;
			dX = pgm_read_byte(&AnimationA[patterncntr].hold);
			fademode = pgm_read_byte(&AnimationA[patterncntr].fade);
			// serialize Level*LedPinsPerLevel -> PWM, dY, Ey for simple fading
			for (i = 0; i < MaxLedPins; i++)
			{	
				eY[i] = 0;
				aDivRes = div(i, LedPinsPerLevel);
				aLevel = aDivRes.quot;
				aLedPin = i;
				aLedPin %= LedPinsPerLevel;
			  	YStart = pgm_read_byte(&AnimationA[patterncntr].pwm[aLevel][aLedPin]);
				if (patterncntr < numanimas-1) idx = patterncntr+1; else idx = 0;
				YEnd = pgm_read_byte(&AnimationA[idx].pwm[aLevel][aLedPin]);
				dY[i] = YEnd-YStart;		 
				PWM[i] = pgm_read_byte(&AnimationA[patterncntr].pwm[aLevel][aLedPin]);
			}
			Hold = 0;

			while (Hold <= pgm_read_byte(&AnimationA[patterncntr].hold))
			{
				
				if (fademode > 0) fade();

				for (i=0; i<=PWMres; i++)
				{	
					
					CARDloop();
					USARTloop();

					for (mux=0; mux < MaxMux; mux++)
					{
						for (aColumn = 0; aColumn < LedPinsPerColumn; aColumn++)
						{	
							mask = 0;
							for (aLevel = 0; aLevel < MaxLevels; aLevel++)
							{
								idx = aColumn+mux * LedPinsPerColumn + aLevel * LedPinsPerLevel;
								if (i < PWM[idx]) mask = mask + (1 << aLevel);
							}
							SetLevelPins(mask);
						}
						switch (mux)
						{
							case 0 :
							   SetLevelPins(15);
							   SetLevelPins(0);
							   SetLevelPins(0);
							   SetLevelPins(0);
							   break;
							case 1 :
							   SetLevelPins(0);
							   SetLevelPins(15);
							   SetLevelPins(0);
							   SetLevelPins(0);
							   break;
							case 2 :
							   SetLevelPins(0);
							   SetLevelPins(0);
							   SetLevelPins(15);
							   SetLevelPins(0);
							   break;
							case 3 :
							   SetLevelPins(0);
							   SetLevelPins(0);
							   SetLevelPins(0);
							   SetLevelPins(15);
							   break;
						}	
						Latch();
					}		
				}
			if (fademode == 0)	Hold++;	
			} 
			Hold = 0;
			patterncntr++;	
		}
		patterncntr = 0;
	}
}

