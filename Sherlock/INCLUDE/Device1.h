#define true	0xff
#define false	0x00

typedef unsigned char	SOCKET;

#define BUFFER_SIZE	2048

#define S_RX_SIZE	8192
#define S_TX_SIZE	8192

extern unsigned char  Data_Buffer[];

extern unsigned char  Parameters[];

extern char S0_Timeout;

extern void Delay(unsigned long us);


