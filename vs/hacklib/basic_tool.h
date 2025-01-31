#ifndef BASIC_TOOL_H
#define BASIC_TOOL_H

#define ERROR_CHECK_INIT()	\
int errorCode = -1;			\

#define ERROR_CHECK(X)		\
if (!(X)) {					\
	HandleError();			\
	return errorCode--;		\
}							\

void DebugMessage(LPCWSTR DebugMessage);
void AssertError(LPCWSTR ErrorMessage);
bool HandleError();
HMODULE GetModule(HANDLE hProcess);

#endif