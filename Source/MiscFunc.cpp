#include "MiscFunc.h"

	DWORD MiscFunc::FindProcessId(const std::wstring& processName)
	{
		PROCESSENTRY32 processInfo;
		processInfo.dwSize = sizeof(processInfo);

		HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (processesSnapshot == INVALID_HANDLE_VALUE)
			return 0;

		Process32First(processesSnapshot, &processInfo);
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}

		while (Process32Next(processesSnapshot, &processInfo))
		{
			if (!processName.compare(processInfo.szExeFile))
			{
				CloseHandle(processesSnapshot);
				return processInfo.th32ProcessID;
			}
		}

		CloseHandle(processesSnapshot);
		return 0;
	}

	bool MiscFunc::Inject(const char* library_name, const char* processName)
	{
		std::cout << "Starting Injection" << std::endl;
		HMODULE kernel_handle = GetModuleHandle(L"kernel32.dll");
		if (kernel_handle == NULL) {
			std::cerr << "couldn't find kernel32.dll" << std::endl;
			return false;
		}
		DWORD load_lib = (DWORD)GetProcAddress(kernel_handle, "LoadLibraryA");
		if (load_lib == 0) {
			std::cerr << "Could not get address to LoadLibrary function: " << GetLastError() << std::endl;
			return false;
		}

		std::vector<char> temp_convert(processName, processName + strlen(processName));
		std::wstring proc_name_w(temp_convert.begin(), temp_convert.end());

		DWORD pid = FindProcessId(proc_name_w);
		std::cout << "PID: " << pid << std::endl;
		if (pid <= 0) {
			std::cerr << GetLastError() << std::endl;
			return false;
		}
		HANDLE ph = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
		if (ph == NULL) {
			std::cerr << GetLastError() << std::endl;
			return false;
		}
		LPVOID allocate_base = VirtualAllocEx(ph, NULL, strlen(library_name) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		printf("\nMemory Address for allocation: %p\n", allocate_base);
		if (allocate_base == NULL) {
			std::cerr << GetLastError() << std::endl;
			return false;
		}
		int bytes_written;
		if (WriteProcessMemory(ph, allocate_base, library_name, strlen(library_name) + 1, (SIZE_T*) &bytes_written) == 0) {
			std::cerr << GetLastError() << "written: " << bytes_written << std::endl;
			return false;
		}
		else std::cout << "Success, bytes written: " << bytes_written << std::endl;
		std::cout << "Injection Complete, attempting to start dll" << std::endl;
		HANDLE thread_id = CreateRemoteThread(ph, NULL, 0, (LPTHREAD_START_ROUTINE)load_lib, allocate_base, 0, NULL);
		if (thread_id == NULL) {
			std::cerr << GetLastError() << std::endl;
			return false;
		}
		else std::cout << "Success with thread id: " << thread_id;
		return true;
	}

	void MiscFunc::GetProcessNames(std::vector<std::wstring>* list_of_names){
		DWORD* process_ids = (DWORD*) calloc(sizeof(DWORD), 2048);
		LPWSTR name = (LPWSTR) calloc(sizeof(TCHAR), 2048);
		unsigned short num_processes;
		DWORD cb = sizeof(DWORD) * 2048;
		DWORD bytes_returned;
		HANDLE proc_handle;
		unsigned int copied_chars = 0;
		EnumProcesses(process_ids, cb, &bytes_returned);
		PROCESSENTRY32 proc_info;
		proc_info.dwSize = sizeof(PROCESSENTRY32);
		num_processes = (unsigned short) bytes_returned / sizeof(DWORD);
		for(int x = 0; x < num_processes; x++){
			proc_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, process_ids[x]);
			if(proc_handle != NULL){
				copied_chars = GetModuleBaseName(proc_handle, NULL, name, 2048);
				if(copied_chars > 0){
					list_of_names->push_back(std::wstring(name));
					memset(name, 0x0, 200 * sizeof(char));
				}
				CloseHandle(proc_handle);
			}
		}
		free(process_ids);
		free(name);
	}