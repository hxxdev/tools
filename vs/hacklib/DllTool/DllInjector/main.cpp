#ifndef UNICODE
#define UNICODE
#endif

/* This code injects DLL to process.
 * This is done by creating thread in the process.
 * The thread call LoadLibraryA inside the process which will load our DLL. */

#include <Windows.h>
#include <tlhelp32.h>
#include "basic_tool.h"
#include "dll_injector.h"
#include <string>

using namespace std;

int main(int argc, char** argv) {
	LPCWSTR processName = L"Notepad.exe";
	LPCSTR dllPath = "C:\\Users\\g1004\\dev\\tools\\vs\\hacklib\\DllTool\\x64\\Release\\DllExample.dll";

	/* Take a snapshot of currently running processes.
	 * If this code is run at 32-bit executable in 64-bit OS, it will only capture 32-bit processes.
	 * If this code is run at 64-bit executable in 64-bit OS, it will capture both 32-bit and 64-bit processes.*/
	HANDLE snapshot = 0;
	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(snapshot, &pe32);

	/* Iterate through processes in the snapshot previously captured.
	 * Compare the process name(`szExeFile`) with process we are looking for(`processName`). */
	DWORD processID = NULL;
	HANDLE hProcess = NULL;
	do {
		if (wcscmp(pe32.szExeFile, processName) == 0) {
			/* Open process and get process handle. */
			processID = pe32.th32ProcessID;
			ERROR_CHECK(hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, processID))
		}
	} while (Process32Next(snapshot, &pe32));

	if (hProcess == NULL) {
		/* if process with name `processName` is not found,
		* display a message box showing "Process not found." */
		wstring wstrProcessName(processName);
		wstring message = L"Process " + wstrProcessName + L" not found.";
		int msgboxID = NULL;
		ERROR_CHECK(MessageBox(	NULL,
								message.c_str(),
								(LPCWSTR)L"Error",
								MB_OK | MB_DEFBUTTON1))
	}
	else {
		DllInjector dllInjector(hProcess, dllPath);
		dllInjector.inject();
		return 0;
	}
	return -1;
	
}