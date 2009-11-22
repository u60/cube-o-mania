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

<<<<<<< HEAD
unsigned int PWM[12];
int X, dX, eX, XChanged;
int YStart[], YEnd[], Y[], dY[], eY[];


struct pattern {
	unsigned int pwm[12];
	unsigned int hold;
	unsigned int fade;
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
=======
#define MaxLEDs 64*3
#define PWMres 100
 
uint8_t PWM[MaxLEDs];
int8_t X, dX, eX, XChanged, YStart, YEnd;
int8_t dY[MaxLEDs], eY[MaxLEDs];

uint8_t fademode = 0;
const uint8_t numanimas = 2;
uint8_t mux, idx;
 
struct pattern {
	uint8_t hold;
	uint8_t fade;
	uint8_t pwm[MaxLEDs];
};


const struct pattern AnimationA[2] ={
	{
	10,1,
	{
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255}},

  	{
	20,1,
  	{
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	80, 80, 80}},
>>>>>>> u60/master


};

<<<<<<< HEAD


=======
>>>>>>> u60/master
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
<<<<<<< HEAD
	unsigned int i;

	while (XChanged != 1)
	{
		for (i = 0; i==11; i++)
		{
			if (dY[i] > 0) 
			{
				if (2*(eY[i] + dY[i]) < 255)
=======
	int i;

	while (XChanged != 1)
	{
	    if (fademode == 1) XChanged = 1; 
		for (i = 0; i < MaxLEDs; i++)
		{
			if (dY[i] > 0) 
			{
				if (2*(eY[i] + dY[i]) < PWMres)
>>>>>>> u60/master
				{
					eY[i] += dY[i];
				}
				else
				{
<<<<<<< HEAD
					Y[i]++;
					eY[i] += (dY[i]-255);
=======
					PWM[i]++;
					eY[i] += (dY[i]-PWMres);
>>>>>>> u60/master
				}
			}
			else
			{
<<<<<<< HEAD
				if (2*(eY[i] + dY[i]) > -255)
=======
				if (2*(eY[i] + dY[i]) > -PWMres)
>>>>>>> u60/master
				{
					eY[i] += dY[i];
				}
				else
				{
<<<<<<< HEAD
					Y[i]++;
					eY[i] += (dY[i]+255);
				}
			}
		
		if (2*(eX + dX) < 255)
=======
					PWM[i]++;
					eY[i] += (dY[i]+PWMres);
				}
			}
		}
		
		if (2*(eX + dX) < PWMres)
>>>>>>> u60/master
		{
			eX += dX;
		}
		else
		{
			X++;
<<<<<<< HEAD
			eX += dX-255;
=======
			eX += dX-PWMres;
>>>>>>> u60/master
			//setled mist
			XChanged = 1;
		}

<<<<<<< HEAD
		}
	}
}

void main()
=======
	}
}

int main()
>>>>>>> u60/master
{
	unsigned int i, k, patterncntr, hold;


	DDRC = (1 << DDC_IN) | (1 << DDC_SCK) | (1 << DDC_G) | (1 << DDC_SCL) | (1 << DDC_RCK);
	
	
<<<<<<< HEAD

=======
>>>>>>> u60/master
	PORTC = (1 << P_G) | (1 << P_SCL);
	patterncntr = 0;

	while (1) 
	{
	
<<<<<<< HEAD
		while (patterncntr <= 1)
=======
		while (patterncntr < numanimas)
>>>>>>> u60/master
		{
			X = 0;
			eX = 0;
			XChanged = 0;

<<<<<<< HEAD
			for (i = 0; i<=11; i++)
			{
				eY[i] = 0;
				Y[i] = YStart[i];

			  YStart[i] = AnimationA[patterncntr].pwm[i];
				YEnd[i] = AnimationA[patterncntr+1].pwm[i];
				dY[i] = YEnd[i]-YStart[i];
				dX = AnimationA[patterncntr].hold;

=======
			for (i = 0; i < MaxLEDs; i++)
			{
				eY[i] = 0;
			  	YStart = AnimationA[patterncntr].pwm[i];
				
				if (patterncntr < numanimas-1) YEnd = AnimationA[patterncntr+1].pwm[i]; else YEnd = AnimationA[0].pwm[i];
				//Y[i] = YStart;
				dY[i] = YEnd-YStart;
				dX = AnimationA[patterncntr].hold;
>>>>>>> u60/master
				PWM[i] = AnimationA[patterncntr].pwm[i];
			}

			while (hold <= AnimationA[patterncntr].hold)
			{
<<<<<<< HEAD
				for (i=0; i<=255; i++)
				{	
=======
				for (i=0; i<=PWMres; i++)
				{	
					fademode = AnimationA[patterncntr].fade;
					if (fademode > 0) fade();	
					for (mux=0; mux<2; mux++)
					{
						for (k=0; k<=5; k++)
						{	
							idx = k*mux*2;
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
>>>>>>> u60/master
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
<<<<<<< HEAD
=======
					*/
>>>>>>> u60/master
				}
				hold++;	
			} 
			hold = 0;
			patterncntr++;	
		}
		patterncntr = 0;
	}
}

