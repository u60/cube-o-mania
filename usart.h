#include <avr/io.h>
#include <inttypes.h>

#define BAUD 9600UL      // Baudrate
#define MaxRX 16

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
 
//vars
extern uint8_t USARTstatus;

//functs 
extern void USARTinit();

extern void USARTloop();
