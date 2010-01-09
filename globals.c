#include <avr/pgmspace.h>
#include "globals.h"

int8_t X, dX, eX, XChanged, YStart, YEnd;
int8_t PWM[MaxLedPins], dY[MaxLedPins], eY[MaxLedPins];

uint8_t fademode = 1;
uint8_t numanimas = 4;
uint8_t Hold, mux, idx;
 
struct pattern AnimationA[4] PROGMEM ={
	{ //Animation 0
	50,1,
	{
	// Level 0
	RD, YE, GN, BU,
	YE, GN, BU, RD,
	GN, BU, RD, YE,
	BU, RD, YE, GN,

	// Level 1
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	// Level 2
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,	

	// Level 3
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	},},

	{ //Animation 1
	50,1,
	{
	// Level 0	
	GN, BU, RD, YE,
	BU, RD, YE, GN,
	RD, YE, GN, BU,
	YE, GN, BU, RD,

	// Level 1
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	// Level 2
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,	

	// Level 3
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	},},

	{ //Animation 2
	50,1,
	{
	// Level 0	
	BU, RD, YE, GN,
	RD, YE, GN, BU,
	YE, GN, BU, RD,
	GN, BU, RD, YE,

	// Level 1
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	// Level 2
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,	

	// Level 3
	RD, YE, GN, WH,
	YE, GN, WH, RD,
	GN, WH, RD, YE,
	WH, RD, YE, GN,

	},},

	{ //Animation 3
	50,1,
	{
	// Level 0
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 1
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 2
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	// Level 3
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,
	BK, BK, BK, BK,

	},},



};




