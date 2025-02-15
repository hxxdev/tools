#ifndef BASIC_TOOL_H
#define BASIC_TOOL_H

#include <stdio.h>

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
void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);
void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[]);
#endif