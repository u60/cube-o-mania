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

#define MaxLEDs 64*3
#define PWMres 100
 
uint8_t PWM[MaxLEDs];
int8_t X, dX, eX, XChanged, YStart, YEnd;
int8_t  Y[MaxLEDs], dY[MaxLEDs], eY[MaxLEDs];

uint8_t fademode = 0;
 
struct pattern {
uint8_t pwm[MaxLEDs];
uint8_t hold;
uint8_t fade;
};


struct pattern AnimationA[]={
	{{
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255}, 10, 1},

  {{
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	80, 80, 80}, 10, 0},


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
	unsigned int i;

	while (XChanged != 1)
	{
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
					Y[i]++;
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
					Y[i]++;
					eY[i] += (dY[i]+PWMres);
				}
			}
		
		if (2*(eX + dX) < PWMres)
		{
			eX += dX;
		}
		else
		{
			X++;
			eX += dX-PWMres;
			//setled mist
			XChanged = 1;
		}

		}
	}
}

int main()
{
	unsigned int i, k, patterncntr, hold;


	DDRC = (1 << DDC_IN) | (1 << DDC_SCK) | (1 << DDC_G) | (1 << DDC_SCL) | (1 << DDC_RCK);
	
	

	PORTC = (1 << P_G) | (1 << P_SCL);
	patterncntr = 0;

	while (1) 
	{
	
		while (patterncntr <= 0)
		{
			X = 0;
			eX = 0;
			XChanged = 0;

			for (i = 0; i < MaxLEDs; i++)
			{
				eY[i] = 0;
			  	YStart = AnimationA[patterncntr].pwm[i];
				YEnd = AnimationA[patterncntr+1].pwm[i];
				Y[i] = YStart;
				dY[i] = YEnd-YStart;
				dX = AnimationA[patterncntr].hold;
				PWM[i] = AnimationA[patterncntr].pwm[i];
			}

			while (hold <= AnimationA[patterncntr].hold)
			{
				for (i=0; i<=PWMres; i++)
				{	
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
				}
				hold++;	
			} 
			hold = 0;
			patterncntr++;	
		}
		patterncntr = 0;
	}
}

