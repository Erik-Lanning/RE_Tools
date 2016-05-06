#include <Windows.h>
#include <Tlhelp32.h>
#include "globalFunctionsTest.h"

namespace retool
{
	void testAllGlobalFunctions()
	{
		testContainsNullVariable();
	}

	void testContainsNullVariable()
	{
		DWORD pid = NULL;
		HANDLE process = NULL;
		LPVOID loadLibraryAddress = NULL;
		LPVOID loadLibraryArgument = NULL;
		int bytesWriten = NULL;
		HANDLE threadID = NULL;
		bool testCase = containsNullVariable(pid, process, loadLibraryAddress, loadLibraryArgument, bytesWriten, threadID);
		assert (testCase == true);

		DWORD pid1 = 1, pid2 = 1, pid3 = 1;
		testCase = containsNullVariable(pid1, pid2, pid3);
		assert (testCase == false);

		pid1 = 1, pid2 = 0, pid3 = 1;
		testCase = containsNullVariable(pid1, pid2, pid3);
		assert (testCase == true);
	}
}