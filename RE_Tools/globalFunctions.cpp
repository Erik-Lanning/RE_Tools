#include <Windows.h>
#include <Tlhelp32.h>
#include "globalFunctions.h"

namespace retool
{
	// Function from RosD.
	DWORD getPid(std::string processName)
	{
		HANDLE hsnap;
		PROCESSENTRY32 pt;
		hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		do {
			if (pt.szExeFile == processName){
				DWORD pid = pt.th32ProcessID;
				CloseHandle(hsnap);
				return pid;
			}
		} while (Process32Next(hsnap,&pt));
		CloseHandle(hsnap);
		return 0;
	}
}