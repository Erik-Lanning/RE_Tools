/*
 * scanner.cpp by Erik Lanning, 2016
 *	Implements a class dealing with finding memory addresses based on some value.
 */
#include <regex>
#include "scanner.h"
#include "globalFunctions.h"

namespace retool
{
	scanner::scanner(std::string processName)
	{
		DWORD pid = getPid(processName);
		process_ = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	}

	scanner::~scanner()
	{
		CloseHandle(process_);
	}

	std::vector<DWORD> scanner::findValue(std::string searchValue)
	{
		std::vector<DWORD> valueAddresses;
		std::vector<char> readBuffer;
		const unsigned char *baseAddress = NULL;
		MEMORY_BASIC_INFORMATION processInfo;
		DWORD bytesRead;

		while (VirtualQueryEx(process_, baseAddress, &processInfo,  sizeof(processInfo)))
		{	
			if (isAllocatedMemory(&processInfo))
			{
				readBuffer.resize(processInfo.RegionSize);
				ReadProcessMemory(process_,baseAddress,&readBuffer[0],processInfo.RegionSize,&bytesRead);
				readBuffer.resize(bytesRead);
				if (readBuffer.size() > 0)
				{
					std::vector<DWORD> foundBlockAddresses = locateMatches(searchValue,readBuffer,baseAddress);
					valueAddresses.insert(valueAddresses.end(),foundBlockAddresses.begin(),foundBlockAddresses.end());
				}
			}
			baseAddress += processInfo.RegionSize;
		}
		return valueAddresses;
	}

	bool scanner::isAllocatedMemory(const PMEMORY_BASIC_INFORMATION memoryRegion)
	{
		return (memoryRegion->State == MEM_COMMIT
			&& (memoryRegion->Type == MEM_MAPPED || memoryRegion->Type == MEM_PRIVATE));
	}

	//@pre buffer.size() > 0.
	//@post vector of memory addresses returned.
	std::vector<DWORD> scanner::locateMatches(std::string regex,std::vector<char> buffer,const unsigned char *base)
	{
		std::vector<DWORD> matchAddresses;
		std::regex pattern(regex);

		for (auto it = std::cregex_iterator(&buffer.front(),&buffer.back(),pattern);
			it != std::cregex_iterator();
			++it)
		{
			matchAddresses.push_back((DWORD)base + it->position());
		}
		return matchAddresses;
	}
}