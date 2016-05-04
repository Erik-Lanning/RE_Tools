#pragma once
#include <string>

namespace retool
{
	DWORD getPid(std::string processName);

	template<typename T,typename... NextVar>
	static bool containsNullVariable(T t,NextVar... args)
	{
		if (t == NULL)
			return true;
		else
			return containsNullVariable(args...);
	}

	template<typename T>
	static bool containsNullVariable(T t)
	{
		return (t == NULL);
	}
}