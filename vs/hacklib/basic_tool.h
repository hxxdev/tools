#ifndef BASIC_TOOL_H
#define BASIC_TOOL_H

#define ERROR_CHECK(X, Y)				\
if ((X) == (Y)) {						\
	HandleError();						\
	wprintf(L"Error occured: ");		\
	wprintf(L#X);						\
	return NULL;						\
}										\

void DebugMessage(LPCWSTR DebugMessage);
void AssertError(LPCWSTR ErrorMessage);
bool HandleError();
HMODULE GetModule(HANDLE hProcess);
/* Open process using process name.
 * example of ProcessName : "Notepad.exe"; */
HANDLE OpenProcessByProcessName(LPCWSTR ProcessName);
/* Open process using window name.
 * example of WindowName : "제목 없음 - 메모장" 
 * Reference to Windows task manager to find exact window name. */
HANDLE OpenProcessByWindowName(LPCWSTR WindowName);

#endif