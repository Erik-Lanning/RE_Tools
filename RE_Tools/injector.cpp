/*
 * injector.cpp by Erik Lanning, 2016
 *	Implements a class dealing with injecting, hooking, modifying various processes or objects.
 */
#include <Windows.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include "globalFunctions.h"
#include "injector.h"

namespace retool
{
	injector::injector(std::string processName, std::string dllLocation) : isInjected_(false)
	{
		injectDll(processName, dllLocation);
	}

	void injector::injectDll(std::string processName, std::string dllLocation)
	{
		const char *dllLocationBuffer = dllLocation.c_str();
		size_t dllLocationLength = strlen(dllLocationBuffer);

		DWORD pid = getPid(processName);
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		LPVOID loadLibraryAddress = (LPVOID) GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		LPVOID loadLibraryArgument = (LPVOID) VirtualAllocEx(process, NULL, dllLocationLength, MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);
		int writeSuccess = WriteProcessMemory(process, loadLibraryArgument, dllLocationBuffer, dllLocationLength, NULL);
		HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE) loadLibraryAddress, loadLibraryArgument, NULL, NULL);

		isInjected_ = !containsNullVariable(process, loadLibraryAddress, loadLibraryArgument, writeSuccess, threadID);

		CloseHandle(process);
	}
}
