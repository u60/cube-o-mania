#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>


#define DDC_IN DDC0
#define DDC_SCK DDC3
#define DDC_G DDC1
#define DDC_SCL DDC4
#define DDC_RCK DDC2

#define P_IN PC0
#define P_SCK PC3
#define P_G PC1
#define P_SCL PC4
#define P_RCK PC2

#define MaxLEDs 3*4*4*4
#define PWMres 100
 
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

void setLED(int state) 
{
	if (state == 1 ) PORTC &= ~(1 << P_IN); else PORTC |= (1 << P_IN);
  	PORTC &= ~(1 << P_SCK);
 	PORTC |= (1 << P_SCK);
  	PORTC &= ~(1 << P_SCK);
}

void commit()
{
	PORTC &= ~(1 << P_RCK);
	PORTC |= (1 << P_RCK);
	PORTC &= ~(1 << P_RCK);
	PORTC &= ~(1 << P_G);
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


	DDRC = (1 << DDC_IN) | (1 << DDC_SCK) | (1 << DDC_G) | (1 << DDC_SCL) | (1 << DDC_RCK);
	
	
	PORTC = (1 << P_G) | (1 << P_SCL);
	patterncntr = 0;
  
	Hold = 0;

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
						commit();
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

