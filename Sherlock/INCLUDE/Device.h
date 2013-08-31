#define true	0xff
#define false	0x00

typedef unsigned char	SOCKET;

#define BUFFER_SIZE	2048
unsigned char  Data_Buffer[BUFFER_SIZE];

unsigned char  Parameters[90];

extern void W5300_SoftReset(void);
extern void W5300_Init(void);
extern unsigned char Detect_Gateway(void);
extern unsigned char SOCKET_Listen(SOCKET s);
extern unsigned char SOCKET_Connect(SOCKET s);
extern unsigned char SOCKET_UDP(SOCKET s);
extern unsigned int Rx_Process(SOCKET s);
extern unsigned char Tx_Process(SOCKET s, unsigned int size);





/* SOCKET0 */
char S0_SendOK;
char S0_Receive;
char S0_Timeout;
char S0_Connect;
char S0_Init;

/* SOCKET1 */
char S1_SendOK;
char S1_Receive;
char S1_Timeout;
char S1_Connect;
char S1_Init;

/* SOCKET2 */
char S2_SendOK;
char S2_Receive;
char S2_Timeout;
char S2_Connect;
char S2_Init;

/* SOCKET3 */
char S3_SendOK;
char S3_Receive;
char S3_Timeout;
char S3_Connect;
char S3_Init;

/* SOCKET4 */
char S4_SendOK;
char S4_Receive;
char S4_Timeout;
char S4_Connect;
char S4_Init;

/* SOCKET5 */
char S5_SendOK;
char S5_Receive;
char S5_Timeout;
char S5_Connect;
char S5_Init;

/* SOCKET6 */
char S6_SendOK;
char S6_Receive;
char S6_Timeout;
char S6_Connect;
char S6_Init;

/* SOCKET7 */
char S7_SendOK;
char S7_Receive;
char S7_Timeout;
char S7_Connect;
char S7_Init;
