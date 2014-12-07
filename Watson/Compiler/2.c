#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
using namespace std;

#define BUF_SIZE 256
TCHAR szNameIn[]=TEXT("Global\\DiyIn");
TCHAR szNameOut[]=TEXT("Global\\DiyOut");    //指向同一块共享内存的名字

int main()
{
    HANDLE hMapFileIn,hMapFileOut;
    LPCTSTR pBufIn,pBufOut;

    hMapFileIn = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameIn);                 // name of mapping object

    if (hMapFileIn == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufIn = (LPTSTR) MapViewOfFile(hMapFileIn,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufIn == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileIn);

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
    //从main开始至此，A B process代码一样，都是获取共享内存的指针

	double* data=(double*)pBufIn;
	double* result=(double*)pBufOut;
    //以下代码，不停读写共享内存
    while(1)
	{
		printf("%lf\n",*++data);
		cout<<"A process: hit keyboard to receive from B process"<<endl;
		getchar();
    }
    UnmapViewOfFile(pBufIn);
    CloseHandle(hMapFileIn);
    UnmapViewOfFile(pBufOut);
    CloseHandle(hMapFileOut);
    return 0;
}