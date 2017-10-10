#ifndef MISCFUNC
#define MISCFUNC

#include "windows.h"
#include "Tlhelp32.h"
#include "intrin.h"
#include "stdio.h"
#include "iostream"
#include "fstream"
#include <vector>
#include <atlconv.h>
#include <Psapi.h>

namespace MiscFunc{
	bool Inject(const char* library_name, const char* processName);
	DWORD FindProcessId(const std::wstring& processName);
	void GetProcessNames(std::vector<std::wstring>* list_of_names);
}
#endif