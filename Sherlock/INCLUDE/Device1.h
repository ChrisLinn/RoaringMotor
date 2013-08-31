#define true	0xff
#define false	0x00

typedef unsigned char	SOCKET;

#define BUFFER_SIZE	2048

#define S_RX_SIZE	8192
#define S_TX_SIZE	8192

extern unsigned char  Data_Buffer[];

extern unsigned char  Parameters[];



/* SOCKET0 */
extern char S0_SendOK;
extern char S0_Receive;
extern char S0_Timeout;
extern char S0_Connect;
extern char S0_Init;

/* SOCKET1 */
extern char S1_SendOK;
extern char S1_Receive;
extern char S1_Timeout;
extern char S1_Connect;
extern char S1_Init;

/* SOCKET2 */
extern char S2_SendOK;
extern char S2_Receive;
extern char S2_Timeout;
extern char S2_Connect;
extern char S2_Init;

/* SOCKET3 */
extern char S3_SendOK;
extern char S3_Receive;
extern char S3_Timeout;
extern char S3_Connect;
extern char S3_Init;

/* SOCKET4 */
extern char S4_SendOK;
extern char S4_Receive;
extern char S4_Timeout;
extern char S4_Connect;
extern char S4_Init;

/* SOCKET5 */
extern char S5_SendOK;
extern char S5_Receive;
extern char S5_Timeout;
extern char S5_Connect;
extern char S5_Init;

/* SOCKET6 */
extern char S6_SendOK;
extern char S6_Receive;
extern char S6_Timeout;
extern char S6_Connect;
extern char S6_Init;

/* SOCKET7 */
extern char S7_SendOK;
extern char S7_Receive;
extern char S7_Timeout;
extern char S7_Connect;
extern char S7_Init;



extern void Delay(unsigned long us);


