#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <string>
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

HMODULE GetModule(HANDLE hProcess) {
	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;

	if (EnumProcessModulesEx(hProcess, hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_64BIT))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				wstring wstrModName = szModName;
				//you will need to change this to the name of the exe of the foreign process
				wstring wstrModContain = L"flare.exe";
				if (wstrModName.find(wstrModContain) != string::npos)
				{
					return hMods[i];
				}
			}
			else {
				HandleError();
				return nullptr;
			}
		}
		// no module found
		wprintf(L"No module found.\n");
	}
	else {
		HandleError();
		return nullptr;
	}
	return nullptr;
}

HANDLE OpenProcessByProcessName(LPCWSTR ProcessName) {
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
		if (wcscmp(pe32.szExeFile, ProcessName) == 0) {
			/* Open process and get process handle. */
			processID = pe32.th32ProcessID;
			ERROR_CHECK(hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, processID), NULL)
		}
	} while (Process32Next(snapshot, &pe32));

	if (hProcess == NULL) {
		/* if process with name `ProcessName` is not found,
		* display a message box showing "Process not found." */
		wstring wstrProcessName(ProcessName);
		wstring message = L"Process " + wstrProcessName + L" not found.";
		int msgboxID = NULL;
		ERROR_CHECK(MessageBox(	NULL,
								message.c_str(),
								(LPCWSTR)L"Error",
								MB_OK | MB_DEFBUTTON1), NULL)
	}

	return hProcess;
}

HANDLE OpenProcessByWindowName(LPCWSTR WindowName) {
	/* get window handle of `WindowName` */
	HWND windowHandle = NULL;
	windowHandle = FindWindow(NULL, WindowName);

	if (windowHandle == NULL) {
		/* if window with name `WindowName` is not found,
		* display a message box showing "Window not found." */
		wstring wstrWindowName(WindowName);
		wstring message = L"Window " + wstrWindowName + L" not found.";
		int msgboxID = NULL;
		ERROR_CHECK(MessageBox(	NULL,
								message.c_str(),
								(LPCWSTR)L"Error",
								MB_OK | MB_DEFBUTTON1) , NULL)
		return NULL;
	}

	/* get PID of Flare.exe. */
	DWORD pid = 0;
	ERROR_CHECK(GetWindowThreadProcessId(windowHandle, &pid), NULL)

	/* get process handle of Flare.exe. */
	HANDLE hProcess = NULL;
	ERROR_CHECK(hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, pid), NULL)

	return hProcess;
}