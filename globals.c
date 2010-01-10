#include <avr/pgmspace.h>
#include "globals.h"

int8_t X, dX, eX, XChanged, YStart, YEnd;
int8_t PWM[MaxLedPins], dY[MaxLedPins], eY[MaxLedPins];

uint8_t fademode = 1;
uint8_t numanimas = 79;
uint8_t Hold, idx;
 
struct pattern AnimationA[79] PROGMEM ={
	{ //Animation 0
	5,0,
	{
	// Level 0
	BU, BK, BK, RD,
	BK, BU, RD, BK,
	BK, RD, BU, BK,
	RD, BK, BK, BU,
/*
	// Level 1
	RD, YE, GN, WH,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,

	// Level 3
	BU, RD, RD, BU,
	YE, BU, BU, GN,
	YE, BU, BU, GN,
	BU, RD, RD, BU,
*/
	},},

	{ //Animation 1
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BU, BU, BK, BK,
	BK, BK, BU, BU,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 2
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BK, BK, BU, BU,
	BU, BU, BK, BK,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},

	{ //Animation 3
	5,0,
	{
	// Level 0
	RD, BK, BK, BU,
	BK, RD, BU, BK,
	BK, BU, RD, BK,
	BU, BK, BK, RD,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	
	// Level 2
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,	

	// Level 3
	BU, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BU,

	},},


	{ //Animation 4
	5,0,
	{
	// Level 0	
	BK, BK, BU, BK,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BK, BU, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 5
	5,0,
	{
	// Level 0	
	BK, BU, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BU, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},


	{ //Animation 0
	5,0,
	{
	// Level 0
	BU, BK, BK, GN,
	BK, BU, GN, BK,
	BK, GN, BU, BK,
	GN, BK, BK, BU,
/*
	// Level 1
	RD, YE, GN, WH,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,

	// Level 3
	BU, RD, RD, BU,
	YE, BU, BU, GN,
	YE, BU, BU, GN,
	BU, RD, RD, BU,
*/
	},},

	{ //Animation 1
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BU, BU, BK, BK,
	BK, BK, BU, BU,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 2
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BK, BK, BU, BU,
	BU, BU, BK, BK,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},

	{ //Animation 3
	5,0,
	{
	// Level 0
	GN, BK, BK, BU,
	BK, GN, BU, BK,
	BK, BU, GN, BK,
	BU, BK, BK, GN,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	
	// Level 2
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,	

	// Level 3
	BU, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BU,

	},},


	{ //Animation 4
	5,0,
	{
	// Level 0	
	BK, BK, BU, BK,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BK, BU, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 5
	5,0,
	{
	// Level 0	
	BK, BU, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BU, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},

	{ //Animation 0
	5,0,
	{
	// Level 0
	BU, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BU,
/*
	// Level 1
	RD, YE, GN, WH,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,
	BU, BK, BK, BK,

	// Level 3
	BU, RD, RD, BU,
	YE, BU, BU, GN,
	YE, BU, BU, GN,
	BU, RD, RD, BU,
*/
	},},

	{ //Animation 1
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BU, BU, BK, BK,
	BK, BK, BU, BU,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 2
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BK, BK, BU, BU,
	BU, BU, BK, BK,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},

	{ //Animation 3
	5,0,
	{
	// Level 0
	BK, BK, BK, BU,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BU, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	
	// Level 2
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,
	RD, GN, WH, BU,	

	// Level 3
	BU, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BU,

	},},


	{ //Animation 4
	5,0,
	{
	// Level 0	
	BK, BK, BU, BK,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BK, BU, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	RD, YE, GN, WH,	
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,
	BU, GN, BK, BK,

	// Level 3
	WH, YE, GN, WH,
	YE, BK, BK, RD,
	GN, BK, BK, YE,
	WH, RD, YE, WH,

	},},

	{ //Animation 5
	5,0,
	{
	// Level 0	
	BK, BU, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BU, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	RD, YE, GN, WH,		
	BK, BK, BK, BK,

	// Level 2
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,
	RD, GN, WH, BK,	

	// Level 3
	BU, BK, BK, BU,
	BK, BU, BU, BK,
	BK, BU, BU, BK,
	BU, BK, BK, BU,

	},},


//spindel

	{ //Animation 0
	5,0,
	{
	// Level 0
	BU, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BU,
	},},

	{ //Animation 1
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BU, BU, BK, BK,
	BK, BK, BU, BU,
	BK, BK, BK, BK,
	},},

	{ //Animation 2
	5,0,
	{
	// Level 0	
	BK, BK, BK, BK,
	BK, BK, BU, BU,
	BU, BU, BK, BK,
	BK, BK, BK, BK,
	},},

	{ //Animation 3
	5,0,
	{
	// Level 0
	BK, BK, BK, BU,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BU, BK, BK, BK,
	},},


	{ //Animation 4
	5,0,
	{
	// Level 0	
	BK, BK, BU, BK,
	BK, BK, BU, BK,
	BK, BU, BK, BK,
	BK, BU, BK, BK,
	},},

	{ //Animation 5
	5,0,
	{
	// Level 0	
	BK, BU, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BU, BK,
	},},


//spindel

	{ //Animation 0
	5,0,
	{
	// Level 0
	BU, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

	{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BU, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BU, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BU,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BU,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	},},

			{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BU, BK, BK, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BU, BK, BK,
	BK, BK, BK, BK,
	},},

			{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BU, BK,
	BK, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BU,
	BK, BK, BK, BK,
	},},

			{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BU, BK, BK, BK,
	},},

		{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BU, BK, BK,
	},},

			{ //Animation 0
	5,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BU, BK,
	},},

			{ //Animation 0
	50,0,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BU,
	},},


	blauespindel

	{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BU,
	},},

				{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BU, BU,
	},},


	blauespindel
					{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BK, BK,
	BU, BK, BK, BK,
	BK, BK, BK, BU,
	BK, BK, BU, BU,
	},},

	{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BK, BK,
	BU, BK, BK, BU,
	BU, BK, BK, BU,
	BK, BK, BU, BU,
	},},

	blauespindel

	{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BU, BK,
	BU, BK, BK, BK,
	BK, BK, BK, BU,
	BK, BU, BU, BU,
	},},

	{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BU, BK,
	BU, BK, BK, BU,
	BU, BK, BK, BU,
	BK, BU, BU, BU,
	},},

	blauespindel

	{ //Animation 0
	20,0,
	{
	// Level 0
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	},},

	blauespindel

	{ //Animation 0
	50,1,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK , BK,
	},},

	{ //Animation 0
	50,1,
	{
	// Level 0
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	BU, BU, BU, BU,
	},},
};




