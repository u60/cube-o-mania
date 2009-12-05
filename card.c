#include "card.h"

uint8_t CARDstatus;

// init
void CARDinit()
{
	CARDstatus = 0;
}

// loop
void CARDloop()
{
	switch (CARDstatus)
	{
		case 0:
			CARDstatus++;
			break;
		case 1:
			CARDstatus++;
			break;
		case 2:
			CARDstatus = 0;
			break;
		
	}
}
