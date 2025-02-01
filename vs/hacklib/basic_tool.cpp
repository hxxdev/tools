#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include "basic_tool.h"

using namespace std;

void DebugMessage(LPCWSTR DebugMessage) {
	wprintf(L"%s\n", DebugMessage);
}

void AssertError(LPCWSTR ErrorMessage) {
	int msgboxID = MessageBox(	NULL,
								ErrorMessage,
								(LPCWSTR)L"Error",
								MB_ICONWARNING | MB_OK | MB_DEFBUTTON1);
	switch (msgboxID) {
	case IDOK:
		// TODO: add code
		break;
	}
	return;
}

bool HandleError(void) {
	DWORD ErrorCode = GetLastError();
	LPWSTR message = nullptr;

	if (ErrorCode == 0) {
		wprintf(L"No error to handle.\n");
		return true;
	}

	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
					   FORMAT_MESSAGE_ALLOCATE_BUFFER,
					   nullptr,
					   ErrorCode,
					   MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
					   (LPWSTR) &message,
					   0,
					   nullptr)) {
		wprintf(L"Format message failed with code 0x%x\n", GetLastError());
		return false;
	}

	if (message) {
		wprintf(L"%s", message);
		LocalFree(message);
	}
	return false;
}
