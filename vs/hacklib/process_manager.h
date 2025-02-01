#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

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

	/* Close Process */
	int CloseProcess();

	/* Get base address of module(`ModuleName`).
	 * Refer to Cheat Enginer for exact module name. */
	DWORD64 Get64BitBaseAddress(LPCWSTR ModuleName);
};

#endif