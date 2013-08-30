
#include"W5300.h"
#include"Parameters.h"
#include"Device1.h"





/***********************************************************************************************
									Software reset W5300
***********************************************************************************************/
void W5300_SoftReset(void)
{
	unsigned char  *ptr;
	ptr=(unsigned char *)(MR+MR_RST);
	*ptr=1;

}