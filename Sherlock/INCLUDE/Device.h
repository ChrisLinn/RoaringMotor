unsigned char  Parameters[90];

extern void W5300_SoftReset(void);
extern void W5300_Init(void);
extern unsigned char Detect_Gateway(void);



#define true	0xff
#define false	0x00

char S0_Timeout;
