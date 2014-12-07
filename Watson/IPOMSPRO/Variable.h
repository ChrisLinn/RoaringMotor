
int count=0;
double dTime1;
double dTime2;
double dTime3;
double dTime4;
double dTime5;
double dTime6;

int scoppoint=0;
int scoppointmax=400;

int nRow=0;
bool FlagStopStartL=0;
bool FlagStopStartR=0;
bool FlagSend=0;
int Check1;
int Check2;
int Check3;
int Check4;
int Check5;
int Check6;

short int *NetDatabuf;
DWORD NetDatalen=0;
char DataReadBuf0[40000];
short int Debugbuf0[50];
short int Channel1buf0[2][500000];
short int Channel2buf0[2][500000];
short int Channel3buf0[2][500000];
short int Channel4buf0[2][500000];
short int Channel5buf0[2][500000];
short int Channel6buf0[2][500000];
short int *PCh1W=Channel1buf0[0];
short int *PCh1R=Channel1buf0[1];
short int *PCh2W=Channel2buf0[0];
short int *PCh2R=Channel2buf0[1];
short int *PCh3W=Channel3buf0[0];
short int *PCh3R=Channel3buf0[1];
short int *PCh4W=Channel4buf0[0];
short int *PCh4R=Channel4buf0[1];
short int *PCh5W=Channel5buf0[0];
short int *PCh5R=Channel5buf0[1];
short int *PCh6W=Channel6buf0[0];
short int *PCh6R=Channel6buf0[1];
short int *PChC;
short int Channel=7;
short int DebugDatalength=0;
short int DatalengthChannel1 = 0;
short int DatalengthChannel2 = 0;
short int DatalengthChannel3 = 0;
short int DatalengthChannel4 = 0;
short int DatalengthChannel5 = 0;
short int DatalengthChannel6 = 0;
int DatalengthChannel1last = 0;
int DatalengthChannel2last = 0;
int DatalengthChannel3last = 0;
int DatalengthChannel4last = 0;
int DatalengthChannel5last = 0;
int DatalengthChannel6last = 0;

int midlenthtest=1000;///**通道1画波形测试暂存数据长度
short int channelPlayPoint=0;//通道1第几个点的索引
short int StartchannelPlayPoint=6000; //显示点数起始点

CString Contr_Q1;
CString Contr_Q3;
CString Contr_Q7;
CString Contr_Q10;
CString Contr_QD0;
CString Contr_ON;
CString Contr_OFF;

CString DataTSh;
BYTE DataBufferTSh[150];
int DataLengthTSh=0;
int CHNum=0;
bool DebugDataAllow;