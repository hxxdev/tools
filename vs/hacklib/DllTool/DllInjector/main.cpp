#ifndef UNICODE
#define UNICODE
#endif

/* This code injects DLL to process.
 * This is done by creating thread in the process.
 * The thread call LoadLibraryA inside the process which will load our DLL. */

#include <Windows.h>

#include "basic_tool.h"
#include "dll_injector.h"
#include <string>

using namespace std;

int main(int argc, char** argv) {
	LPCWSTR ProcessName = L"Notepad.exe";
	LPCWSTR WindowName = L"제목 없음 - 메모장";
	LPCSTR dllPath = "C:\\Users\\g1004\\dev\\tools\\vs\\hacklib\\DllTool\\x64\\Release\\DllExample.dll";
	HANDLE hProcess = NULL;

	//hProcess = OpenProcessByProcessName(ProcessName);
	hProcess = OpenProcessByWindowName(WindowName);

	if (hProcess != NULL) {
		DllInjector dllInjector(hProcess, dllPath);
		dllInjector.inject();
		return 1;
	}

	return NULL;
}