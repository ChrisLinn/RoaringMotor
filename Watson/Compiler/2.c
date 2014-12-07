#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
using namespace std;

#define BUF_SIZE 256
TCHAR szName[]=TEXT("Global\\MyFileMappingObject");    //指向同一块共享内存的名字

int main(int argc, char *argv[])
{
    HANDLE hMapFile;
    LPCTSTR pBuf;
	int i=0;

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
    //从main开始至此，A B process代码一样，都是获取名为"Global\\MyFileMappingObject"的共享内存的指针

    //以下代码，A不停地读共享内存pBuf
    while(1)
    {
        cout<<pBuf<<endl;cout<<++i<<endl;
        cout<<"A process: hit keyboard to receive from B process"<<endl;
        //getchar();
    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}