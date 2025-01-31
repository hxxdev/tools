#ifndef BASIC_TOOL_H
#define BASIC_TOOL_H

#define ERROR_CHECK(X)					\
if (!(X)) {								\
	HandleError();						\
	wprintf(L"Error occured: ");		\
	wprintf(L#X);						\
	return -1;							\
}										\

void DebugMessage(LPCWSTR DebugMessage);
void AssertError(LPCWSTR ErrorMessage);
bool HandleError();
HMODULE GetModule(HANDLE hProcess);

#endif