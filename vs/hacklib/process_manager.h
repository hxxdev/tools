#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <stdio.h>
#include "basic_tool.h"

class ProcessManager {
private:
	HANDLE hProcess = NULL;
	LPCWSTR ProcessName = NULL;
	LPCWSTR WindowName = NULL;
public:
	/* Constructors*/
	ProcessManager();

	/* Returns process handle(`hProcess`) */
	HANDLE GetProcess();

	/* Open process using process name.
	 * example of ProcessName : "Notepad.exe"
	 * Refer to Windows task manager to find exact window name.*/
	HANDLE OpenProcessByProcessName(LPCWSTR ProcessName);

	/* Open process using window name.
	 * example of WindowName : "제목 없음 - 메모장"
	 * Refer to Windows task manager to find exact window name. */
	HANDLE OpenProcessByWindowName(LPCWSTR WindowName);

	
	/* Read Process */
	template <typename T>
	int ReadProcess(DWORD64 ReadAddress, T* ReadData);

	/* Close Process */
	int CloseProcess();

	/* Get base address of module(`ModuleName`).
	 * Refer to Cheat Enginer for exact module name. */
	DWORD64 Get64BitBaseAddress(LPCWSTR ModuleName);
};

template <typename T>
int ProcessManager::ReadProcess(DWORD64 ReadAddress, T* ReadData) {
	SIZE_T ActualNumBytesRead = 0;
	ERROR_CHECK(ReadProcessMemory(	hProcess,
									(LPCVOID)ReadAddress,
									ReadData,
									sizeof(ReadData),
									&ActualNumBytesRead), NULL)

		if (ActualNumBytesRead != sizeof(ReadData)) {
			wprintf(L"ReadProcessMemory failed\n");
			wprintf(L"Expected Bytes Read : %I64d\n", (long long)sizeof(ReadData));
			wprintf(L"Actual Bytes Read : %I64d\n", (long long)ActualNumBytesRead);
			return NULL;
		}

	return 1;
}
#endif