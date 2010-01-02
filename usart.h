#include <avr/io.h>
#include <inttypes.h>

#define BAUD 9600UL      // Baudrate
#define MaxRX 16

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
 

#if defined (__AVR_ATmega644__)

#define UCSRA UCSR0A
#define UCSRB UCSR0B 
#define UCSRC UCSR0C 
#define UBRRL UBRR0L
#define UBRRH UBRR0H 
#define TXEN TXEN0
#define RXEN RXEN0 
#define RXC RXC0
#define UDR UDR0
#define UDRE UDRE0

#endif

//vars
extern uint8_t USARTstatus;

//functs 
extern void USARTinit();

extern void USARTloop();
