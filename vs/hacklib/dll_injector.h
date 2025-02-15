#ifndef DLL_INJECTOR_H
#define DLL_INJECTOR_H

class DllInjector {
private:
	HANDLE hProcess;
public:
	DllInjector(HANDLE ProcessHandle);
	int inject(LPCSTR dllFullPath);
};

#endif