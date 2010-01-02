//02.01.2010 prepared for ATMega644

#include "usart.h"

uint8_t USARTstatus;
uint8_t RXbuffer[MaxRX], TXbuffer[MaxRX]; 
uint8_t RXptr, TXptr, RXcount;
int LoopCnt;

// 9600Baud
void USARTinit()
{
	UCSRB |= (1<<TXEN);  // UART TX einschalten
    UCSRC = (1<<USBS0)|(3 << UCSZ00); // Asynchron 8N1     
	UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;
	UCSRB |= ( 1 << RXEN );	// Receiver
	RXptr = 0;
	RXcount = 0;
	TXptr = 0;
	USARTstatus = 0;
}

// called every ca. 40us
void USARTloop()
{
	if (UCSRA & (1<<RXC)) 
	{
		RXbuffer[RXptr] = UDR;
		if (RXptr < MaxRX -1) RXptr++; else RXptr = 0;
		RXcount++;
	}
	switch (USARTstatus) 
	{
		case 0:
			if (RXcount > 0)
			{
				USARTstatus++;
			}
			break;
		case 1:
			if (UCSRA & (1<<UDRE))
			{
				UDR = RXbuffer[TXptr]; // send
				if (TXptr < MaxRX -1) TXptr++; else TXptr = 0;
				RXcount--;
				USARTstatus++;
			}
			break;
		case 2:
			{
				USARTstatus = 0;
				break;
			}

	}

	LoopCnt++;
}
