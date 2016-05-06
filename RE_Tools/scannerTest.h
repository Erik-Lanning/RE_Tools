#include <cassert>
#include <iostream>
#include "scanner.h"

namespace retool
{
	class scannerTest
	{
	public:
		//@pre Process with the name injectorTestExe.exe is running.
		//	   Process must have a the memory value of 0xDEADBEEF stored.
		//@post Class and tests successfully run.
		scannerTest()
		{
			testLocateMatches();

			// Form the search value.
			char needle[sizeof(int) + 1];
			int value = 0xDEADBEEF;
			snprintf(needle, sizeof(int), "%s", (char*) &value);
			needle[sizeof(int)] = '\0';

			std::string processName = "injectorTestExe.exe";
			scanner testScanner(processName);
			std::vector<DWORD> offsets = testScanner.findValue(needle);
			assert(offsets.size() > 0);
		}

		void testLocateMatches()
		{
			std::vector<char> exampleBuffer;
			std::string regex = "Hello world";
			char *message = "Hello world, this is to test Hello world locateMatches method.";
			int expectedMatches = 2;
			int len = strlen(message);

			for (int i = 0; i < len; ++i)
				exampleBuffer.push_back(message[i]);

			std::vector<DWORD> matchIndexes = scanner::locateMatches(regex, exampleBuffer);
			assert(matchIndexes.size() == expectedMatches);
		}
	};
}