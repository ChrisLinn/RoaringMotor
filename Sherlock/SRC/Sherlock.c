#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "Parameters.h"  
#include "Device.h"  
#include "W5300.h"
#include "Device1.h"


/*
待解决：
	1.初始化W5300时应用硬件复位还是软件复位？
*/
/***************************************************************************************
                                   Delay
***************************************************************************************/
void Delay(Uint32 us)
{
   Uint32 i,j;
   for(i = 0; i < us ; i++)
   {
      for(j = 0; j < 100; j++);
   }
}

/***************************************************************************************
                                   Load Parameters from Flash
***************************************************************************************/
void Load_Parameters(void)
{
	unsigned char i;
//	unsigned char  *p_ptr;

	Para *param=(Para *)Parameters;

	//if(D_INPUT1==0)
	{		/* Set Default parameters */
		param -> GATEWAY[0]= 192;				/* default Gateway */
		param -> GATEWAY[1]= 168;
		param -> GATEWAY[2]= 0;
		param -> GATEWAY[3]= 1;

		param -> SUBNET[0]= 255;				/* default subnet mask */
		param -> SUBNET[1]= 255;
		param -> SUBNET[2]= 255;
		param -> SUBNET[3]= 0;

		param -> IP[0]= 192;					/* default local IP address */
		param -> IP[1]= 168;
		param -> IP[2]= 0;
		param -> IP[3]= 20;
	
		for(i=0;i<8;i++)
		{
			param -> Sn_SPORT[i][0]= 0xc3;		/* default SOCKET port number*/
			param -> Sn_SPORT[i][1]= 0x50+i;
		

		param->Sn_DIP[i][0]=192;
		param->Sn_DIP[i][1]=168;
		param->Sn_DIP[i][2]=0;
		param->Sn_DIP[i][3]=30;

		param->Sn_DPORT[i][0]=0xc7;
		param->Sn_DPORT[i][1]=0x38;
		}
		for(i=0;i<8;i++)
			param -> Sn_MODE[i]= TCP_SERVER;	/* SOCKET operate in TCP server (default) */

		//Erase_Page();
		//Write_FALSH_Data();
	}

	param -> MAC_ADDR[0]= 0;				
	param -> MAC_ADDR[1]= 0xa0;
	param -> MAC_ADDR[2]= 0xc9;
	param -> MAC_ADDR[3]= 0x78;
	param -> MAC_ADDR[4]= 0x3e;
	param -> MAC_ADDR[5]= 0x10;
/*
	p_ptr=(unsigned char *)FLASH_MEM_BASE;
	for(i=0;i<4;i++)							
	{
		param -> GATEWAY[i]=*p_ptr;
		p_ptr++;
	}

	for(i=0;i<4;i++)							
	{
		param -> SUBNET[i]=*p_ptr;
		p_ptr++;
	}
	
	p_ptr+=6;

	for(i=0;i<4;i++)							
	{
		param -> IP[i]=*p_ptr;
		p_ptr++;
	}
	
	for(i=0;i<8;i++)							
	{
		param -> Sn_SPORT[i][0]=*p_ptr;
		p_ptr++;
		param -> Sn_SPORT[i][1]=*p_ptr;
		p_ptr++;
	}
*/
/*	for(i=0;i<8;i++)							
	{
		param -> Sn_DIP[i][0]=*p_ptr;
		p_ptr++;
		param -> Sn_DIP[i][1]=*p_ptr;
		p_ptr++;
		param -> Sn_DIP[i][2]=*p_ptr;
		p_ptr++;
		param -> Sn_DIP[i][3]=*p_ptr;
		p_ptr++;
	}

	for(i=0;i<8;i++)						
	{
		param -> Sn_DPORT[i][0]=*p_ptr;	
		p_ptr++;
		param -> Sn_DPORT[i][1]=*p_ptr;
		p_ptr++;
	}

	for(i=0;i<8;i++)
	{
		param->Sn_MODE[i]=*p_ptr;

		if(param->Sn_MODE[i]>UDP_MODE)
			param->Sn_MODE[i]=TCP_SERVER;

		p_ptr++;
	}
*/
//	UART_RX=0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	//指向结构体数组的指针
	Para *param=(Para *)Parameters;



// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
   InitXintf16Gpio();	//zq

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;


// Step 4. 
	//GO GO GO!
	//复位W5300，51例程及PDF说要硬件复位，官方例程却又用软件复位。此处先尝试软件复位
	W5300_SoftReset();

	Load_Parameters();

	Delay(5);


	//???RST_W5300=1;


	W5300_Init();					/* Initialize W5300 */
	
	
	if(Detect_Gateway()==true)
			//D_OUTPUT1=0;				/* Detect Gateway */
		;


}

//===========================================================================
// No more.
//===========================================================================
