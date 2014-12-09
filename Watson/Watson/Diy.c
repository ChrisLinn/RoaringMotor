#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
using namespace std;

#define BUF_SIZE 256
TCHAR szNameIn1[]=TEXT("Global\\DiyIn1");
TCHAR szNameIn2[]=TEXT("Global\\DiyIn2");
TCHAR szNameOut[]=TEXT("Global\\DiyOut");    //指向同一块共享内存的名字

void calculate(double* U,double* I,double* output);

int main()
{
    HANDLE hMapFileIn1,hMapFileIn2,hMapFileOut;
    LPCTSTR pBufIn1,pBufIn2,pBufOut;

    hMapFileIn1 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameIn1);                 // name of mapping object

    if (hMapFileIn1 == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufIn1 = (LPTSTR) MapViewOfFile(hMapFileIn1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufIn1 == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileIn1);

        return 1;
    }
	
    hMapFileIn2 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameIn2);                 // name of mapping object

    if (hMapFileIn2 == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufIn2 = (LPTSTR) MapViewOfFile(hMapFileIn2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufIn2 == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileIn2);

        return 1;
    }
	
	
    hMapFileOut = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        2,                // maximum object size (low-order DWORD)
        szNameOut);                 // name of mapping object

    if (hMapFileOut == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufOut = (LPTSTR) MapViewOfFile(hMapFileOut,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        2);

    if (pBufOut == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileOut);

        return 1;
    }

	double* DataU=(double*)pBufIn1;
	double* DataI=(double*)pBufIn2;
	double* Result=(double*)pBufOut;
    //从main开始至此，A B process代码一样，都是获取共享内存的指针
    //以下代码，不停读写共享内存
    while(Result[1])
	{
		calculate(DataU, DataI, Result);
		//printf("%lf",Result[0]);
		//getchar();
    }
    UnmapViewOfFile(pBufIn1);
    CloseHandle(hMapFileIn1);
    UnmapViewOfFile(pBufIn2);
    CloseHandle(hMapFileIn2);
    UnmapViewOfFile(pBufOut);
    CloseHandle(hMapFileOut);
    return 0;
}
void calculate(double* U,double* I,double* output)
{
output[0]=U[0]+I[0];
}