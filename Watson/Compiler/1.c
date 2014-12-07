#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
using namespace std;

#define BUF_SIZE 256
TCHAR szName[]=TEXT("Global\\MyFileMappingObject");    //指向同一块共享内存的名字

int main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }
    //从main开始至此，A B process代码一样，都是获取共享内存的指针

	float* s=(float*)pBuf;
    //以下代码，不停读写共享内存
    while(1)
    {
		*s=171.0;
		*++s=172.0;
		(*s)++;
		getchar();
    }
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}