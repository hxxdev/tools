#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <string>
#include "basic_tool.h"
#include "dll_injector.h"

using namespace std;

DllInjector::DllInjector(HANDLE ProcessHandle, LPCSTR dllFullPath) {
	hProcess = ProcessHandle;
	dllPath = dllFullPath;
}

int DllInjector::inject() {

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