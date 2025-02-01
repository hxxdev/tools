#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include "basic_tool.h"

int injected_thread() {
    int msgboxID = NULL;
    ERROR_CHECK(msgboxID = MessageBox(  NULL,
                                        L"Hello, Please press 'M'.",
                                        (LPCWSTR)L"Hello",
                                        MB_OK | MB_DEFBUTTON1), NULL)
    while (true) {
        if (GetAsyncKeyState('M')) {
            int msgboxID = NULL;
            ERROR_CHECK(msgboxID = MessageBox(  NULL,
                                                L"Hello, M",
                                                (LPCWSTR)L"Hello",
                                                MB_OK | MB_DEFBUTTON1), NULL)
            break;
        }
        Sleep(1);
    }
    
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        ERROR_CHECK(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL), NULL)
    }

    return true;
}