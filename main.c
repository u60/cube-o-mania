#include <inttypes.h>
#include <avr/io.h>

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

#define MaxLEDs 12
#define PWMres 200
 
int PWM[MaxLEDs];
int X, dX, eX, XChanged, YStart, YEnd;
int dY[MaxLEDs], eY[MaxLEDs];

int fademode = 0;
const int numanimas = 2;
int mux, idx, hold;
 
struct pattern {
	int hold;
	int fade;
	int pwm[MaxLEDs];
};


struct pattern AnimationA[2] ={
	{
	100,0,
	{
	100, 100, 100,
	100, 100, 100,
	100, 100, 100,
	100, 100, 100}},

	{
	100,0,
	{
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0}},

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
				if (2*(eY[i] + dY[i]) > -PWMres)
				{
					eY[i] += dY[i];
				}
				else
				{
					PWM[i]++;
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
			hold++;
			eX += dX-PWMres;
			//setled mist
			XChanged = 1;
		}

	}
}

void main()
{
	unsigned int i, k, patterncntr;


	DDRC = (1 << DDC_IN) | (1 << DDC_SCK) | (1 << DDC_G) | (1 << DDC_SCL) | (1 << DDC_RCK);
	
	
	PORTC = (1 << P_G) | (1 << P_SCL);
	patterncntr = 0;
  
	hold = 0;

	while (1) 
	{
	
		while (patterncntr < numanimas)
		{
			X = 0;
			eX = 0;
			XChanged = 0;

			for (i = 0; i < MaxLEDs; i++)
			{
				
				eY[i] = 0;
			  YStart = AnimationA[patterncntr].pwm[i];

				if (patterncntr < numanimas-1) YEnd = AnimationA[patterncntr+1].pwm[i]; else YEnd = AnimationA[0].pwm[i];
				//Y[i] = YStart;
				dY[i] = YEnd-YStart;
				dX = AnimationA[patterncntr].hold; 
				PWM[i] = AnimationA[patterncntr].pwm[i];
			}

			while (hold <= AnimationA[patterncntr].hold)
			{
				for (i=0; i<=PWMres; i++)
				{	
					fademode = AnimationA[patterncntr].fade;
					if (fademode > 0) fade();	
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
							   setLED(1);
							   setLED(0);
							   break;
							case 1 :
							   setLED(0);
							   setLED(1);
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
					PORTC &= ~(1 << P_G); // OE

/*					
					for (k=0; k<=5; k++)
					{	
						if (i < PWM[k]) setLED(1); else setLED(0);
					}
					setLED(1);
					setLED(0);
					commit();
	
					for (k=6; k<=11; k++)
					{
						if (i < PWM[k]) setLED(1); else setLED(0);
					}
					setLED(0);
					setLED(1);
					commit();
					PORTC &= ~(1 << P_G);
*/					
				}
			if (fademode == 0)	hold++;	
			} 
			hold = 0;
			patterncntr++;	
		}
		patterncntr = 0;
	}
}

