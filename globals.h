#include <avr/io.h>
#include <inttypes.h>


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
#define P_SCK_MASK 0x04

//Latch (RCK)
#define LatchPort PORTD
#define DDD_RCK DDD5
#define P_RCK PD5

//OE 74HC595 and 74ACT540
#define DDD_OE	DDD2
#define P_OE PD2


#define MaxColumns 4
#define MaxRows 4
#define MaxLevels 4
#define ColorsPerLed 3
#define MaxMux 4
#define LedPinsPerColumn MaxColumns*ColorsPerLed
#define MaxLedsPerLevel MaxColumns*MaxRows
#define LedPinsPerLevel MaxLedsPerLevel*ColorsPerLed
#define MaxLeds MaxLedsPerLevel*MaxLevels
#define MaxLedPins ColorsPerLed*MaxLeds
#define PWMres 20
#define Lumi 15





#define blauespindel 	{ 5,0,	{BU,BK,BK,BK,BK,BU,BK,BK,BK, BK, BU, BK,BK, BK, BK, BU,},},{5,0,{BK, BK, BK, BK,BU, BU, BK, BK,BK, BK, BU, BU,BK, BK, BK, BK,},},{5,0,{BK, BK, BK, BK,BK, BK, BU, BU,BU, BU, BK, BK,BK, BK, BK, BK,},},{5,0,{BK, BK, BK, BU,BK, BK, BU, BK,BK, BU, BK, BK,BU, BK, BK, BK,},},{5,0,{BK, BK, BU, BK,BK, BK, BU, BK,BK, BU, BK, BK,BK, BU, BK, BK,},},{ 5,0,{BK, BU, BK, BK,BK, BU, BK, BK,BK, BK, BU, BK,	BK, BK, BU, BK,},},





#define RD Lumi, 0, 0
#define BU 0, Lumi, 0
#define GN 0, 0, Lumi
#define WH Lumi, Lumi, Lumi
#define YE Lumi, 0, Lumi
#define BK 0, 0, 0

extern int8_t X, dX, eX, XChanged, YStart, YEnd;
extern int8_t PWM[MaxLedPins], dY[MaxLedPins], eY[MaxLedPins];

extern uint8_t fademode;
extern uint8_t numanimas;
extern uint8_t Hold, idx;

struct pattern {
	uint8_t hold;
	uint8_t fade;
	uint8_t pwm[MaxLedPins];
};

extern struct pattern AnimationA[79];
