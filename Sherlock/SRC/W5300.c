
#include"W5300.h"
#include"Parameters.h"
#include "Device1.h"







/***********************************************************************************************
									Software reset W5300
***********************************************************************************************/
void W5300_SoftReset(void)
{
	unsigned char  *ptr;
	ptr=(unsigned char *)MR1;
	*ptr=MR_RST;
	Delay(10);	/* Delay 100ms */
}

/***********************************************************************************************
Initialize W5300, Such as Hardware address, Gateway address, Subnet mask and Source IP address
***********************************************************************************************/
void W5300_Init(void)
{
	unsigned char  *ptr;
	unsigned char i;

	Para *param=(Para *)Parameters;

	/* Software Reset */
	ptr=(unsigned char *)MR1;
	*ptr=MR_RST;
	Delay(10);			/* Delay 100ms */
	
	ptr=(unsigned char *)SHAR0;	/* Set Hardware address */
	for(i=0;i<6;i++)
	{
		*ptr=param->MAC_ADDR[i];
		ptr++;
	}
	
	ptr=(unsigned char *)GAR0;		/* Set Gateway address */
	for(i=0;i<4;i++)
	{
		*ptr=param->GATEWAY[i];
		ptr++;
	}
	
	ptr=(unsigned char *)SUBR0;	/* Set Subnet mask */
	for(i=0;i<4;i++)
	{
		*ptr=param->SUBNET[i];
		ptr++;
	}
	
	ptr=(unsigned char *)SIPR0;	/* Set Source IP address */
	for(i=0;i<4;i++)
	{
		*ptr=param->IP[i];
		ptr++;
	}

	/*********************************************************** 
	Default memory type 
	MTYPER0=0;			memory block 15~8 set as RX memory
	MTYPER1=0xff;		memory block 7~0 set as TX memory
	user may change the value according to DATA communication
	***********************************************************/
	ptr=(unsigned char *)MTYPER0;
	*ptr=0x00;		
	ptr++;
	*ptr=0xff;

/***************************************************************
****************** Default TX memory allocation ***************/
	ptr=(unsigned char *)TMSR0;
	*ptr=0x02;			/* Set SOCKET0 TX memory size 2K */
	ptr++;
	*ptr=0x14;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
/*	user may change the value according to DATA communication
***************************************************************/

/***************************************************************
***************** Default RX memory allocation ****************/
	ptr=(unsigned char *)RMSR0;
	*ptr=0x02;				/* Set SOCKET0 RX memory size 2K */
	ptr++;
	*ptr=0x14;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
	ptr++;
	*ptr=0x08;
/*   user may change the value according to DATA communication
*********************************************************************/

	ptr=(unsigned char *)IMR0;		/* Set Source IP address */
	*ptr=IR_CONFLICT|IR_UNREACH;		/* IP conflict and IP unreach interrupt*/
	ptr++;
	*ptr=0xff;							/* SOCKET0~SOCKET7 interrupt */

}


/********************* Detect Gateway ********************************************
Use SOCKET0 to detect Gatewat. If don't use Gateway, this step can be skipped
Return TRUE if detecte Gateway
Return FALSE if no Gateway
*********************************************************************************/
unsigned char Detect_Gateway(void)
{
	unsigned char  *ptr;
	unsigned char i;

	Para *param=(Para *)Parameters;

	ptr=(unsigned char *)Sn_MR1(0);	/* Set SOCKET0 in TCP mode */
	*ptr=Sn_MR_TCP;
	
	ptr=(unsigned char *)Sn_CR1(0);	/* Open SOCKET0 */
	*ptr=Sn_CR_OPEN;

	ptr=(unsigned char *)Sn_SSR1(0);	/* Set SOCKET0 in TCP mode */
	if(*ptr!=SOCK_INIT)
	{
		ptr=(unsigned char *)Sn_CR1(0);	/* Close SOCKET0 */
		*ptr=Sn_CR_CLOSE;
		
		return false;
	}

	ptr=(unsigned char *)Sn_DIPR0(0);	/* Set Destination IP address */
	for(i=0;i<4;i++)
	{
		*ptr=(param->IP[i])+1;				/* Set Destionation IP in the differnt subnet */
		ptr++;
	}
	
	ptr=(unsigned char *)Sn_CR1(0);	/* Make connection*/
	*ptr=Sn_CR_CONNECT;
	
	ptr=(unsigned char *)Sn_DHAR0(0);
	do
	{
		if(S0_Timeout)
		{
			S0_Timeout=0;
			break;
		}
		else
		{
			if(*ptr!=0xff)
				return true;
		}
	}while(1);

	return false;

}

