#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <string>
#include "basic_tool.h"
#include "dll_injector.h"

using namespace std;

DllInjector::DllInjector(HANDLE ProcessHandle) {
	hProcess = ProcessHandle;
}

int DllInjector::inject(LPCSTR dllFullPath) {

	/* Allocate memory inside the process to store the full path of DLL to be injected.
	* Base address of the allocated memory is retreived(`lpBaseAddress`).
	* And then, write path of DLL to be injected to this base address. */
	LPVOID lpBaseAddress = NULL;
	ERROR_CHECK(lpBaseAddress = VirtualAllocEx(hProcess, NULL, strlen(dllFullPath) + 1, MEM_COMMIT, PAGE_READWRITE), NULL)
	ERROR_CHECK(WriteProcessMemory(hProcess, lpBaseAddress, dllFullPath, strlen(dllFullPath) + 1, NULL), NULL)

	/* LoadLibraryA exists inside kernel32.dll.
	 * Get handle of kernel32.dll. */
	HMODULE kernel32base = NULL;
	ERROR_CHECK(kernel32base = GetModuleHandle(L"kernel32.dll"), NULL)

	/* Get address of LoadLibraryA. */
	FARPROC pAddress = NULL;
	ERROR_CHECK(pAddress = GetProcAddress(kernel32base, "LoadLibraryA"), NULL)

	/* Create thread in process that runs LoadLibraryA. */
	HANDLE thread = NULL;
	ERROR_CHECK(thread = CreateRemoteThread(hProcess,
											NULL,
											0,
											(LPTHREAD_START_ROUTINE)pAddress,
											lpBaseAddress,
											0,
											NULL), NULL)

	/* Wait until the thread has been created. */
	ERROR_CHECK(WaitForSingleObject(thread, INFINITE), WAIT_FAILED)

	/* Wait until the thread has finished executing. */
	DWORD exitCode = NULL;
	do {
		ERROR_CHECK(GetExitCodeThread(thread, &exitCode), NULL)
	} while (exitCode == STILL_ACTIVE);
	
	//GetExitCodeThread(thread, exitCode);

	/* Clean up */
	ERROR_CHECK(VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE), NULL)
	ERROR_CHECK(CloseHandle(thread), NULL)

	return 0;
}