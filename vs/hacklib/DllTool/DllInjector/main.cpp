#ifndef UNICODE
#define UNICODE
#endif

/* This code injects DLL to process.
 * This is done by creating thread in the process.
 * The thread call LoadLibraryA inside the process which will load our DLL. */

#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include "basic_tool.h"

using namespace std;

LPCWSTR processName = L"Notepad.exe";
LPCSTR dllPath = "C:\\Users\\g1004\\dev\\tools\\vs\\hacklib\\DllTool\\x64\\Release\\DllExample.dll";

int main(int argc, char** argv) {
	ERROR_CHECK_INIT()

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

			/* Allocate memory inside the process to store the full path of DLL to be injected.
			* Base address of the allocated memory is retreived(`lpBaseAddress`).
			* And then, write path of DLL to be injected to this base address. */
			LPVOID lpBaseAddress = NULL;
			ERROR_CHECK(lpBaseAddress = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE))
			ERROR_CHECK(WriteProcessMemory(hProcess, lpBaseAddress, dllPath, strlen(dllPath) + 1, NULL))

			/* LoadLibraryA exists inside kernel32.dll.
				* Get handle of kernel32.dll. */
			HMODULE kernel32base = NULL;
			ERROR_CHECK(kernel32base = GetModuleHandle(L"kernel32.dll"))

			/* Get address of LoadLibraryA. */
			FARPROC pAddress = NULL;
			ERROR_CHECK(pAddress = GetProcAddress(kernel32base, "LoadLibraryA"))

			/* Create thread in process that runs LoadLibraryA. */
			HANDLE thread = NULL;
			ERROR_CHECK(thread = CreateRemoteThread(hProcess,
													NULL,
													0,
													(LPTHREAD_START_ROUTINE)pAddress,
													lpBaseAddress,
													0,
													NULL))

			/* Wait until the thread is created. */
			ERROR_CHECK(WaitForSingleObject(thread, INFINITE))

			/* Wait until the thread is finished executing. */
			LPDWORD exitCode = NULL;
			ERROR_CHECK(GetExitCodeThread(thread, exitCode))

			/* Clean up */
			ERROR_CHECK(VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE))
			ERROR_CHECK(CloseHandle(thread))
			ERROR_CHECK(CloseHandle(hProcess))

			return 0;
		}
	} while (Process32Next(snapshot, &pe32));

	/* if process with name `processName` is not found,
	 * display a message box showing "Process not found." */
	wstring wstrProcessName(processName);
	wstring message = L"Process " + wstrProcessName + L" not found.";
	int msgboxID = NULL;
	ERROR_CHECK(MessageBox(	NULL,
							message.c_str(),
							(LPCWSTR)L"Error",
							MB_OK | MB_DEFBUTTON1))
	return -1;
}