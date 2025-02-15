#ifndef UNICODE
#define UNICODE
#endif

/* This code injects DLL to process.
 * This is done by creating thread in the process.
 * The thread call LoadLibraryA inside the process which will load our DLL. */

#include <Windows.h>

#include "basic_tool.h"
#include "process_manager.h"
#include "dll_injector.h"
#include <string>

using namespace std;

int main(int argc, char** argv) {
	LPCWSTR ProcessName = L"Notepad.exe";
	LPCWSTR WindowName = L"제목 없음 - 메모장";
	LPCSTR dllPath = "C:\\Users\\g1004\\dev\\tools\\vs\\hacklib\\DllTool\\x64\\Release\\DllExample.dll";
	HANDLE hProcess = NULL;

	ProcessManager pManager;

	//hProcess = OpenProcessByProcessName(ProcessName);
	hProcess = pManager.OpenProcessByWindowName(WindowName);

	if (hProcess != NULL) {
		DllInjector dllInjector(hProcess);
		dllInjector.inject(dllPath);
		return 1;
	}

	return NULL;
}