#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include "basic_tool.h"

int injected_thread() {
    ERROR_CHECK_INIT()

    int msgboxID = NULL;
    ERROR_CHECK(msgboxID = MessageBox(  NULL,
                                        L"Hello, Please press 'M'.",
                                        (LPCWSTR)L"Hello",
                                        MB_OK | MB_DEFBUTTON1))
    while (true) {
        if (GetAsyncKeyState('M')) {
            int msgboxID = NULL;
            ERROR_CHECK(msgboxID = MessageBox(  NULL,
                                                L"Hello, M",
                                                (LPCWSTR)L"Hello",
                                                MB_OK | MB_DEFBUTTON1))
            break;
        }
        Sleep(1);
    }
    
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    ERROR_CHECK_INIT()
    if (fdwReason == DLL_PROCESS_ATTACH) {
        ERROR_CHECK(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL))
    }

    return true;
}