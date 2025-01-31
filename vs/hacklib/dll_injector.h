#ifndef DLL_INJECTOR_H
#define DLL_INJECTOR_H

class DllInjector {
private:
	HANDLE hProcess;
	LPCSTR	dllPath;
public:
	DllInjector(HANDLE ProcessHandle, LPCSTR dllFullPath);
	int inject();
};

#endif