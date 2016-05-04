/*
* scanner.cpp by Erik Lanning, 2016
*	Declares a class dealing with finding addresses, string, etc in some process.
*/
#pragma once
#include <Windows.h>
#include <string>
#include <vector>

namespace retool
{
	class scanner
	{
	public:
		friend class scannerTest;
		scanner(std::string processName);
		virtual ~scanner();
		std::vector<DWORD> findValue(const std::string searchValue);

	private:
		HANDLE process_;

		bool isAllocatedMemory(const PMEMORY_BASIC_INFORMATION memoryRegion);
		static std::vector<DWORD> locateMatches(std::string regex,std::vector<char> buffer,const unsigned char *base = 0);
	};
}