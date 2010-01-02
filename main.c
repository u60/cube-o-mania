#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "card.h"
#include "usart.h"

//74HC595 
//Serial In
#define DataPort PORTC
#define DDC_IN1 DDC0
#define DDC_IN2 DDC1
#define DDC_IN3 DDC2
#define DDC_IN4 DDC3
#define P_IN1 PC0
#define P_IN2 PC1
#define P_IN3 PC2
#define P_IN4 PC3

//Serial Clock
#define ClockPort PORTB
#define DDB_T1 DDB1
#define DDB_SCK DDB2
#define P_SCK PB2

//Latch (RCK)
#define LatchPort PORTD
#define DDD_RCK DDD5
#define P_RCK PD5

//OE 74HC595 and 74ACT540
#define DDD_OE	DDD2
#define P_OE PD2

#define MaxLEDs 3*4*4*4
#define PWMres 200
 
int8_t X, dX, eX, XChanged, YStart, YEnd;
int8_t PWM[MaxLEDs], dY[MaxLEDs], eY[MaxLEDs];

int8_t fademode = 0;
int8_t numanimas = 4;
int8_t Hold, mux, idx;
 
struct pattern {
	uint8_t hold;
	uint8_t fade;
	uint8_t pwm[MaxLEDs];
};


struct pattern AnimationA[4] PROGMEM ={
	{
	100,2,
	{
	0, 0, 0,
	0, 100, 0,
	0, 0, 0,
	20, 20, 20}},

	{
	50,2,
	{
	100,0,0,
	0,0,0,
	0,100,100,
	100,100,100}},

	{
	25,2,
	{
	0,80,0,
	90,100,0,
	0,0,0,
	10,10,10}},

		{
	10,2,
	{
	0,0,0,
	0,0,0,
	0,0,0,
	100,100,100}}, 

};


void InitPorts()
{
	DDRB = (1 << DDB_SCK) | (1 << DDB_T1);
	DDRC = (1 << DDC_IN1) | (1 << DDC_IN2) | (1 << DDC_IN3) | (1 << DDC_IN4);
	DDRD = (1 << DDD_OE) | (1 << DDD_RCK);
	DataPort = 0;
	ClockPort = 0;
}

void setLED(int state) 
{
	DataPort = state;
  	ClockPort &= ~(1 << P_SCK);
 	ClockPort |= (1 << P_SCK);
  	ClockPort &= ~(1 << P_SCK);
}

void latch()
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
		for (i = 0; i < MaxLEDs; i++)
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
	unsigned int i, k, patterncntr;

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

			for (i = 0; i < MaxLEDs; i++)
			{	
				eY[i] = 0;
			  	YStart = pgm_read_byte(&AnimationA[patterncntr].pwm[i]);
				if (patterncntr < numanimas-1) idx = patterncntr+1; else idx = 0;
				YEnd = pgm_read_byte(&AnimationA[idx].pwm[i]);
				dY[i] = YEnd-YStart;		 
				PWM[i] = pgm_read_byte(&AnimationA[patterncntr].pwm[i]);
			}
			Hold = 0;

			while (Hold <= pgm_read_byte(&AnimationA[patterncntr].hold))
			{
				
				if (fademode > 0) fade();

				for (i=0; i<=PWMres; i++)
				{	
					
					CARDloop();
					USARTloop();

					for (mux=0; mux<2; mux++)
					{
						for (k=0; k<=5; k++)
						{	
							idx = k+mux*6;
							if (i < PWM[idx]) setLED(1); else setLED(0);
						}
						switch (mux)
						{
							case 0 :
							   setLED(0);
							   setLED(1);
							   break;
							case 1 :
							   setLED(1);
							   setLED(0);
							   break;
							case 2 :
							   setLED(1);
							   setLED(0);
							   break;
							case 3 :
							   setLED(1);
							   setLED(0);
							   break;
						}	
						latch();
					}
				//	PORTC &= ~(1 << P_G); // OE				
				}
			if (fademode == 0)	Hold++;	
			} 
			Hold = 0;
			patterncntr++;	
		}
		patterncntr = 0;
	}
}

