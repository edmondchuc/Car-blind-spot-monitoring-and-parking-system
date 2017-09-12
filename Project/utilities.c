// Author: 				Edmond Chuc
// Date created:	12/09/2017
// File: 					utilities.c
// Description:		Utilities/helper functions

void util_DelayMs(unsigned int numLoops)
{
	unsigned int lp;
	unsigned int i;
	
	for(lp=0; lp<numLoops; lp++)
	{
		for(i=0; i<0xFFFF; i++) {};
	}
}
